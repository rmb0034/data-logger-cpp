
#ifndef DATALOGGER_TYPE_H
#define DATALOGGER_TYPE_H


namespace DataLogger{

	enum class TYPE : unsigned long {
		INT,
		FLOAT,
		DOUBLE,
		VOID
	};

	template <typename T>
	struct DL_TYPE{
		static constexpr TYPE type = TYPE::VOID;
	};
	
	template <TYPE T>
	struct CPP_TYPE{
		using type = void;
	};

	template <>
	struct DL_TYPE<int>{
		static constexpr TYPE type = TYPE::INT;
	};
	
	template <>
	struct DL_TYPE<float>{
		static constexpr TYPE type = TYPE::FLOAT;
	};

	template <>
	struct DL_TYPE<double>{
		static constexpr TYPE type = TYPE::DOUBLE;
	};

	template <>
	struct CPP_TYPE<TYPE::INT>{
		using type = int;
	};

	template <>
	struct CPP_TYPE<TYPE::FLOAT>{
		using type = float;
	};

	template <>
	struct CPP_TYPE<TYPE::DOUBLE>{
		using type = double;
	};

}

#endif
