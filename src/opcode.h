#include <string>

using std::string;

class Opcode {
  public:
    static string decode(uint16_t opcode);
    static void print(uint16_t opcode, uint16_t address);
    static uint8_t op(uint16_t opcode) { return opcode >> 12; }
    static uint8_t x(uint16_t opcode) { return (opcode & 0x0F00) >> 8; }
    static uint8_t y(uint16_t opcode) { return (opcode & 0x00F0) >> 4; }
    static uint8_t kk(uint16_t opcode) { return opcode & 0x00FF; }
    static uint16_t nnn(uint16_t opcode) { return opcode & 0x0FFF; }
    static uint8_t n(uint16_t opcode) { return opcode & 0x000F; }


};