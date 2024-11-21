#ifndef CPU_H
#define CPU_H

typedef int bool;
#define true 1
#define false 0

typedef unsigned char BYTE;
typedef unsigned short int WORD;

BYTE gameMemory[0xFFF];
BYTE registers[16];
WORD addressI;
WORD programCounter;
BYTE keyState[16];
BYTE delayTimer = 0;
BYTE soundTimer = 0;
BYTE screenData[64][32];
WORD stack[100];
unsigned int stackIndex = 0;
int regx = 0;
int regy = 0;

//-- Utils
void stackPush(WORD data)
{
	stack[stackIndex] = data;
	stackIndex++;
}

void stackPop()
{
	if (stackIndex > 0)
		stackIndex--;
}

/***************************************************************************
* ROUTINE
****************************************************************************/

void init()
{
	addressI = 0;
	programCounter = 0x200;
	memset(registers, 0, sizeof(registers));
	memset(gameMemory, 0, sizeof(gameMemory));
	memset(keyState, 0, sizeof(keyState));
}

void loadGame(const char* fileName)
{
	FILE* in;
	if (fopen_s(&in, fileName, "rb") != 0) {
		printf("Error: Impossible to load file.\n");
		return;
	}

	fread(&gameMemory[0x200], 0xFFF, 1, in);
	fclose(in);
}

void keyPressed(BYTE key)
{
	keyState[key] = 1;
}

void keyReleased(BYTE key)
{
	keyState[key] = 0;
}

void clearScreen()
{
	for (int x = 0; x < 64; ++x)
		for (int y = 0; y < 32; ++y)
			screenData[x][y] = 0;
}

int getKeyPressed()
{
	int res = -1;
	for (int i = 0; i < 16; ++i)
	{
		if (keyState[i] > 0)
		{
			return i;
		}
	}

	return res;
}

WORD getNextOpCode()
{
	WORD res = 0;
	res = gameMemory[programCounter];
	res <<= 8;
	res |= gameMemory[programCounter + 1];
	programCounter += 2;
	return res;
}

void loadOpcodeInRegX(WORD opcode)
{
	regx = opcode & 0x0F00; //which register?
	regx >>= 8;
}

void loadOpcodeInRegY(WORD opcode)
{
	regy = opcode & 0x00F0;
	regy >>= 4;
}

/***************************************************************************
* OPCODES
****************************************************************************/
/* 00EE Flow return; Returns from a subroutine. */
void opcode00EE()
{
	if (stackIndex == 0)
		return;

	programCounter = stack[stackIndex - 1];
	stackPop();
}

/* 1NNN, goto NNN, Jumps to address NNN. */
void opcode1NNN(WORD opcode)
{
	programCounter = opcode & 0x0FFF;
}

/* 2NNN, *(0xNNN)(), Calls subroutine at NNN. */
void opcode2NNN(WORD opcode)
{
	stackPush(programCounter);
	programCounter = opcode & 0x0FFF;
}

/* 3XNN	Cond if (Vx == NN)
   Skips the next instruction if VX equals NN
   (usually the next instruction is a jump to skip a code block). */
void opcode3XNN(WORD opcode)
{
	int NN = opcode & 0x00FF; //take value of NN

	loadOpcodeInRegX(opcode);
	if (registers[regx] == NN)
		programCounter += 2;
}

/* 4XNN	Cond if (Vx != NN)
   Skips the next instruction if VX does not equal NN
   (usually the next instruction is a jump to skip a code block). */
void opcode4XNN(WORD opcode)
{	
	int NN = opcode & 0x00FF; //take value of NN
	
	loadOpcodeInRegX(opcode);
	if (registers[regx] != NN)
		programCounter += 2;
}

/* 6XNN, Vx = NN, Sets VX to NN. */
void opcode6XNN(WORD opcode)
{
	int NN = opcode & 0x00FF; //take value of NN

	loadOpcodeInRegX(opcode);
	registers[regx] = NN;
}

/* 7XNN Const Vx += NN Adds NN to VX (carry flag is not changed). */
void opcode7XNN(WORD opcode)
{
	int NN = opcode & 0x00FF; //take value of NN
	
	loadOpcodeInRegX(opcode);
	registers[regx] += NN;
}

/* 8XY0 Assig Vx = Vy Sets VX to the value of VY. */
void opcode8XY0(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	registers[regx] = registers[regy];
}

/* 8XY1	BitOp Vx |= Vy Sets VX to VX or VY. (bitwise OR operation). */
void opcode8XY1(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	registers[regx] = registers[regx] | registers[regy];
}

/* 8XY2	BitOp Vx &= Vy Sets VX to VX and VY. (bitwise AND operation). */
void opcode8XY2(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	registers[regx] = registers[regx] & registers[regy];
}

/* 8XY3[a] BitOp Vx ^= Vy Sets VX to VX xor VY. */
void opcode8XY3(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	registers[regx] = registers[regx] ^ registers[regy];
}

/* 8XY4	Math Vx += Vy Adds VY to VX. VF is set to 1 when there's an overflow, and to 0 when there is not. */
void opcode8XY4(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	int value = registers[regx] + registers[regy];

	registers[regx] = registers[regx] + registers[regy];

	if (value > 255)
		registers[0xF] = 1;
	else
		registers[0xF] = 0;
}

/* 8XY5	Math Vx -= Vy VY is subtracted from VX.
   VF is set to 0 when there's an underflow, and 1 when there is not. (i.e. VF set to 1 if VX >= VY and 0 if not). */
void opcode8XY5(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	bool underflow = registers[regx] < registers[regy];
	registers[regx] = registers[regx] - registers[regy];

	if (underflow)
		registers[0xF] = 0;
	else
		registers[0xF] = 1;
}

