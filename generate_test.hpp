#ifndef H_TESTPROGRAM
#define H_TESTPROGRAM

// Data memory filled,	on dm[0:100]	dm[i]		=	i
//						on dm[101]		dm[100]		=	-5

void testprogram_1(memory<1024, instruction>& program_memory) {

// i2rfl test(s)
	program_memory.write(0, instruction(0b0000, 0b0000, 0b1010, 0b1010));  //immediate load "10101010" to rf[0] rf[0] :=0000000010101010 , z := 0
	program_memory.write(1, instruction(0b0000, 0b0000, 0b0101, 0b0101));  //immediate load "01010101" to rf[0] rf[0] :=0000000001010101 , z := 0
	program_memory.write(2, instruction(0b0000, 0b0001, 0b0000, 0b0000));  //immediate load "00000000" to rf[1] rf[1] :=0000000000000000 , z := 1
	program_memory.write(3, instruction(0b0000, 0b0010, 0b0110, 0b0100));  //immediate load "01100100" to rf[2] rf[2] :=0000000001100100 , z := 0
//load test(s)	
	program_memory.write(4, instruction(0b0001, 0b0010, 0b0000, 0b0101));  //load dmem[5]		to rf[2] 	rf[2] :=0000000000000101 (5) , z := 0, n := 0
	program_memory.write(5, instruction(0b0001, 0b0011, 0b0000, 0b0110));  //load dmem[6]		to rf[3] 	rf[3] :=0000000000000110 (6) , z := 0, n := 0
	program_memory.write(6, instruction(0b0001, 0b0100, 0b0000, 0b0111));  //load dmem[7]		to rf[4] 	rf[4] :=0000000000000111 (7) , z := 0, n := 0
	program_memory.write(7, instruction(0b0001, 0b0101, 0b0011, 0b0001));  //load dmem[50]		to rf[5] 	rf[5] :=0000000000110001 (50) , z := 0, n := 0
	program_memory.write(8, instruction(0b0001, 0b0110, 0b0110, 0b0101));  //load dmem[101]		to rf[6] 	rf[6] :=1111111111111011 (-5) , z := 0, n := 1
//store test(s)
	program_memory.write(9, instruction(0b0010, 0b0110, 0b0110, 0b0110));  //store rf[6]			to dmem[102] dmem[102] :=1111111111111011 (-5)
//add test(s)
	program_memory.write(10, instruction(0b0011, 0b0111, 0b0010, 0b0011));	//store add(rf[2] + rf[3]) to rf[7] rf[7] := 0000000000001011  (11) z := 0, n := 0
	program_memory.write(11, instruction(0b0011, 0b0111, 0b0010, 0b0100));	//store add(rf[2] + rf[4]) to rf[7] rf[7] := 0000000000001100  (12) z := 0, n := 0
	program_memory.write(12, instruction(0b0011, 0b0001, 0b0001, 0b0001));  //store add(rf[1] + rf[1]) to rf[1] rf[1] := 0000000000000000  (0)  z := 1, n := 0
//sub test(s)
	program_memory.write(13, instruction(0b0100, 0b0000, 0b0111, 0b0010));  //store sub(rf[7] - rf[2]) to rf[0] rf[0] := 0000000000000111  (7)  z := 0, n := 0
//and test(s)
	program_memory.write(14, instruction(0b0101, 0b0001, 0b0001, 0b0000));  //store and(rf[1] & rf[0])  to rf[1] rf[1] := 0000000000000000  (rf[1]) z := 1, n := 0
	program_memory.write(15, instruction(0b0101, 0b0001, 0b0101, 0b0110));  //store and(rf[5] & rf[6])  to rf[1] rf[1] := 0000000000110001			z := 0, n := 0
//or test(s)
	program_memory.write(16, instruction(0b0110, 0b0001, 0b0001, 0b0000));  //store or(rf[1] | rf[0])  to rf[1] rf[1] := 0000000000110111			z := 0, n := 0
	program_memory.write(17, instruction(0b0110, 0b0001, 0b0101, 0b0110));  //store or(rf[5] | rf[6])  to rf[1] rf[1] := 1111111111111011			z := 0, n := 0
//xor test(s)
	program_memory.write(18, instruction(0b0111, 0b0010, 0b0001, 0b0000));  //store or(rf[1] ^ rf[0])  to rf[2] rf[2] := 1111111111111100			z := 0, n := 0
	program_memory.write(19, instruction(0b0111, 0b0010, 0b0101, 0b0110));  //store or(rf[5] ^ rf[6])  to rf[2] rf[2] := 1111111111001010			z := 0, n := 0
//shl test(s)
	program_memory.write(20, instruction(0b1000, 0b0010, 0b0011, 0b0000));  //store or(rf[3] << rf[0])  to rf[2] rf[2] := 0000001100000000			z := 0, n := 0
	program_memory.write(21, instruction(0b1000, 0b0011, 0b0101, 0b0110));  //store or(rf[5] << rf[6])  to rf[3] rf[3] := 0000000000000000			z := 1, n := 0
//shr test(s)
	program_memory.write(22, instruction(0b1001, 0b0010, 0b0001, 0b0000));  //store or(rf[1] >> rf[0])  to rf[2] rf[2] := 0000000111111111			z := 0, n := 0
	program_memory.write(23, instruction(0b1001, 0b0011, 0b0101, 0b0110));  //store or(rf[5] >> rf[6])  to rf[3] rf[3] := 0000000000000000			z := 1, n := 0
//bnz test(s)
	program_memory.write(24, instruction(0b1010, 0b0000, 0b0001, 0b1111));  // z = 1 => ++p
		program_memory.write(25, instruction(0b0000, 0b0000, 0b1010, 0b1010));  //immediate load "10101010" to rf[0] rf[0] :=0000000010101010 , z := 0
	program_memory.write(26, instruction(0b1010, 0b0000, 0b0001, 0b1101));	// z = 0 => p=p+29 (55)
//bnn test(s)
	program_memory.write(56, instruction(0b1011, 0b0000, 0b0000, 0b1010));	// n = 0 => p=p+10 (66)
//jmp test(s)
	program_memory.write(67, instruction(0b1100, 0b0000, 0b0000, 0b1010));	// n = 0 => p=p+10 (77)
	program_memory.write(78, instruction(0b1100, 0b0000, 0b0001, 0b0110));	// p=p+10 (100)


	program_memory.write(55, instruction(0b0000, 0b0000, 0b1100, 0b1100));
	program_memory.write(66, instruction(0b0000, 0b0000, 0b0011, 0b1100));
	program_memory.write(77, instruction(0b0000, 0b0000, 0b0011, 0b0011));

	program_memory.write(100, instruction(0b1111, 0b0110, 0b0110, 0b0101)); //load dmem[101]		to rf[6] 	rf[6] :=0000000000000111 (7) , z := 0, n := 1

}

#endif 
