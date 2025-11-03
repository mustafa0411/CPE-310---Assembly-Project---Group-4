/**
 * Authors: Mustafa Al-Shebeeb, Seth McBee, Finan Grmay, Bennet Melilo
 * Date: 10/28/2025
 * Byteforge Systems
 * Group: Hefeida Group #4
 */

// dont get paid enough to implement

#include "Instruction.h"

void ori_immd_assm(void) {
		// If the op code doesnt match, this isnt the correct command
	if (strcmp(OP_CODE, "ORI") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

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

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// Set the opcode for ORI
	setBits_str(31, "001101");

	// set Rt
	setBits_num(25, PARAM1.value, 5);

	// set Rs
	setBits_num(20, PARAM2.value, 5);

	// set immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void ori_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "001101") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

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

	setOp("ORI");
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); // destination register
	setParam(2, REGISTER, Rs); // source register
	setParam(3, IMMEDIATE, imm16); // immediate value

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;


}



