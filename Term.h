#pragma once
#include "string"
#include "Types.h"
#include "iostream"
#include "sstream"

using namespace std;

namespace RTC {
	class Term {
	public:
		void* data;
		Type type;
		Term() { type = INT_T; data = nullptr; }
		Term(void* data, Type type) {
			this->data = data; this->type = type;  }
		Term(string s);
		Term(Term* term) { this->data = term->data; this->type = term->type; }

		~Term() { delete data; }

		virtual Term* Evaluate();
		virtual string toString();

		// Oh boy...
		operator int() {
			switch (type) {
			case INT_T:
				return static_cast<int>(*(int*)data);
			case FLOAT_T:
				return static_cast<int>(*(float*)data);
			case DOUBLE_T:
				return static_cast<int>(*(double*)data);
			case CHAR_T:
				return static_cast<int>(*(char*)data);
			default:
				throw exception("RTC Error: Cast exception");
			}
		}
		operator float() {
			switch (type) {
			case INT_T:
				return static_cast<float>(*(int*)data);
			case FLOAT_T:
				return static_cast<float>(*(float*)data);
			case DOUBLE_T:
				return static_cast<float>(*(double*)data);
			case CHAR_T:
				return static_cast<float>(*(char*)data);
			default:
				throw exception("RTC Error: Cast exception");
			}
		}
		operator double() {
			switch (type) {
			case INT_T:
				return static_cast<double>(*(int*)data);
			case FLOAT_T:
				return static_cast<double>(*(float*)data);
			case DOUBLE_T:
				return static_cast<double>(*(double*)data);
			case CHAR_T:
				return static_cast<double>(*(char*)data);
			default:
				throw exception("RTC Error: Cast exception");
			}
		}
		operator char() {
			char val = *(char*)data;
			if (type == CHAR_T)
				return val;
			else {
				throw exception("RTC Error: Cast exception");
			}
		}
		operator string() {
			switch (type) {
			case STRING_T:
				return *(string*)data;
			case INT_T:
				return to_string(*(int*)data);
			case FLOAT_T:
				return to_string(*(float*)data);
			case DOUBLE_T:
				return to_string(*(double*)data);
			case CHAR_T:
				return to_string(*(char*)data);
			default:
				throw exception("RTC Error: Cast exception");
			}
		}

	};
}
