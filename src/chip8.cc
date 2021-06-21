#include "chip8.h"
#include "opcode.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;

bool CHIP8::loadRom(string filename) {
  ifstream f(filename, std::ios::binary);
  if (f.is_open()) {
    f.read((char*) &memory[PROGRAM_DATA_START], MEMORY_SIZE - PROGRAM_DATA_START);
    cout << f.gcount() << " bytes read from: " << filename << endl;
    if (f.eof()) {
      for (int k = 0; k < f.gcount(); k+=2) {
        cout << std::hex << "0x" << (int) (pc + k) << ": " << (int) memory[pc + k] << (int) memory[pc+k+1] << endl;
      }
      return true;
    }
    else {
      return false;
    }
  } 
  else {
    cerr << "failed to open: " << filename << endl;
    return false;
  }
}

void CHIP8::printState() {
  cout << std::hex << "I: " << i << ", PC: " << pc << ", SP: " << (0x00FF & sp) << ", DT: " << (0x00FF & dt) << ", ST: " << (0x00FF & st) << endl;
  cout << "registers: ";
  for (int k = 0; k < 16; k++) {
    cout << std::hex << (0x00FF & v[k]) << " ";
  }
  cout << endl;
  cout << "stack: ";
  for (int k = 0; k < 16; k++) {
    cout << std::hex << stack[k] << " ";
  }
  cout << endl << endl;
}

void CHIP8::exec(uint16_t opcode) {
  uint8_t op = Opcode::op(opcode);
  uint8_t x = Opcode::x(opcode);
  uint8_t y = Opcode::y(opcode);
  uint8_t kk = Opcode::kk(opcode);
  uint8_t n = Opcode::n(opcode);
  uint16_t nnn = Opcode::nnn(opcode);
  Opcode::print(opcode, pc & 0xfff);

  switch (op) {
    case 0x0:
      switch (opcode) {
        case 0x00EE: exec00EE(); break;
      }
      break;
    case 0x1: exec1nnn(nnn); break;
    case 0x2: exec2nnn(nnn); break;
    case 0x5:
      switch (n) {
        case 0x0: exec5xy0(x, y); break;
      }
      break;
    case 0x6: exec6xkk(x, kk); break;
    case 0x7: exec7xkk(x, kk); break;
    case 0x8: 
      switch (n) {
        case 0x0: exec8xy0(x, y); break;
        case 0x1: exec8xy1(x, y); break;
      }
      break;
    case 0xA: execAnnn(nnn); break;
    case 0xD: execDxyn(x, y, n); break;
    case 0xF:
      switch (opcode & 0x00FF) {
        case 0x1E: execFx1E(x); break;
      }
      break;
  }
  printState();

}

void CHIP8::exec00EE() {
  pc = stack[sp];
  sp -= 1;
}

void CHIP8::exec1nnn(uint16_t nnn) {
  pc = nnn; 
}

void CHIP8::exec2nnn(uint16_t nnn) {
  if (sp == 15) {
    cerr << "out of stack space!" << endl;
    exit(1);
  }
  sp += 1;
  stack[sp] = pc;
  pc = nnn;
}

void CHIP8::exec5xy0(uint8_t x, uint8_t y) {
  if (v[x] == v[y]) {
    pc += 2;
  }
}

void CHIP8::exec6xkk(uint8_t x, uint8_t kk) {
  v[x] = kk;
}

void CHIP8::exec7xkk(uint8_t x, uint8_t kk) {
  v[x] += kk;
}

void CHIP8::exec8xy0(uint8_t x, uint8_t y) {
  v[x] = v[y];
}

void CHIP8::exec8xy1(uint8_t x, uint8_t y) {
  v[x] = v[x] | v[y];
}

void CHIP8::execAnnn(uint16_t nnn) {
  i = nnn;
}

void CHIP8::execDxyn(uint8_t x, uint8_t y, uint8_t n) {
  uint64_t row, draw, update, line;
  for (int k = 0; k < n; k++) {
    line = memory[i + k];
    row = display[v[y] + k];
    if (v[x] > DISPLAY_WIDTH - 8) {
      uint8_t overflow = v[x] + 8 - DISPLAY_WIDTH;
      draw = line << (8 - overflow) >> (8 - overflow) << (DISPLAY_WIDTH - overflow) | line >> overflow;
    }
    else {
      draw = line << (DISPLAY_WIDTH - 8 - v[x]);
    }

    update = row ^ draw;
    
    // if a pixel was on previously (row) and is now not on (update), a pixel was erased, so set Vf to 1
    v[0xf] = (row & ~update) != 0 ? 1 : 0;
    display[y + k] = update;
  }
}

void CHIP8::execFx1E(uint8_t x) {
  i += v[x];
}

void CHIP8::cycle() {
    uint16_t opcode = (memory[pc & 0xfff] << 8) | memory[(pc + 1) & 0xfff];
    
    exec(opcode);
    
    pc += 2;

    // string op = Opcode::decode(opcode);

}

void CHIP8::run() {
  for (int k = 0; true; k++) {
    cycle();
  }
}
