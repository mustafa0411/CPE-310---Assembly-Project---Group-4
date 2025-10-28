#include "Instruction.h"

/**
 * Authors: Mustafa Al-Shebeeb, Seth McBee, Finan Grmay, Bennet Melilo
 * Date: 10/28/2025
 * Byteforge Systems
 * Group: Hefeida Group #4
 */

// will do later

void mult_reg_assm(void) {
	// If the op code doesnt match, this isnt the correct command
	if (strcmp(OP_CODE, "MULT") != 0) {
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

	// putting the binary together

	// Set the opcode(R-Type instructions have opcode 0)
	setBits_num(31, 0, 5);

	// Set Rs (bits 25-21)
	setBits_num(25, PARAM1.value, 5);

	// Set Rs (bits 20-16)
	setBits_num(20, PARAM2.value, 5);

	// Rd is not used for MULT (bits 15-11 = 0)
	setBits_num(15, 0, 5);

	setBits_num(10, 0, 5);

	// Set the function code (MULT = 24 = 0x18 = 011000)
	setBits_str(5, "011000");

	// Tell the system the encoding is done
	state = COMPLETE_ENCODE;

}

void mult_reg_bin(void) {
	// Check if the op code bits match (R-type = 000000) and function code (MULT = 011000)
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// Find the values in the binary
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	
	// Setting Instruction values
	setOp("MULT");
	// setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rs); // first source register
	setParam(2, REGISTER, Rt); // second source register

	// Tell the system the decoding is done
	state = COMPLETE_DECODE;


}

