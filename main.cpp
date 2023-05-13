#include <iostream>

int main() {
	
	return 0;
}

/*
lexer:

[word, string]
[word, s]
[new line]
[word, s]
[operator, =]
[lstring, "Hello World!"]
[new line]
[word, print]
[word, s]
*/

/*
syntax analyzer:

сделать таблицу объявленных переменных
*/

class Node {
	Node* parent;

	std::list<Node*> children;

	enum {
		DEF,
		VAR,
		OPER,
		LSTR
	} type;
}


