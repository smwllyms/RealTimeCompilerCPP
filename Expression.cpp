#include "Expression.h"
#include "iostream"

using namespace RTC;

inline bool isSpace(char c) { return c == ' ' || c == '\t'; }
//
//inline bool isOperation1(char c) {
//	return c == '*' || c == '/';
//}
//inline bool isOperation0(char c) {
//	return c == '+' || c == '-';
//}
//inline bool isOperation(char c, int level) {
//	if (level == -1)
//		return isOperation0(c) || isOperation1(c);
//	else if (level == 1)
//		return isOperation1(c);
//	else
//		return isOperation0(c);
//}
//
//Expression::Expression(Term* l, Term* r, char op) {
//	left = l;
//	right = r;
//	operation = op;
//}
//
//Term* FindExpression(string expression, int start, int end) {
//	int level = 0, level2 = 0, i = start, j = 0;
//	printf("Expression:{%s}\n", expression.substr(start, end - start + 1).c_str());
//	//printf("%d, %d", start, end);
//	//printf("Expression:{%s}\n", expression.c_str());
//	char c = 0;
//	while (true) {
//		//printf("%d, %d\n", i, j);
//		// Find first operation from right
//		while (i < end && !isOperation(c = expression[i], 0)) {
//			if (c == '(')
//				level++;
//			else if (c == ')')
//				level--;
//			i++;
//		}
//		// No operation found = term
//		if (i == end)
//			break;
//		// We found an operation
//		// Come from right and see if levels match;
//		level2 = 0;
//		j = end - 1;
//		while (j >= start && !isOperation(c = expression[j], 0)) {
//			if (c == '(')
//				level2--;
//			else if (c == ')')
//				level2++;
//			j--;
//		}
//		// Check if equal levels
//		//printf("%d, %d\n", level, level2);
//		if (level == level2)
//			break;
//		// Otherwise find next
//		j--;
//	}
//	// If term
//	if (i == end) {
//		// trim parentheses
//		j = start;
//		while (expression[j] == '(') {
//			start++;
//			end--;
//			j++;
//		}
//		return new Term(expression.substr(start, end-start+1));
//	}
//
//	int opIdx = i, oldEnd = end;
//	j = i + 1;
//	i = i - 1;
//	// Trim interior space
//	while (isSpace(expression[i]))
//		i--;
//	while (isSpace(expression[j]))
//		j++;
//	start = i;
//	end = j;
//	level2 = 0;
//	// Remove parentheses if (they exist)
//	if (expression[start] == ')') {
//		while (start >= 0) {
//			if (expression[start] == ')')
//				level2++;
//			else if (expression[start] == '(')
//				level2--;
//			if (level2 == 0)
//				break;
//			start--;
//		}
//	}
//	else {
//		// TODO account for functions
//		while (start >= 0 && !isOperation(expression[start], -1) && expression[start] != '(')
//			start--;
//	}
//	start++;
//	// Remove parentheses if (they exist)
//	if (expression[end] == '(') {
//		while (end < oldEnd) {
//			if (expression[end] == ')')
//				level2++;
//			else if (expression[end] == '(')
//				level2--;
//			if (level2 == 0)
//				break;
//			end++;
//		}
//		end++;
//	}
//	else {
//		// TODO account for functions
//		while (end < oldEnd && !isOperation(expression[end], -1) && expression[end] != ')')
//			end++;
//	}
//	end--;
//	/*printf("Left Expression:{%s}\n", expression.substr(start, i - start+1).c_str());
//	printf("Right Expression:{%s}\n", expression.substr(j, end - j).c_str());*/
//
//	return (Term*) new Expression(FindExpression(expression, start, i), FindExpression(expression, j, end), c);
//}
//
//	Term* ParseExpression(string exp) {
//		// Remove leading and trailing whitespace
//		int i = 0, len = exp.length(), j = len - 1;
//		while (isSpace(exp[i]))
//			i++;
//		while (isSpace(exp[j]))
//			j--;
//		string trimmedExp = exp.substr(i, j - i + 1);
//		printf("Trimmed Expression: %s\n", trimmedExp.c_str());
//		i = 0;
//		int numOps = 0;
//		len = trimmedExp.length();
//		char c;
//		while (i < len)
//			if (isOperation(trimmedExp[i++], -1))
//				numOps++;
//		if (numOps > 0)
//			return FindExpression(trimmedExp, 0, len);
//		return new Term(trimmedExp);
//	}

