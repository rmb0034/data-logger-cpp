#include "Buffer.h"
#include "Type.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <iostream>

namespace DataLogger {

	Buffer::Buffer(const FrameDescription & desc,const size_t len){
		size_t memory_size_full = 0;
		for(const auto & [name,info] : desc){
			const auto & [type,dims] = info;
			size_t memory_size = len*std::accumulate(dims.begin(),dims.end(),1,std::multiplies<int>());
			buffer_.emplace(name, Item{type,dims,memory_size,size(type)});
			memory_size_full += memory_size;
		};

		data_ = calloc(memory_size_full,1);
		int last_len = 0;
		for(auto & [name,item] : buffer_){
			item.begin = (char*)data_ + last_len;
			last_len = item.size*item.len;
			item.end = (char*)data_ + last_len;
		};

	};

	Buffer::~Buffer(){
		free(data_);
	};

	template <TYPE T>
	void Buffer::set(const std::string & name, const std::vector<typename CPP_TYPE<T>::type> & data, size_t ind){
		Buffer::Item & item = buffer_.at(name);

		if(data.size() + ind > item.len) throw std::length_error("Indexed out of bounds memory");
		if(item.type == T) std::memcpy(item[ind], &(*data.begin()),data.size()*item.size);

		for(int i = 0; i < data.size(); i++) cast_to_dlog(item.type,data[i],item[ind+i]);
	};

	template <TYPE T>
	std::vector<typename CPP_TYPE<T>::type> Buffer::get(const std::string & name, size_t ind, size_t len){
		Buffer::Item & item = buffer_.at(name);
		if(len == std::numeric_limits<size_t>::max()) len = item.len;
		if(item.type == T) return std::vector<typename CPP_TYPE<T>::type>(
		 	static_cast<typename CPP_TYPE<T>::type*>(item.begin)+ind,
		 	static_cast<typename CPP_TYPE<T>::type*>(item.end));
		std::vector<typename CPP_TYPE<T>::type> temp(len);
		for(int i = 0; i < len; i++){
		 cast_from_dlog(item.type,item[ind+i],temp[i]);	
		}
		return temp;
	};

	template std::vector<CPP_TYPE<TYPE::INT>::type> Buffer::get<TYPE::INT>(const std::string & name, size_t ind, size_t len);
	template std::vector<CPP_TYPE<TYPE::DOUBLE>::type> Buffer::get<TYPE::DOUBLE>(const std::string & name, size_t ind, size_t len);
	template std::vector<CPP_TYPE<TYPE::FLOAT>::type> Buffer::get<TYPE::FLOAT>(const std::string & name, size_t ind, size_t len);

	template void Buffer::set<TYPE::INT>(const std::string & name, const std::vector<typename CPP_TYPE<TYPE::INT>::type> & data, size_t ind);
	template void Buffer::set<TYPE::DOUBLE>(const std::string & name, const std::vector<typename CPP_TYPE<TYPE::DOUBLE>::type> & data, size_t ind);
	template void Buffer::set<TYPE::FLOAT>(const std::string & name, const std::vector<typename CPP_TYPE<TYPE::FLOAT>::type> & data, size_t ind);
}