/* 8XY6[a] BitOp Vx >>= 1
   Shifts VX to the right by 1, then stores the least significant bit of VX prior to the shift into VF.*/
void opcode8XY6(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	BYTE temp = registers[regx] & 0x1;

	registers[regx] >>= 1;
	registers[0xF] = temp;
}

/* 8XY7	Math Vx = Vy - Vx
   Sets VX to VY minus VX.
   VF is set to 0 when there's an underflow, and 1 when there is not. (i.e. VF set to 1 if VY >= VX).*/
void opcode8XY7(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	registers[regx] = registers[regy] - registers[regx];

	if (registers[regy] > registers[regx])
		registers[0xF] = 1;
	else
		registers[0xF] = 0;
}

/* 8XYE	Math Vx <<= 1
   Shifts VX to the left by 1, then sets VF to 1 if the most significant
   bit of VX prior to that shift was set, or to 0 if it was unset. */
void opcode8XYE(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	BYTE temp = registers[regx] >> 7;

	registers[regx] <<= 1;
	registers[0xF] = temp;
}

/* 9XY0	Cond if (Vx != Vy)
   Skips the next instruction if VX does not equal VY.
   (Usually the next instruction is a jump to skip a code block).[24] */
void opcode9XY0(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	if (registers[regx] != registers[regy])
		programCounter += 2;
}

/* ANNN, MEM I = NNN, Sets I to the address NNN. */
void opcodeANNN(WORD opcode)
{
	addressI = opcode & 0x0FFF;
}

/* EX9E KeyOp if (key() == Vx)
   Skips the next instruction if the key stored in VX is pressed
   (usually the next instruction is a jump to skip a code block).*/
void opcodeEX9E(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	int key = registers[regx];

	if (keyState[key] == 1)
		programCounter += 2;
}

/* EXA1 KeyOp if (key() != Vx)
   Skips the next instruction if the key stored in VX is not pressed
   (usually the next instruction is a jump to skip a code block).*/
void opcodeEXA1(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	int key = registers[regx];

	if (keyState[key] == 0)
		programCounter += 2;
}

/* FX07	Timer Vx = get_delay() Sets VX to the value of the delay timer. */
void opcodeFX07(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	registers[regx] = delayTimer;
}

/* FX0A	KeyOp Vx = get_key()
   A key press is awaited, and then stored in VX (blocking operation, all instruction halted until next key event) */
void opcodeFX0A(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	int keypressed = getKeyPressed();

	if (keypressed == -1)
		programCounter -= 2;
	else
		registers[regx] = keypressed;
}

/* FX15	Timer delay_timer(Vx) Sets the delay timer to VX. */
void opcodeFX15(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	delayTimer = registers[regx];
}

/* FX18	Sound sound_timer(Vx) Sets the sound timer to VX. */
void opcodeFX18(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	soundTimer = registers[regx];
}

/* FX1E MEM I += Vx Adds VX to I. VF is not affected. */
void opcodeFX1E(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	addressI += registers[regx];
}

/* FX29	MEM	I = sprite_addr[Vx]
   Sets I to the location of the sprite for the character in VX.
   Characters 0-F (in hexadecimal) are represented by a 4x5 font. */
void opcodeFX29(WORD opcode)
{
	printf("[WNG] OpcodeFX29 Not implemented!");
}

/* FX33 BCD
   set_BCD(Vx)
   *(I + 0) = BCD(3);
   *(I + 1) = BCD(2);
   *(I + 2) = BCD(1);
   Stores the binary-coded decimal representation of VX,
   with the hundreds digit in memory at location in I,
   the tens digit at location I + 1, and the ones digit at location I + 2*/
void opcodeFX33(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	int value = registers[regx];

	int hundreds = value / 100;
	int tens = (value / 10) % 10;
	int units = value % 10;

	gameMemory[addressI] = hundreds;
	gameMemory[addressI + 1] = tens;
	gameMemory[addressI + 2] = units;
}

/* FX55	MEM	reg_dump(Vx, &I) Stores from V0 to VX (including VX) in memory, starting at address I.
   The offset from I is increased by 1 for each value written, but I itself is left unmodified. */
void opcodeFX55(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	for (int i = 0; i <= regx; ++i)
	{
		gameMemory[addressI + i] = registers[i];
	}

	addressI = addressI + regx + 1;
}

/* FX65	MEM	reg_load(Vx, &I)
   Fills from V0 to VX (including VX) with values from memory, starting at address I.
   The offset from I is increased by 1 for each value read, but I itself is left unmodified. */
void opcodeFX65(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	for (int i = 0; i <= regx; ++i)
	{
		registers[i] = gameMemory[addressI + i];
	}

	addressI = addressI + regx + 1;
}

/* 5XY0, if (Vx == Vy),
   Skips the next instruction if VX equals VY
   (usually the next instruction is a jump to skip a code block). */
void opcode5XY0(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);
	if (registers[regx] == registers[regy])
		programCounter += 2;
}

void opcodeDXYN(WORD opcode)
{
	loadOpcodeInRegX(opcode);
	loadOpcodeInRegY(opcode);

	int height = opcode & 0x000F;
	int coordx = registers[regx];
	int coordy = registers[regy];

	registers[0xF] = 0;

	for (int yline = 0; yline < height; ++yline)
	{
		BYTE data = gameMemory[addressI + yline];
		int xpixellinv = 7;

		for (int xpixel = 0; xpixel < 8; ++xpixel, --xpixellinv)
		{
			int mask = 1 << xpixellinv;
			if (data & mask)
			{
				int x = coordx + xpixel;
				int y = coordy + yline;

				if (screenData[x][y] == 1)
				{
					registers[0xF] = 1; //collision
				}

				screenData[x][y] ^= 1;
			}
		}
	}
}

#endif