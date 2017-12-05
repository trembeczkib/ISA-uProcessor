#include "inst.h"
#include <string>
#include <bitset>
#include <iostream>

//default, empty constructor

instruction::instruction() {
	this->type_code = 0x0;
	this->destination_code = 0x0;
	this->oper_a_code = 0x0;
	this->oper_b_code= 0x0;
}



instruction::instruction(const std::bitset<4>& type_code, const std::bitset<4>& destination_code, const std::bitset<4>& oper_a_code, const std::bitset<4>& oper_b_code) {
	this->type_code = type_code;
	this->destination_code = destination_code;
	this->oper_a_code = oper_a_code;
	this->oper_b_code = oper_b_code;
}



instruction::instruction(const int& type_code, const int& destination_code, const int& oper_a_code, const int& oper_b_code) {
	this->type_code = std::bitset<4>(type_code);
	this->destination_code = std::bitset<4>(destination_code);
	this->oper_a_code = std::bitset<4>(oper_a_code);
	this->oper_b_code = std::bitset<4>(oper_b_code);
}

instruction::instruction(const instruction& source) {
	this->type_code = source.get_type_code();
	this->destination_code = source.get_destination_code();
	this->oper_a_code = source.get_oper_a_code();
	this->oper_b_code = source.get_oper_b_code();
}


void instruction::set_type_code(const std::bitset<4>& typecode) {
	this->type_code = typecode;
}


void instruction::set_destination_code(const std::bitset<4>& destination) {
	this->destination_code = destination;
}


void instruction::set_oper_a_code(const std::bitset<4>& operand_a) {
	this->oper_a_code = operand_a;
}


void instruction::set_oper_b_code(const std::bitset<4>& operand_b) {
	this->oper_b_code = operand_b;
}


const std::bitset<4>& instruction::get_type_code() const {
	return this->type_code;
}


const std::bitset<4>& instruction::get_destination_code() const {
	return this->destination_code;
}


const std::bitset<4>& instruction::get_oper_a_code() const {
	return this->oper_a_code;
}


const std::bitset<4>& instruction::get_oper_b_code() const {
	return this->oper_b_code;
}

void instruction::operator = (const instruction& source) {
	this->type_code = source.get_type_code();
	this->destination_code = source.get_destination_code();
	this->oper_a_code = source.get_oper_a_code();
	this->oper_b_code = source.get_oper_b_code();
}


bool instruction::operator == (const instruction& other) {
	return (
		this->type_code			 == other.get_type_code()			&&
		this->destination_code	 == other.get_destination_code()	&&
		this->oper_a_code		 == other.get_oper_a_code()			&&
		this->oper_b_code		 == other.get_oper_b_code()
		);
}

void instruction::print() const{
		std::string tmp = "";
		switch ((this->get_type_code()).to_ulong()) {
			case 0b0000: tmp = "i2rfl: ";							break;
			case 0b0001: tmp = "load: ";							break;
			case 0b0010: tmp = "store: ";							break;
			case 0b0011: tmp = "add: ";								break;
			case 0b0100: tmp = "sub: ";								break;
			case 0b0101: tmp = "and: ";								break;
			case 0b0110: tmp = "or: ";								break;
			case 0b0111: tmp = "xor: ";								break;
			case 0b1000: tmp = "shl (shift logical left?): ";		break;
			case 0b1001: tmp = "shr (shift logical right?): ";		break;
			case 0b1010: tmp = "branchnotzero: ";					break;
			case 0b1011: tmp = "branchnotnegative: ";				break;
			case 0b1100: tmp = "jmp: ";								break;
			default: tmp = "invalid instruction code: ";
		}
		std::cout << tmp << this->get_type_code() << " " << this->get_destination_code() << " " << this->get_oper_a_code() << " " << this->get_oper_b_code() << std::endl;
}


/*
std::ostream &operator << (std::ostream &str, const instruction&  inst) {
	std::string tmp = "";
	
	switch ((inst.get_type_code()).to_ulong()) {
	case 0000: tmp = "i2rfl: ";							break;
	case 0001: tmp = "load: ";							break;
	case 0010: tmp = "store: ";							break;
	case 0011: tmp = "add: ";							break;
	case 0100: tmp = "sub: ";							break;
	case 0101: tmp = "and: ";							break;
	case 0110: tmp = "xor: ";							break;
	case 0111: tmp = "jump: ";							break;
	case 1000: tmp = "shl (shift logical left?): ";		break;
	case 1001: tmp = "shr (shift logical right?): ";	break;
	case 1010: tmp = "branchnotzero: ";					break;
	case 1011: tmp = "branchnotnegative: ";				break;
	case 1100: tmp = "jmp: ";							break;
	default: tmp = "invalid instruction code: ";
	}
	
	return str;

}

*/
