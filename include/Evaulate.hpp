#ifndef EVAULATE_HPP
#define EVAULATE_HPP

#include <iostream>
#include <string>

using namespace std;

class Evaulate {
private:
	string expression;

public:
	
	Evaulate(string p_expression): expression(p_expression) {}

	long evaluate() {
		long i = 0;
		return parse_expression(i);
	}

private:

	long parse_number(long& i) {
        long num = 0;
        while (i < expression.size() && isdigit(expression[i])) {
            num = num * 10 + (expression[i] - '0');
            i++;
        }
        return num;
    }

    long parse_term(long& i) {
        long num1 = parse_number(i);
        while (i < expression.size() && (expression[i] == '*' || expression[i] == '/')) {
            char op = expression[i];
            i++;
            long long num2 = parse_number(i);
            if (op == '*') {
                num1 *= num2;
            }
            else {
                num1 /= num2;
            }
        }
        return num1;
    }

    long parse_expression(long& i) {
        long num1 = parse_term(i);
        while (i < expression.size() && (expression[i] == '+' || expression[i] == '-')) {
            char op = expression[i];
            i++;
            long num2 = parse_term(i);
            if (op == '+') {
                num1 += num2;
            }
            else {
                num1 -= num2;
            }
        }
        return num1;
	}
};

#endif