#include "Term.h"
#include "algorithm"

static Type DetermineType(Type l, Type r, bool equal);
static bool hasType(Type types[], Type type);
static int GetOperationPriority(char op);
static bool isOperation(char c);
static string RemoveSpace(string str);

    char validOperations[] =
    {
        '+', '-', '*', '/'
    };
    Expression::Expression(Term* left, Term* right, char operation)
        : Term()
    {
        type = EXPR_T;
        this->left = left;
        this->right = right;
        this->operation = operation;
    }
    Term* Expression::Evaluate(/*Context context*/)
    {
        //cout << "\tEvaluating: " << toString() << '\n';
        Term* l = left->Evaluate(/*context*/);
        Term* r = right->Evaluate(/*context*/);
        // Type will bubble
        Type lType = l->type;
        Type rType = r->type;

        void* result = nullptr;

        bool typesEqual = (lType == rType);
        Type determinedType = DetermineType(lType, rType, typesEqual);
        switch (determinedType)
        {
        case INT_T: {
            int lInt = (int)*l;
            int rInt = (int)*r;
            switch (operation)
            {
            case '+':
                result = new int(lInt + rInt);
                break;
            case '-':
                result = new int(lInt - rInt);
                break;
            case '*':
                result = new int(lInt * rInt);
                break;
            case '/':
                result = new int(lInt / rInt);
                break;
            default:
                result = nullptr;
                break;
            }
            break;
        }
        case FLOAT_T: {
            float lFloat = (float)*l;
            float rFloat = (float)*r;
            switch (operation)
            {
            case '+':
                result = new float(lFloat + rFloat);
                break;
            case '-':
                result = new float(lFloat - rFloat);
                break;
            case '*':
                result = new float(lFloat * rFloat);
                break;
            case '/':
                result = new float(lFloat / rFloat);
                break;
            default:
                result = nullptr;
                break;
            }
            break;
        }
        case DOUBLE_T: {
            double lDouble = (double)*l;
            double rDouble = (double)*r;
            switch (operation)
            {
            case '+':
                result = new double(lDouble + rDouble);
                break;
            case '-':
                result = new double(lDouble - rDouble);
                break;
            case '*':
                result = new double(lDouble * rDouble);
                break;
            case '/':
                result = new double(lDouble / rDouble);
                break;
            default:
                result = nullptr;
                break;
            }
            break;
        }
        default:
            result = nullptr;
            break;
        }
        delete l;
        delete r;
        //cout << "Expr r t: " << TypeFromStr(determinedType) << '\n';
        return new Term(result, determinedType);
    }
    string Expression::toString() {
        stringstream str;
        str << "{expression:(" << (left ? left->toString() : "") << " " << operation << " " << (right ? right->toString() : "") << ")}";
        return str.str();
    }
    Term* Expression::ParseAndCreate(string expression)
    {
        return TryCreate(Parse(expression));
    }
    string Expression::Parse(string expression)
    {
        // Ensure we don't have any screwy chars
        expression = RemoveSpace(expression);
        // Ensure expression follows protocol
        int expLen = expression.length();
        expression = expression.insert(0, "(", 1).insert(expLen + 1, ")", 1);
        // Parse operations by priority
        for (int priority = TOP_PRIORITY; priority > -1; priority--)
        {
            // Create a RegEx with all operations to identify all operations
            // Form a new expression in valid format
            string clone = expression;
            replace(clone.begin(), clone.end(), '(', '[');
            replace(clone.begin(), clone.end(), ')', ']');
            // With the given priority
            string validOps;
            string invalidOps;
            for (char op : validOperations)
            {
                if (GetOperationPriority(op) == priority) {
                    validOps += '\\'; validOps += op;
                }
                else {
                    invalidOps += '\\'; invalidOps += op;
                }
            }
            //string* regex = &validOps;
            // Replace all valid ops with '|'
            for (char c : validOps) {
                replace(clone.begin(), clone.end(), c, '|');
            }
            // replace(clone.start(), "[" + *regex + "]+", "|");
            // If no valid ops were found
            if (clone.find('|') == string::npos)
                continue;
            //regex = &invalidOps;
            // Replace all invalid ops with 'u'
            for (char c : invalidOps) {
                replace(clone.begin(), clone.end(), c, 'u');
            }
            // clone = Regex.Replace(clone, "[" + *regex + "]+", "u");

            //Console.WriteLine("Start");

            while (true)
            {
                // Console.WriteLine(clone);
                // Exit if no brackets
                if (clone.find('[') == string::npos)
                    break;
                int end = 0, len = clone.length(), firstPriorityOp = -1;
                // Find first end bracket
                while (end < len && clone[end] != ']')
                {
                    end++;
                }
                // Find corresponding start bracket
                int start = end;
                while (start > -1 && clone[start] != '[')
                {
                    start--;
                }
                while (true)
                {
                    int numOps = 0, numPriorityOps = 0, pos = start;
                    // Find all operations
                    while (pos < end)
                    {
                        if (isOperation(clone[pos]))
                        {
                            numOps++;
                            if (clone[pos] == '|')
                            {
                                numPriorityOps++;
                                if (numPriorityOps == 1)
                                    firstPriorityOp = pos;
                            }
                        }
                        pos++;
                    }
                    if (numPriorityOps == 0)
                    {
                        //Console.WriteLine("3a: " + clone);
                        //if (clone.IndexOf(']') == len - 1 && clone.LastIndexOf('[') == 0)
                        //{
                        //    clone = clone.Remove(len - 1, 1).Remove(0, 1);
                        //    expression = expression.Remove(len - 1, 1).Remove(0, 1);
                        //}
                        if (clone[start] == '[')
                        {
                            clone = clone.replace(start, 1, "(");
                            clone = clone.replace(end, 1, ")");
                        }
                        //Console.WriteLine("3b: " + clone);
                        break;
                    }
                    else if (numPriorityOps >= 1)
                    {
                        pos = firstPriorityOp - 1;
                        int level = 0, placeStart = start, placeEnd = end;
                        while (pos > start)
                        {
                            char c = clone[pos];
                            if (isOperation(c) && level == 0)
                                break; // need +1
                            else if (c == ')')
                                level++;
                            else if (c == '(')
                                level--;
                            pos--;
                        }
                        placeStart = pos + 1;
                        pos = firstPriorityOp + 1;
                        level = 0;
                        while (pos < end)
                        {
                            char c = clone[pos];
                            if (isOperation(c) && level == 0)
                                break; // need +1
                            else if (c == '(')
                                level++;
                            else if (c == ')')
                                level--;
                            pos++;
                        }
                        placeEnd = pos;
                        // Add parentheses
                        if (numOps == 1)
                        {
                            //Console.WriteLine("1a: " + clone);
                            clone = clone.replace(firstPriorityOp, 1, "u");
                            clone = clone.replace(placeEnd, 1, "u");
                            clone = clone.replace(placeStart - 1, 1, "(");
                            //Console.WriteLine("1b: " + clone);
                            continue;
                        }
                        //Console.WriteLine("2a: " + clone);
                        clone = clone.replace(firstPriorityOp, 1, "u");
                        clone = clone.insert(placeEnd, ")");
                        clone = clone.insert(placeStart, "(");
                        expression = expression.insert(placeEnd, ")");
                        expression = expression.insert(placeStart, "(");
                        //Console.WriteLine("2b: " + clone);
                        len += 2;
                        end += 2;
                    }
                }
            }
        }
        // Remove the extra parentheses we added originally
        expression = expression.erase(0,1).erase(expression.length() - 2, 1);
        //cout << "Expression: " << expression << '\n';
        return expression;
    }
    Term* Expression::TryCreate(string expression)
    {
        if (expression.find("(") != string::npos)
        {
            int level = 0, pos = 0, len = expression.length();
            do
            {
                if (expression[pos] == ')')
                    level--;
                else if (expression[pos] == '(')
                    level++;
                pos++;
            } while (level != 0 && pos < len);

            if (pos < len)
            {
                for (char operation : validOperations)
                {
                    if (expression[pos] == operation)
                    {
                        pos++;
                        /*cout << "Attempting to create: " << TryCreate(expression.substr(0, pos - 1))->toString() << '\n';
                        cout << "... and: " << TryCreate(expression.substr(pos, len - pos))->toString() << '\n';*/
                        return new Expression(
                            TryCreate(expression.substr(0, pos - 1)),
                            TryCreate(expression.substr(pos, len - pos)), operation);
                    }
                }
            }
            else
            {
                expression = expression.erase(0, 1).erase(len - 2, 1);
                /*cout << "Attempting to create SINGLE: " << TryCreate(expression)->toString() << '\n';*/
                return TryCreate(expression);
            }
        }
        for (char operation : validOperations)
        {
            int pos = -1;
            if ((pos = expression.find(operation)) != string::npos)
            {
                string landr[] = { expression.substr(0, pos), expression.substr(pos + 1, expression.length()) };
                return new Expression(
                    TryCreate(landr[0]),
                    TryCreate(landr[1]), operation);
            }
        }
        //cout << expression << '\n';
        // Guess the type
        Type type = VAR_T;
        void* value = nullptr;
        bool isNumber = isdigit(expression[0]);
        bool isString = (expression[0] == '\"');
        bool isChar = (expression[0] == '\'');
        bool hasDecimal = expression.find('.') != string::npos;
        bool isFloat = expression.find('f') != string::npos;
        if (isNumber)
        {
            if (isFloat)
            {
                type = FLOAT_T;
                value = new float(stof(expression.erase(expression.find_last_of('f'), 1)));
            }
            else if (hasDecimal)
            {
                type = DOUBLE_T;
                //cout << expression << '\n';
                // just incase there is a d
                if (expression.find('d') != string::npos)
                    expression = expression.erase(expression.find_last_of('d'), 1);
                value = new double(stod(expression));
            }
            else
            {
                type = INT_T;
                value = new int(stoi(expression));
            }
        }
        else if (isString)
        {
            type = STRING_T;
            expression = expression.substr(1, expression.length() - 1);
            value = new string(expression);
        }
        else if (isChar)
        {
            type = CHAR_T;
            value = new char(expression[1]);
        }
        else {
            // var
            value = new string(expression);
        }
        Term* newTerm = new Term(value, type);
        //cout << newTerm->toString() << '\n';
        return newTerm;
    }

    static Type DetermineType(Type l, Type r, bool equal)
    {
        if (equal)
        {
            for (const auto type : RTC::Types)
            {
                if (type == l) return type;
            }
            return VAR_T;
        }
        Type types[] = { l, r };
        // Implementation choice -> treat op with char as string
        bool hasString = hasType(types, STRING_T) || hasType(types, CHAR_T);
        bool hasDouble = hasType(types, DOUBLE_T);
        bool hasInt = hasType(types, INT_T);
        bool hasFloat = hasType(types, FLOAT_T);
        if (hasString) return STRING_T;
        if (hasDouble) return DOUBLE_T;
        if (hasFloat) return FLOAT_T;
        if (hasInt) return INT_T;
        return VAR_T;
    }
    static bool hasType(Type types[], Type type)
    {
        return (types[0] == type || types[1] == type);
    }
    static int GetOperationPriority(char op)
    {
        if (op == '+' || op == '-') return 0;
        return 1;
    }
    static bool isOperation(char c)
    {
        return c == '|' || c == 'u';
    }

    static string RemoveSpace(string str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\t'), str.end());
        return str;
    }