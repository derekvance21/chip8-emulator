#include "opcode.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>

string Opcode::decode(uint16_t opcode) {
  switch (opcode & 0xF000) {
    case 0x0000:
      switch (opcode) {
        case 0x00EE:
          return "RET";
        default:
          std::cerr << "unsupported opcode: " << std::hex << opcode << std::endl;
          exit(1);
      }
      break;
    case 0x1000:
      return "JP addr";
    case 0x2000:
      return "CALL addr";
    case 0x5000:
      switch (opcode & 0x000F) {
        case 0x0:
          return "SE Vx, Vy";
        default:
          std::cerr << "unsupported opcode: " << std::hex << opcode << std::endl;
          exit(1);
      }
    case 0x6000:
      return "LD Vx, byte";
    case 0x7000:
      return "ADD Vx, byte";
    case 0x8000:
      switch (opcode & 0x000F) {
        case 0x0:
          return "LD Vx, Vy";
        case 0x1:
          return "OR Vx, Vy";
        default:
          std::cerr << "unsupported opcode: " << std::hex << opcode << std::endl;
          exit(1);
      }
    case 0xA000:
      return "LD I, addr";
    case 0xD000:
      return "DRW Vx, Vy, n";
    case 0xF000:
      switch (opcode & 0x00FF) {
        case 0x1E:
          return "ADD I, Vx";
        default:
          std::cerr << "unsupported opcode: " << std::hex << opcode << std::endl;
          exit(1);        
      }
    default:
      std::cerr << "unsupported opcode: " << std::hex << opcode << std::endl;
      exit(1);
  }
}

void Opcode::print(uint16_t opcode, uint16_t address) {
  std::cout << std::hex << "0x" << address << ": " << opcode << " ";
  string op = Opcode::decode(opcode);
  std::cout << op << std::endl;
}