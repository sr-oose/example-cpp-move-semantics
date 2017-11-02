#ifndef MOVEABLE_H_
#define MOVEABLE_H_

#include "Data.h"

struct Moveable {
	Data* data;
	bool dataIsExternal = false;

	Moveable(){
		std::cout << "Moveable default constructor" << std::endl;
		data = new Data{};
	}

	Moveable(const Moveable& other){
		std::cout << "Moveable copy constructor" << std::endl;
		data = new Data{*other.data};
	}

	Moveable(Moveable&& other){
		std::cout << "Moveable move constructor" << std::endl;
		data = other.data;
		other.dataIsExternal = true;
	}

	Moveable& operator=(const Moveable& other) {
		std::cout << "Moveable copy assignment" << std::endl;
		*data = *other.data;
		dataIsExternal = false;
		return *this;
	}

	Moveable& operator=(Moveable&& other){
		std::cout << "Moveable move assignment" << std::endl;
		if (!dataIsExternal) delete data;
		data = other.data;
		other.dataIsExternal = true;
		dataIsExternal = false;
		return *this;
	}

	~Moveable() {
		std::cout << "Moveable destructor" << std::endl;
		if (!dataIsExternal) delete data;
	}
};


#endif /* MOVEABLE_H_ */
