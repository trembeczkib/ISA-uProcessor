#ifndef H_UPROC
#define H_UPROC

#include "inst.h"
#include "memory.h"
#include <bitset>

class processor {
public:
    processor(memory<1024, instruction>& program_memory, memory<1024, std::bitset<16>>& data_memory);
    void run_program();
    void print_state();
	memory<1024, std::bitset<16>>& data_memory;
private:
    const memory<1024, instruction>& program_memory;
    instruction ir;
    unsigned ip;
    memory<16, std::bitset<16>> rf;
    unsigned destination_index;
    int op_a_index;
    int op_b_index;
    unsigned mar;  // memory address register
    unsigned mdr;	// memory data register
    bool zero_flag;
    bool negative_flag;
    bool run;

    void fetch();
    void decode();
    void execute();
};


#endif

