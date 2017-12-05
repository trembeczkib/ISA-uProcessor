#include <iostream>
#include <bitset>
#include "inst.h"
#include "memory.h"
#include "uproc.h"
#include "generate_test.hpp"

int main() {

	memory<1024, instruction> pmem;			//initialise program memory
	testprogram_1(pmem);					//generate test program
	memory<1024, std::bitset<16>> dmem;		//initialise data memory

	for (unsigned i = 0; i < 101; ++i) {	//fill data memory with some data
		std::bitset<16> temp(i);
		dmem.write(i, temp);
	}

	std::bitset<16> temp(-5);				//fill data memory with some other data
	dmem.write(101, temp);
	
	processor p(pmem, dmem);				//initialise processor with pmem and dmem

	p.run_program();						//run the test program from pmem

	getchar();
	return 0;
}