#ifndef H_MEMORY
#define H_MEMORY

//

template < unsigned size, typename item_type >
class memory {

private:

	item_type content[size];

public:

	const item_type& read(unsigned address) const {
		if (address <= size) {
			return content[address];
		}
		else throw ("Memory access error: invalid read address");
	}

	void write(const unsigned address, const item_type& data_in) {
		if (address <= size) {
			content[address] = data_in;
		}
		else throw ("Memory access error: invalid write address");
	}

};


#endif 

