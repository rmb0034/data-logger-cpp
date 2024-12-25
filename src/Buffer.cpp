#include "DataLogger.h"
#include <cstddef>
#include <functional>
#include <numeric>
#include <iostream>

DataLogger::Buffer::Buffer(FrameDescription & desc, size_t len){
	size_t memory_size_full = 0;
	for(const auto & [name,info] : desc){
		const auto & [type,dims] = info;
		size_t memory_size = len*std::accumulate(dims.begin(),dims.end(),1,std::multiplies<int>());
		buffer_.emplace(name,Item {type,nullptr,dims,memory_size});
		memory_size_full += memory_size;
	};
	std::cout << sizeof(buffer_);
	data_ = malloc(memory_size_full);

	int last_len = 0;
	for(auto & [name,item]: buffer_){
		item.ptr = (char*)data_ + last_len;
		last_len = item.len;
	};
};

DataLogger::Buffer::~Buffer(){
	free(data_);
};
