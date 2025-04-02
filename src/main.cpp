#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <array>

#define IS_CHAR_VALID(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-' || currentChar == '.' || currentChar == ',' || currentChar == '[' || currentChar == ']')
#define IS_CHAR_MULTI(currentChar) (currentChar == '>' || currentChar == '<' || currentChar == '+' || currentChar == '-')


typedef struct Token {
  char type;
  size_t data; // reference to matching instruction OR n of times command should be repeated
} Token;

int main(int argc, char* argv[]) {
  // Input & output files provided?
  if (argc < 3) {
    std::cout << "Error: No input/output files.\nUsage: " << argv[0] << " <in.bf> <out.asm>" << std::endl;
    return 1;
  }

  // Input file exists?
  std::ifstream inFile(argv[1]);

  if (inFile.fail()) {
    std::cout << "Error: Couldn't read input file " << argv[1] << std::endl;
    return 1;
  }

  // Output file can be created?
  std::ofstream outFile(argv[2]);

  if (outFile.fail()) {
    std::cout << "Error: Couldn't create output file " << argv[2] << std::endl;
    return 1;
  }

  // ---- Read file ----
  // First pass, get amount of tokens
  char currentChar;
  char lastChar = '\0';

  int tokenAmount = 0;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    // Some successive characters are just stored as a single command
    // Their 'data' field represents how many times it should be executed
    if (!IS_CHAR_MULTI(currentChar) || currentChar != lastChar) {
      tokenAmount++;
    }

    lastChar = currentChar;
  }

  // ---- init command storage ----
  std::vector<Token> commands;
  commands.resize(tokenAmount);

  // Rewind file
  inFile.clear();
  inFile.seekg(0);

  // ---- Store tokens ----
  // Second pass, store tokens
  size_t i = 0;
  size_t data = 1;
  lastChar = '\0';
  size_t bracketIndex = 0;
  std::stack<size_t> bracketStack;

  while (inFile.get(currentChar)) {
    if (!IS_CHAR_VALID(currentChar)) { continue; }

    if (currentChar == '[') {
      data = bracketIndex;
      bracketStack.push(bracketIndex++);
    }
    else if (currentChar == ']') {
      if (bracketStack.empty()) {
        std::cout << "Error in input file at pos. " << inFile.tellg() << std::endl;
        throw std::runtime_error("Unmatched Closing Bracket");
      }
      // Assign last opening bracket's index to this one
      data = bracketStack.top();
      bracketStack.pop();
    }
    else {
      // Optimize
      if (IS_CHAR_MULTI(currentChar) && currentChar == lastChar) {
        commands[i - 1].data += 1;
        continue;
      }
      else {
        data = 1;
      }
    }

    lastChar = currentChar;
    commands[i++] = Token {
      .type = currentChar,
      .data = data,
    };
  }

  // Check for overflow
  if (bracketStack.size() != 0) {
    std::cout << "Error in input file" << std::endl;
    throw std::runtime_error("Unmatched Opening Bracket");
  }

  // Close input file
  inFile.close();

  // ---- Insert starting code ----
  outFile << "# Code generated using github.com/Nanrech/bf-mips\n"
             ".data\ntape: .space 4096\n\n"
             ".text\nmain:\n"
             "  # Set Memory Pointer\n"
             "  la $t0, tape\n\n"
             "  # Zero out tape\n"
             "  li $t1, 4096\n"
             "  _clear_tape:\n"
             "  sb $zero, 0($t0)\n"
             "  addi $t0, $t0, 1\n"
             "  addi $t1, $t1, -1\n"
             "  bnez $t1, _clear_tape\n"
             "  addi $t0, $t0, -4096\n\n";

  // ---- Generate output code ----
  for (auto c : commands) {
    switch (c.type) {
      case '>': {
        outFile << "  sb $t1, 0($t0) # >\n"
                   "  addi $t0, $t0, " << c.data << "\n"
                   "  lbu $t1, 0($t0)\n\n";
        break;
      }
      case '<': {
        outFile << "  sb $t1, 0($t0) # >\n"
                   "  addi $t0, $t0, -" << c.data << "\n"
                   "  lbu $t1, 0($t0)\n\n";
        break;
      }
      case '+': {
        outFile << "  addi $t1, $t1, " << c.data << " # +\n"
                   "  andi $t1, $t1, 0xff\n\n";
        break;
      }
      case '-': {
        outFile << "  addi $t1, $t1, -" << c.data << " # -\n"
                   "  andi $t1, $t1, 0xff\n\n";
        break;
      }
      case '.': {
        outFile << "  li $v0, 11 # .\n"
                   "  move $a0, $t1\n"
                   "  syscall\n\n";
        break;
      }
      case ',': {
        outFile << "  li $v0, 12 # ,\n"
                   "  syscall\n"
                   "  move $t1, $v0\n\n";
        break;
      }
      case '[': {
        outFile << "  _BO" << c.data << ": # [\n"
                   "  beqz $t1, _BC" << c.data << "\n\n";
        break;
      }
      case ']': {
        outFile << "  bnez $t1, _BO" << c.data << " # ]\n"
                   "  _BC" << c.data << ":\n\n";
        break;
      }
      default:
        break;
    }
  }

  // Insert closing code
  outFile << "  # Exit Syscall\n"
          << "  li $v0, 10\n"
          << "  syscall\n";

  // Close output file
  outFile.close();

  return 0;
}
