#include "string"
#include "Types.h"
#include "Term.h"

#include "iostream"

using namespace std;
using namespace RTC;

Term::Term(string s) {
	int i = 0, len = s.length(), j = len - 1;
	cout << "Term:";
	cout << s;
	cout << "\n";
	// Remove extra parentheses
	while (i == '(') i++;
	while (j == ')') j--;
	bool isNumber = isdigit(s[0]);
	bool isFloat = s.find('f') != string::npos;
	bool isDouble = s.find('.') != string::npos;

	bool isString = s.find('\"') != string::npos;
	bool isChar = s.find('\'') != string::npos;

	if (isNumber) {
		if (isFloat) {
			data = new float(stof(s));
			type = FLOAT_T;
		}
		else if (isDouble) {
			data = new double(stod(s));
			type = DOUBLE_T;
		}
		else {
			data = new int(stoi(s));
			type = INT_T;
		}
	}
	else {
		if (isString) {
			data = new string(s.replace(s.begin(), s.end(), "\"", ""));
			type = STRING_T;
		}
		else if (isChar) {
			data = new char(s.replace(s.begin(), s.end(), "\'", "")[0]);
			type = CHAR_T;
		}
		else {
			throw new exception("RTC - Invalid Parsed Type");
		}
	}
}
Term* Term::Evaluate() {
	return new Term(this);
}

string Term::toString() {
	stringstream str;
	switch (type) {
	case INT_T: {
		str << "{int:" << (int)*this << "}";
		break;
	}
	case FLOAT_T: {
		str << "{float:" << (float)*this << "}";
		break;
	}
	case DOUBLE_T: {
		str << "{double:" << (double)*this << "}";
		break;
	}
	case STRING_T: {
		str << "{string:" << (string)*this << "}";
		break;
	}
	case CHAR_T: {
		str << "{char:" << (char)*this << "}";
		break;
	}
	case VAR_T: {
		str << "{var:(" << (string)*this << ")}";
		break;
	}
	default:
		str << "{}";
		break;
	}
	return str.str();
}