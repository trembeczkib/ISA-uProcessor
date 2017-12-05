#include "uproc.h"
#include <iostream>
#include <bitset>
#include <sstream>



processor::processor(memory<1024, instruction>& program_memory, memory<1024, std::bitset<16>>& data_memory) : program_memory(program_memory), data_memory(data_memory) {
	ip = 0;
	destination_index = 0;
	op_a_index = 0;
	op_b_index = 0;
	mar = 0;
	mdr = 0;
	zero_flag = false;
	negative_flag = false;
	run = false;
}


void processor::run_program() {
	run = true;
	try {
		while (run) {
			fetch();
			std::cout << "@" << ip << ": ";
			ir.print();
			decode();
			execute();
			print_state();
		}
	}
	catch (const char* e) {
		std::cout << std::string(e) << std::endl;
	}
}


void processor::print_state() {
	if (ir.get_type_code() == 0b0000 ||
		ir.get_type_code() == 0b0001 ||
		ir.get_type_code() == 0b0011 ||
		ir.get_type_code() == 0b0100 ||
		ir.get_type_code() == 0b0101 ||
		ir.get_type_code() == 0b0110 ||
		ir.get_type_code() == 0b0111 ||
		ir.get_type_code() == 0b1000 ||
		ir.get_type_code() == 0b1001
		) std::cout << "RF[" << destination_index << "] <= " << rf.read(destination_index) << ", Z <= " << zero_flag << ", N <= " << negative_flag << ", IP <= " << ip << std::endl;

	if (ir.get_type_code() == 0b0010)
		std::cout << "data memory[" << mar << "] <= " << data_memory.read(mar) << ", IP <= " << ip << std::endl;

	if (ir.get_type_code() == 0b1010 ||
		ir.get_type_code() == 0b1011 ||
		ir.get_type_code() == 0b1100 	
		) std::cout << "IP <= " << ip << ", Z <= " << zero_flag << ", N <= " << negative_flag << std::endl;

	std::cout << std::endl;
}


void processor::fetch() {
	ir = program_memory.read(ip);
}


void processor::decode() {
	destination_index = ir.get_destination_code().to_ulong();
	op_a_index = ir.get_oper_a_code().to_ulong();
	op_b_index = ir.get_oper_b_code().to_ulong();

	if (ir.get_type_code().to_ulong() == 0b0001) {
		std::stringstream tmp_strstream;
		tmp_strstream << ir.get_oper_a_code().to_string() << ir.get_oper_b_code().to_string();
		std::bitset<16> tmp_addr(tmp_strstream.str());
		mdr = tmp_addr.to_ulong();
		mar = rf.read(destination_index).to_ulong();
	}
	else if (ir.get_type_code().to_ulong() == 0b0010) {
		std::stringstream tmp_strstream;
		tmp_strstream << ir.get_oper_a_code().to_string() << ir.get_oper_b_code().to_string();
		std::bitset<16> tmp_addr(tmp_strstream.str());
		mar = tmp_addr.to_ulong();
		mdr = rf.read(destination_index).to_ulong();
	}
	else 
	mdr = rf.read(op_a_index).to_ulong();
}


void processor::execute() {
	switch (ir.get_type_code().to_ulong()) {
	case 0b0000:  {
		std::stringstream tmp_strstream;
		tmp_strstream << "00000000" << (ir.get_oper_a_code()).to_string() << (ir.get_oper_b_code()).to_string();
		std::string tmp_string = tmp_strstream.str();
		std::bitset<16> tmp_bit(tmp_string);
		rf.write(destination_index, tmp_bit);
		if (rf.read(destination_index) == 0) 
			zero_flag = true; 
		else 
			zero_flag = false;		
		++ip;
	}
		break;
	case 0b0001: {

		unsigned tmp_addr = op_a_index + op_b_index;
		rf.write(destination_index, data_memory.read(mdr));
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}
		break;
	case 0b0010: {
		data_memory.write(mar, rf.read(destination_index));
		++ip;
	}
		break;
	case 0b0011: {
		std::string string_op_a_index = rf.read(ir.get_oper_a_code().to_ulong()).to_string();
		int op_a = std::stoi(string_op_a_index,nullptr,2);
		std::string string_op_b_index = rf.read(ir.get_oper_b_code().to_ulong()).to_string();
		int op_b = std::stoi(string_op_b_index,nullptr,2);

		int tmp_res = (op_a + op_b) % 65536;
		std::bitset<16> tmp_bitset(tmp_res);
		rf.write(destination_index, tmp_bitset );
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}
		break;
	case 0b0100: {
		unsigned tmp_res = (rf.read(op_a_index).to_ulong() - rf.read(op_b_index).to_ulong()) % 65536;
		std::bitset<16> tmp_bitset(tmp_res);
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}

		break;
	case 0b0101: {
		std::bitset<16> tmp_bitset = rf.read(op_a_index) & rf.read(op_b_index);
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}

		break;
	case 0b0110: {
		std::bitset<16> tmp_bitset = rf.read(op_a_index) | rf.read(op_b_index);
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}

		break;
	case 0b0111: {
		std::bitset<16> tmp_bitset = rf.read(op_a_index) ^ rf.read(op_b_index);
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}

		break;
	case 0b1000: {
		std::bitset<16> tmp_bitset = rf.read(op_a_index) << rf.read(op_b_index).to_ulong();
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}

		break;
	case 0b1001: {
		std::bitset<16> tmp_bitset = rf.read(op_a_index) >> rf.read(op_b_index).to_ulong();
		rf.write(destination_index, tmp_bitset);
		if (rf.read(destination_index) == 0)
			zero_flag = true;
		else
			zero_flag = false;
		if (rf.read(destination_index)[15] == 1)
			negative_flag = true;
		else
			negative_flag = false;
		++ip;
	}
		break;
	case 0b1010: {
		std::stringstream tmp_stream;
		tmp_stream << ir.get_destination_code().to_string() << ir.get_oper_a_code().to_string() << ir.get_oper_b_code().to_string();
		std::string tmp_string = tmp_stream.str();
		std::bitset<12> tmp_bitset(tmp_string);
		if (!zero_flag) ip = ip + tmp_bitset.to_ulong();
		else ++ip;	
	}

		break;
	case 0b1011: {
		std::stringstream tmp_stream;
		tmp_stream << ir.get_destination_code().to_string() << ir.get_oper_a_code().to_string() << ir.get_oper_b_code().to_string();
		std::string tmp_string = tmp_stream.str();
		std::bitset<12> tmp_bitset(tmp_string);
		if (!negative_flag) ip = ip + tmp_bitset.to_ulong();
		else ++ip;
	}

		break;
	case 0b1100: {
		std::stringstream tmp_stream;
		tmp_stream << ir.get_destination_code().to_string() << ir.get_oper_a_code().to_string() << ir.get_oper_b_code().to_string();
		std::string tmp_string = tmp_stream.str();
		std::bitset<12> tmp_bitset(tmp_string);
		ip = ip + tmp_bitset.to_ulong();
	}

		break;
	default: run = false;
	}
}
