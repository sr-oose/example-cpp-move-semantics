#ifndef NONMOVEABLE_H_
#define NONMOVEABLE_H_

#include "Data.h"


struct NonMoveable {
	Data* data;

	NonMoveable() {
		std::cout << "NonMoveable default constructor" << std::endl;
		data = new Data{};
	}

	NonMoveable(const NonMoveable& other) {
		std::cout << "NonMoveable copy constructor" << std::endl;
		data = new Data{*other.data};
	}

	//NonMoveable(NonMoveable&& other) = delete;

	NonMoveable& operator=(const NonMoveable& other) {
		std::cout << "NonMoveable copy assignment" << std::endl;
		*data = *other.data;
		return *this;
	}

	//NonMoveable& operator=(NonMoveable&& other) = delete;

	~NonMoveable() {
		std::cout << "NonMoveable destructor" << std::endl;
		delete data;
	}
};


#endif /* NONMOVEABLE_H_ */
