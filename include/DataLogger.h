#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <cstddef>
#include <hdf5/serial/H5Cpp.h>
#include <vector>
#include <unordered_map>


namespace DataLogger {

	enum class TYPE {
		INT,
		FLOAT
	};

	struct frame_item{
		TYPE type;
		std::vector<int> dims;
	};

	typedef std::unordered_map<std::string,frame_item> frame;


	void make(std::string filepath);
	class Logger{
	public:
		Logger(std::string filepath);
	};


	class Buffer{
		public: 
			Buffer(frame frame, int rank);
			~Buffer();
			frame get_frame(int ind);
		private:
			void init_buffer_(const std::string & name, const frame_item & item);
			void* init_data_(TYPE type, size_t size);
			void delete_data_(TYPE type, const void* data);
			template <typename T>
			std::vector<T> get_data_(void* begin, int size);
			std::unordered_map<std::string, const void*> buffer_;
			frame frame_;
			size_t frame_size_;
			int rank_;
	};
}

#endif
