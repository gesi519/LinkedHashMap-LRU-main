#ifndef SJTU_INTEGER_HPP
#define SJTU_INTEGER_HPP

class Integer {
public:
	static int counter;
	int val;
	
	Integer(int val) : val(val) {counter++;}
	~Integer() {counter--;}

	Integer(const Integer &rhs) {
		val = rhs.val;
		counter++;
	}

	bool operator==(const Integer &rhs){
		return val == rhs.val;
	}
};

int Integer::counter = 0;

#endif