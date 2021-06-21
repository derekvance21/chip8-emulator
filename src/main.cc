#include "chip8.h"
#include <iostream>

using std::cerr;
using std::endl;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: chip8 <ROM-filename>" << endl;
    return 1;
  }

  CHIP8 chip8;
  if (!chip8.loadRom(argv[1])) {
    return 1;
  }

  chip8.run();

}