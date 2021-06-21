#include <string>
#include <stdint.h>

#define MEMORY_SIZE 4096
#define PROGRAM_DATA_START 0x200
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

using std::string;

class CHIP8 {
	public:
		CHIP8() {}
		~CHIP8() {}
		bool loadRom(string filename);
		void run();
		void printState();

	private:
		void exec(uint16_t opcode);
		void cycle();

		void exec00EE();
		void exec1nnn(uint16_t nnn);
		void exec2nnn(uint16_t nnn);
		void exec5xy0(uint8_t x, uint8_t y);
		void exec6xkk(uint8_t x, uint8_t kk);
		void exec7xkk(uint8_t x, uint8_t kk);
		void exec8xy0(uint8_t x, uint8_t y);
		void exec8xy1(uint8_t x, uint8_t y);
		void execAnnn(uint16_t nnn);
		void execDxyn(uint8_t x, uint8_t y, uint8_t n);
		void execFx1E(uint8_t x);



		uint8_t memory[MEMORY_SIZE] = {};
		uint16_t stack[16] = {};
		uint8_t v[16] = {};
		uint64_t display[DISPLAY_HEIGHT] = {};

		uint16_t i = 0;
		uint16_t pc = PROGRAM_DATA_START;
		uint8_t sp = 0;
		uint8_t dt = 0;
		uint8_t st = 0;

};
