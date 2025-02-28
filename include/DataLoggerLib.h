#ifndef DATALOGGER_LIB_H
#define DATALOGGER_LIB_H

#include "Type.h"
#include <cstdlib>
#include <filesystem>

namespace DataLogger{

	template <typename T>
	void cast_to_dlog(TYPE type,const T & src,void* dest){
		switch(type){
			case TYPE::INT:
				*static_cast<int*>(dest) = (int)src;
				return ;
			case TYPE::FLOAT:
				*static_cast<float*>(dest) = (float)src;
				return;
			case TYPE::DOUBLE:
				*static_cast<double*>(dest) = (double)src;
				return;
			case TYPE::VOID:
				return ;
		};
	};

	template <typename T>
	void cast_from_dlog(TYPE type,const void* src, T & dest){
		switch(type){
			case TYPE::INT:
				dest = *(int*)src;
				return ;
			case TYPE::FLOAT:
				dest = *(float*)src;
				return;
			case TYPE::DOUBLE:
				dest = *(double*)src;
				return;
			case TYPE::VOID:
				return ;
		};
	};

	unsigned long size(TYPE type);

	bool is_dlog(std::filesystem::path path);

	bool make(std::filesystem::path path);

}

#endif
