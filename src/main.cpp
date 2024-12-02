#include <DataLogger.h>
#include <iostream>


int main(int argc, char* argv[]){
	DataLogger::frame frame = {
		{"pose", {DataLogger::TYPE::INT, {3}}},
		{"image", {DataLogger::TYPE::FLOAT, {100,100,3}}},
	};

	DataLogger::Buffer buffer(frame,100);
	DataLogger::frame f = buffer.get_frame(0);
//for(int i : f["pose"].dims){
//	std::cout << i;
//};
}
