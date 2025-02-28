#ifndef DATALOGGER_LOGGER_H
#define DATALOGGER_LOGGER_H

#include <Type.h>
#include "Buffer.h"
#include <cstdio>
#include <filesystem>

namespace DataLogger {
	class Logger{
	public:
		Logger(const std::filesystem::path path, DataLogger::FrameDescription & description,const size_t len);
		void load(size_t ind);
		void write(size_t ind);

		template <TYPE T>
		void set_to_buffer(const std::string & name, std::vector<typename CPP_TYPE<T>::type> & data, size_t ind);
		
		template <TYPE T>
		std::vector<typename CPP_TYPE<T>::type> get_from_buffer(const std::string & name, size_t ind);

	private:
		Buffer buffer_;
		size_t len_;
		std::unordered_map<std::string,size_t> item_sizes_;  
	};

}

#endif
