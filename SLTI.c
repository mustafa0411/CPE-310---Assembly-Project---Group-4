/**
 * Authors: Mustafa Al-Shebeeb, Seth McBee, Finan Grmay, Bennet Melilo
 * Date: 10/28/2025
 * Byteforge Systems
 * Group: Hefeida Group #4
 */

// give this to the intern

#include "Instruction.h"

void slti_immd_assm(void) {
	// Checking that the op code matches
	if (strcmp(OP_CODE, "SLTI") != 0) {
		// If the op code doesn't match, this isn't the correct command
		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The first parameter should be a register (rt - destination)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The second parameter should be a register (rs - source)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// The third parameter should be an immediate value
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits signed (-32768 to 32767)
	// Check if it fits in 16 bits when masked
	if ((PARAM3.value & 0xFFFF0000) != 0 && (PARAM3.value & 0xFFFF0000) != 0xFFFF0000) {
		state = INVALID_IMMED;
		return;
	}

	/*
		Putting the binary together
	*/

	// Set the opcode (SLTI = 10 = 0x0A = 001010)
	setBits_str(31, "001010");

	// Set Rs (bits 25-21)
	setBits_num(25, PARAM2.value, 5);

	// Set Rt (bits 20-16)
	setBits_num(20, PARAM1.value, 5);

	// Set immediate (bits 15-0)
	setBits_num(15, PARAM3.value, 16);

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;

}

void slti_immd_bin(void) {
	// Check if the op code bits match (SLTI = 001010)
	if (checkBits(31, "001010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read correctly

	/*
		Finding values in the binary
	*/
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("SLTI");
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination register
	setParam(2, REGISTER, Rs); // source register
	setParam(3, IMMEDIATE, imm16); // immediate value

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;

}