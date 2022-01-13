#pragma once

namespace RTC {
	typedef enum {
		INT_T = 1,
		FLOAT_T = 2,
		DOUBLE_T = 3,
		STRING_T = 4,
		CHAR_T = 5,
		VAR_T = 6,
		EXPR_T = 7
	} Type;

	const Type Types[] = {
		INT_T,
		FLOAT_T,
		DOUBLE_T,
		STRING_T,
		CHAR_T,
		VAR_T,
		EXPR_T
	};

	static const char* TypeFromStr(Type t) {
		switch (t)
		{
		case INT_T:
			return "int";
		case FLOAT_T:
			return "float";
		case DOUBLE_T:
			return "double";
		case STRING_T:
			return "string";
		case CHAR_T:
			return "char";
		case VAR_T:
			return "var";
		case EXPR_T:
			return "expression";
		default:
			return "";
		}
	}
}