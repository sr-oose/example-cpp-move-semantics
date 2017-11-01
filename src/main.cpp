#include <iostream>

struct Data {
	int value {42};

	Data(){
		std::cout << "Data created" << std::endl;
	}

	~Data(){
		std::cout << "Data destroyed" << std::endl;
	}

	Data(const Data&) : Data(){	}
	Data(Data&&) : Data(){ }
	Data& operator=(const Data& other) = default;
	Data& operator=(Data&& other) = default;
};


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
	bool invalid = false;

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
		other.invalid = true;
	}

	Moveable& operator=(const Moveable& other) {
		std::cout << "Moveable copy assignment" << std::endl;
		*data = *other.data;
		return *this;
	}

	Moveable& operator=(Moveable&& other){
		std::cout << "Moveable move assignment" << std::endl;
		data = other.data;
		other.invalid = true;
		return *this;
	}

	~Moveable() {
		std::cout << "Moveable destructor" << std::endl;
		if (!invalid) delete data;
	}
};

template<typename T> T returnByValue(T t){
	return t;
}

using namespace std;

int main(int argc, char** argv){
	cout << "====Without move constructor====\n";
	{
	NonMoveable nonMoveable{};
	NonMoveable nonMoveable2 = returnByValue<NonMoveable>(nonMoveable);
	}
	cout << "====With move constructor====\n";
	{
	Moveable moveable{};
	Moveable moveable2 = returnByValue<Moveable>(moveable);
	}
	cout << "====Forcing move for function call====\n";
	{
	Moveable moveable{};
	Moveable moveable2 = returnByValue<Moveable>(std::move(moveable));
	//Do not use variable "moveable" anymore!
	}
	return 0;
}
