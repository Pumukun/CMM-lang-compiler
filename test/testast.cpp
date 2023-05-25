#include <iostream>

#include "../include/AST.hpp"
#include "../include/Token.hpp"


using namespace std;

int main() {
	Token a;
	a.set_lexeme("a");
	a.set_pos(0);
	a.set_type(VARIABLE);
	Variable_Node nv(a);
	
	return 0;
}
