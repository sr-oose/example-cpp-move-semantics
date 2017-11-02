#include "Data.h"
#include "NonMoveable.h"
#include "Moveable.h"

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
		//Be careful when using "moveable" from here!
		moveable = factory<Moveable>();
		cout << "------Before end of block-------\n";
	}
	return 0;
}
