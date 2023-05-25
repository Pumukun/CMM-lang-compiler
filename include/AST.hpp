#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>

#include "Token.hpp"

using namespace std;

class Expression_Node;


class Statsmest_Node : public Expression_Node{
public:
	vector<Expression_Node> MyNode;

	void Add_Node(Expression_Node p_node){
		MyNode.push_back(p_node);
	}
}

class Variable_Node : public Expression_Node{
public: 
	 Token token;

	 Variable_Node(Token p_token) {
	 	token = p_token;
	 }
}


class Number_Node : public Expression_Node{
public:
	Token number;

	Number_Node(Token p_number){
		number = p_number;
	}
}

class Binary_oper_Node : public Expression_Node{
public:
	Token oper;
	Expression_Node *left_node;
	Expression_Node *right_node;

	Binary_oper_Node(Token p_oper, Expression_node *p_left_node,Expression_node *p_right_node){
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}

}

class Unar_oper_Node : public Expression_Node{
public:
	Token oper;
	Expression_Node *operand;

	Unar_oper_Node(Token p_oper, Expression_node *p_operand){
		oper = p_oper;
		operand = p_operand;
	}
}

class Assign_Node : public Expression_Node{
public:
	Token oper;
	Expression_node *left_node;
	Expression_Node *right_node;

	Assign_Node(Token p_oper, Expression_node *p_left_node, Expression_node *p_right_node){
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}
}

#endif
