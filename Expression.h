#pragma once

#include "Term.h"

//class Expression : Term {
//public:
//	Term* left;
//	Term* right;
//	char operation;
//	Expression(Term* l, Term* r, char op);
//};
//
//static Term* FindExpression(string expression, int start, int end);
//Term* ParseExpression(string exp);

namespace RTC {
    class Expression : Term {
    public:
        Expression(Term* left, Term* right, char operation);
        ~Expression() { delete left; delete right; }

        Term* Evaluate(/*Context context*/);

        static Term* ParseAndCreate(string expression);
        static string Parse(string expression);
        static Term* TryCreate(string expression);

        virtual string toString();

        static const int TOP_PRIORITY = 1;
        Term* left;
        Term* right;
        char operation;
    };
}