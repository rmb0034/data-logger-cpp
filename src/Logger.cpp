#include <Logger.h>
#include <numeric>

namespace DataLogger{

	Logger::Logger(const std::filesystem::path path, DataLogger::FrameDescription & description,const size_t len) :
		buffer_(description,len), len_(len){
			for(const auto & [name,info] : description){
				item_sizes_.emplace(name,std::accumulate(info.second.begin(),info.second.end(),1,std::multiplies<int>()));
			};
		};

	template <TYPE T>
	void Logger::set_to_buffer(const std::string & name, std::vector<typename CPP_TYPE<T>::type> & data, size_t ind){
		size_t & len = item_sizes_.at(name);
		if(data.size() != len) throw std::length_error("Incorrect data size");
		buffer_.set<T>(name,data,ind*len);
	};
	
	template <TYPE T>
	std::vector<typename CPP_TYPE<T>::type> Logger::get_from_buffer(const std::string & name, size_t ind){
		size_t & len = item_sizes_.at(name);
		return buffer_.get<T>(name,ind*len,len);
	};

	template std::vector<typename CPP_TYPE<TYPE::INT>::type> Logger::get_from_buffer<TYPE::INT>(const std::string&, size_t);
	template std::vector<typename CPP_TYPE<TYPE::FLOAT>::type> Logger::get_from_buffer<TYPE::FLOAT>(const std::string&, size_t);
	template std::vector<typename CPP_TYPE<TYPE::DOUBLE>::type> Logger::get_from_buffer<TYPE::DOUBLE>(const std::string&, size_t);

	template void Logger::set_to_buffer<TYPE::INT>(const std::string & name, std::vector<typename CPP_TYPE<TYPE::INT>::type> & data, size_t ind);
	template void Logger::set_to_buffer<TYPE::FLOAT>(const std::string & name, std::vector<typename CPP_TYPE<TYPE::FLOAT>::type> & data, size_t ind);
	template void Logger::set_to_buffer<TYPE::DOUBLE>(const std::string & name, std::vector<typename CPP_TYPE<TYPE::DOUBLE>::type> & data, size_t ind);

};
