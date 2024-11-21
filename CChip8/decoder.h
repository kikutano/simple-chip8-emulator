#ifndef DECODER_H
#define DECODER_H
#include <stdio.h>
#include <stdlib.h>

void DecodeOpcode0(WORD opcode)
{
	switch (opcode & 0xF)
	{
	case 0x0: clearScreen(); break;
	case 0xE: opcode00EE(); break;

	default:
		printf("\n [WRG][0] opcode %04X not implemented.", opcode);
	}
}

void DecodeOpcode8(WORD opcode)
{
	switch (opcode & 0xF)
	{
	case 0x0: opcode8XY0(opcode); break;
	case 0x1: opcode8XY1(opcode); break;
	case 0x2: opcode8XY2(opcode); break;
	case 0x3: opcode8XY3(opcode); break;
	case 0x4: opcode8XY4(opcode); break;
	case 0x5: opcode8XY5(opcode); break;
	case 0x6: opcode8XY6(opcode); break;
	case 0x7: opcode8XY7(opcode); break;
	case 0xE: opcode8XYE(opcode); break;
	default:
		printf("\n [WRG][8] opcode 0x%04X not implemented.", opcode & 0xF00F);
	}
}

void DecodeOpcodeE(WORD opcode)
{
	switch (opcode & 0xF)
	{
	case 0xE: opcodeEX9E(opcode); break;
	case 0x1: opcodeEXA1(opcode); break;
	default:
		printf("\n [WRG][E] opcode 0x%04X not implemented.", opcode & 0x00FF);
		break;
	}
}

void DecodeOpCodeF(WORD opcode)
{
	switch (opcode & 0xFF)
	{
	case 0x07: opcodeFX07(opcode); break;
	case 0x0A: opcodeFX0A(opcode); break;
	case 0x15: opcodeFX15(opcode); break;
	case 0x18: opcodeFX18(opcode); break;
	case 0x1E: opcodeFX1E(opcode); break;
	case 0x29: opcodeFX29(opcode); break;
	case 0x33: opcodeFX33(opcode); break;
	case 0x55: opcodeFX55(opcode); break;
	case 0x65: opcodeFX65(opcode); break;
	default:
		printf("\n [WRG][F] opcode 0x%04X not implemented.", opcode & 0x00FF);
		break;
	}
}

void processNextOpcode()
{
	WORD opcode = getNextOpCode();

	//printf("\n [INF] processing opcode 0x%04X.", opcode & 0xF000);

	switch (opcode & 0xF000)
	{
	case 0x0000: DecodeOpcode0(opcode); break;
	case 0x1000: opcode1NNN(opcode); break;
	case 0x2000: opcode2NNN(opcode); break;
	case 0x3000: opcode3XNN(opcode); break;
	case 0x4000: opcode4XNN(opcode); break;
	case 0x5000: opcode5XY0(opcode); break;
	case 0x6000: opcode6XNN(opcode); break;
	case 0x7000: opcode7XNN(opcode); break;
	case 0x8000: DecodeOpcode8(opcode); break;
	case 0x9000: opcode9XY0(opcode); break;
	case 0xA000: opcodeANNN(opcode); break;
	case 0xD000: opcodeDXYN(opcode); break;
	case 0xE000: DecodeOpcodeE(opcode); break;
	case 0xF000: DecodeOpCodeF(opcode); break;
	default:
		printf("\n [WRG] opcode 0x%04X not implemented.", opcode & 0xF000);
	}
}

#endif