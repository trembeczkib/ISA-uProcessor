#ifndef H_INST
#define H_INST

#include <bitset>

class instruction {
	public:
		instruction();
		instruction(const std::bitset<4>& type_code, const std::bitset<4>& destination_code, const std::bitset<4>& oper_a_code, const std::bitset<4>& oper_b_code);
		instruction::instruction(const int& type_code, const int& destination_code, const int& oper_a_code, const int& oper_b_code);
		instruction(const instruction& source);
		void set_type_code(const std::bitset<4>& typecode);
		void set_destination_code(const std::bitset<4>& destination);
		void set_oper_a_code(const std::bitset<4>& operand_a);
		void set_oper_b_code(const std::bitset<4>& operand_b);
		const std::bitset<4>& get_type_code() const;
		const std::bitset<4>& get_destination_code() const;
		const std::bitset<4>& get_oper_a_code() const;
		const std::bitset<4>& get_oper_b_code() const;
		void print() const;
		void operator = (const instruction& other);
		bool operator == (const instruction& other);
		std::ostream &operator << (std::ostream &str);

	private:
		std::bitset<4> type_code;
		std::bitset<4> destination_code;
		std::bitset<4> oper_a_code;
		std::bitset<4> oper_b_code;

};




#endif

