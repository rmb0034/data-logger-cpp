
#ifndef DATALOGGER_BUFFER_H
#define DATALOGGER_BUFFER_H

#ifndef DATALOGGER_LIB_H
#include "DataLoggerLib.h"
#endif

#include "Type.h"
#include <cstring>
#include <cstddef>
#include <unordered_map>
#include <string>
#include <vector>

namespace DataLogger{

	typedef const std::unordered_map<std::string, std::pair<TYPE,std::vector<int>>> FrameDescription;

	class Buffer{
	public:
		Buffer(FrameDescription & desc, const size_t len);
		~Buffer();

		template <TYPE T>
		void set(const std::string & name, const std::vector<typename CPP_TYPE<T>::type> & data, size_t ind);

		template <TYPE T>
		std::vector<typename CPP_TYPE<T>::type> get(const std::string & name, size_t ind, size_t len);

	private:

		struct Item{
			TYPE type;
			std::vector<int> dims;
			size_t len;
			size_t size;
			void* begin = nullptr;
			void* end = nullptr;
			void* operator[](size_t i){
				return static_cast<char*>(begin) + i*size;
			};
		};

		std::unordered_map<std::string,Item> buffer_;
		void* data_;
	};

}

#endif
