#include <iostream>

struct Data {
	int value {42};
	static int instances;

	Data(){
		Data::instances++;
		std::cout << "Data created" << std::endl;
	}

	~Data(){
		Data::instances--;
		std::cout << "Data destroyed" << std::endl;
	}

	Data(const Data&) : Data(){	}
	Data(Data&&) : Data(){ }
	Data& operator=(const Data& other) = default;
	Data& operator=(Data&& other) = default;
};

int Data::instances {0};

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

template<typename T> T returnByValue(T t){
	std::cout << "-> returnByValue(T) called" << std::endl;
	return t;
}

template<typename T> T factory(){
	std::cout << "-> factory() called" << std::endl;
	return T{};
}


using namespace std;

int main(int argc, char** argv){

	cout << "====Without move constructor====\n";
	{
		NonMoveable nonMoveable{};
		NonMoveable nonMoveable2 = returnByValue(nonMoveable);
		nonMoveable = nonMoveable2;
		nonMoveable = factory<NonMoveable>();
		cout << "------Before end of block-------\n";
	}
	cout << "====With move constructor====\n";
	{
		Moveable moveable{};
		Moveable moveable2 = returnByValue(moveable);
		moveable = factory<Moveable>();
		cout << "------Before end of block-------\n";
	}
	cout << "====Forcing move for function call====\n";
	{
		Moveable moveable{};
		Moveable moveable2 = returnByValue(std::move(moveable));
		//Do not use variable "moveable" anymore!
		moveable = factory<Moveable>();
		cout << "------Before end of block-------\n";
	}
	return 0;
}
