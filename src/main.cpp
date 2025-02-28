#include "H5public.h"
#include "Type.h"
#include <DataLogger.h>
#include <iostream>
#include <H5Cpp.h>

int main(int argc, char* argv[]){
	std::filesystem::path dlog_path ("/home/rmb/test.dlog");  
	//DataLogger::make(dlog_path);

  DataLogger::FrameDescription description = {
  	{"pose", {DataLogger::TYPE::INT, {5}}},
  	{"image", {DataLogger::TYPE::FLOAT, {100,100,3}}},
  	{"depth", {DataLogger::TYPE::DOUBLE, {10,10,3}}},
  };
  
  DataLogger::Logger logger(dlog_path,description,10);
  std::vector<int> v {1,2,3,4,5};

	H5::H5File f{};
	f.close();

	H5close();

  logger.set_to_buffer<DataLogger::TYPE::INT>("pose", v, 0);
	std::vector<int> v2 = logger.get_from_buffer<DataLogger::TYPE::INT>("pose", 0);
  for(const int i : v2) std::cout << i << ' ';
  std::cout << '\n';
} 
