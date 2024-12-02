#include <DataLogger.h>


namespace DataLogger {
	Buffer::Buffer(frame frame,int rank) : frame_(frame){
		for(const auto & [name,frame_i] : frame){
			init_buffer_(name,frame_i);
		}
	}

	Buffer::~Buffer(){
		for(const auto & [name,frame_i] : frame_){
			delete_data_(frame_i.type, buffer_[name]);
		}
	}

	frame Buffer::get_frame(int ind){
		frame res;
		for(const auto & [name,data] : buffer_){
			switch (frame_[name].type) {
				case TYPE::FLOAT:
					res.emplace(name,);
				case TYPE::INT:
					res.emplace(name,get_data_<int>(const_cast<void*>(data),10));
			}
		};
		return res;
	};


	void Buffer::init_buffer_(const std::string & name, const frame_item & item){
		auto dims_iter = item.dims.begin();

		size_t size = 1;
		while(dims_iter != item.dims.end()) size *= *(dims_iter++);
		frame_size_ = size;
		size *= rank_;
		
		buffer_.emplace(name,init_data_(item.type,size));
	}

	void Buffer::delete_data_(TYPE type,const void* data){
		switch (type) {
			case TYPE::FLOAT:
				delete[] static_cast<const float*>(data);
				break;
			case TYPE::INT:
				delete[] static_cast<const int*>(data);
				break;
		}
	}

	void* Buffer::init_data_(TYPE type, size_t size){
		switch (type) {
			case TYPE::FLOAT:
				return new float[size]; 
			case TYPE::INT:
				return new int[size]; 
		}
	}

	template <typename T>
	std::vector<T> Buffer::get_data_(void* begin, int size){
		return std::vector<T>(static_cast<T*>(begin),static_cast<T*>(begin)+size); 
	}
}
