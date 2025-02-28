#include <DataLoggerLib.h>
#include <H5Cpp.h>

namespace DataLogger {
	
	unsigned long size(TYPE type){
		switch(type){
			case TYPE::INT:
				return sizeof(int);
			case TYPE::FLOAT:
				return sizeof(float);
			case TYPE::DOUBLE:
				return sizeof(double);
			case TYPE::VOID:
				return 0;
		};
	};


//bool is_dlog(std::filesystem::path path){
//	return (H5::H5File::isHdf5(path) && path.extension() == ".dlog");
//};

//
//bool make(std::filesystem::path path){
//	if(path.extension() != ".dlog") return false;
//	try{
//		H5::H5File file(path,H5F_ACC_TRUNC);
//	}
//	catch(H5::FileIException error){
//		error.printErrorStack();
//		return false;
//	}
//	return true;
//};


}
