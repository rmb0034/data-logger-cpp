#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <cstddef>
#include <unordered_map>
#include <string>
#include <vector>

namespace DataLogger{
	enum class TYPE{
		INT,
		FLOAT
	};

	typedef std::unordered_map<std::string, std::pair<TYPE,std::vector<int>>> FrameDescription;


	class Buffer{
	public:
		Buffer(FrameDescription & desc, size_t len);
		~Buffer();
	private:
		struct Item{
			TYPE type;
			void* ptr;
			std::vector<int> dims;
			size_t len;
		};
		std::unordered_map<std::string,Item> buffer_;
		void* data_;
	};
}
#endif
