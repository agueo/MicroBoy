#pragma once

#include <cstdint>
#include <memory>
#include "MemoryBus.h"

struct Flag {
	uint8_t C : 1;
	uint8_t H : 1;
	uint8_t N : 1;
	uint8_t Z : 1;
	uint8_t pad : 4;

	void from_byte(uint8_t byte);
	uint8_t to_byte();
	// flag setting operations
};

enum RegisterName8Bit : uint8_t {
	B, C, D, E, H, L, F, A
};

enum RegisterName16Bit : uint8_t {
	BC, DE, HL, AF, SP
};

class Cpu {
public:
	void connect_bus(std::shared_ptr<MemoryBus> bus);
	int step(int cycles);
	void reset();
	// void clock(); // maybe needed
	bool is_halted() { return m_halted; }
	
	// read and write functions for registers
	uint8_t read_byte(RegisterName8Bit reg);
	void write_byte(RegisterName8Bit reg, uint8_t value);
	uint16_t read_word(RegisterName16Bit reg);
	void write_word(RegisterName16Bit reg, uint16_t value);

private:
	void fetch();
	int decode();
	int execute();

	//--------------------
	// Data members
	//--------------------
	uint8_t m_reg[8];
	Flag m_flags;
	uint16_t m_SP;
	uint16_t m_PC;

	// Create an instruction class that holds everything it needs to execute
	uint8_t m_opcode;
	// useful things for executing instructions
	// TODO look through all the instructions and glean out the common ones
	uint8_t m_data[2];
	// TODO - which registers 8 bit src and dest
	// TODO - which registers 16 bit
	// TODO - an address?
	// TODO - a signed value

	bool m_halted;
	bool IME;

	// Bus connection
	std::shared_ptr<MemoryBus> m_bus;
};

