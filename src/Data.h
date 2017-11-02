#ifndef DATA_H_
#define DATA_H_

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


#endif /* DATA_H_ */
