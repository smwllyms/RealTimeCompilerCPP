// RTCCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>

//#include "Object.h"
#include "Term.h"
#include "Types.h"
#include "Expression.h"

using namespace std;
using namespace RTC;



int main()
{
    std::ifstream t("TestExpressions.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();

    Term* exp = Expression::ParseAndCreate(buffer.str());
    exp = exp->Evaluate();

    //Term* o = new Term(buffer.str());
    //
    // if (exp->type == INT_T)
    std::cout << exp->toString() << '\n';

}
