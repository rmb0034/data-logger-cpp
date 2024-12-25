#include <DataLogger.h>

int main(int argc, char* argv[]){
	DataLogger::FrameDescription description = {
		{"pose", {DataLogger::TYPE::INT, {3}}},
		{"image", {DataLogger::TYPE::FLOAT, {100,100,3}}},
	};
	float****x;

	DataLogger::Buffer buffer(description,100);
} 
