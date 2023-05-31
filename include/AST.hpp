#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <string>

#include "Token.hpp"

using namespace std;

/*

class Expression_Node {
public:
	virtual ~Expression_Node() = default;
};


class Statesment_Node : public Expression_Node {
public:
	vector<Expression_Node> MyNode;

	void add_node(Expression_Node p_node) {
		MyNode.push_back(p_node);
	}

	~Statesment_Node() = default;
}; 

class Variable_Node : public Expression_Node {
public: 
	 Token token;

	 Variable_Node(Token p_token) {
	 	token = p_token;
	 }

	 ~Variable_Node() = default;
};


class Number_Node : public Expression_Node {
public:
	Token number;

	Number_Node(Token p_number) {
		number = p_number;
	}

	~Number_Node() = default;
};

class Binary_oper_Node : public Expression_Node {
public:
	Token oper;
	Expression_Node left_node;
	Expression_Node right_node;

	Binary_oper_Node(Token p_oper, Expression_Node p_left_node, Expression_Node p_right_node) {
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~Binary_oper_Node() = default;
};

class Unar_oper_Node : public Expression_Node {
public:
	Token oper;
	Expression_Node operand;

	Unar_oper_Node(Token p_oper, Expression_Node p_operand) {
		oper = p_oper;
		operand = p_operand;
	}

	~Unar_oper_Node() = default;
};

class Assign_Node : public Expression_Node {
public:
	Token oper;
	Expression_Node *left_node;
	Expression_Node *right_node;

	Assign_Node(Token p_oper, Expression_Node *p_left_node, Expression_Node *p_right_node) {
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~Assign_Node() = default;
};

#endif
*/


class Extra_node{
private:
	Token token;
	Extra_node* left_node;
	Extra_node* right_node;	
public:
	void set_token(token){
		this->token = token;
		p_token;
	}
	void set_left_node(left_node){
		this->left_node = left_node;
	}
	void set_right_node(right_node){
		this->right_node = right_node;
	}
	get_token() {return token;}
	get_left_token() {return left_node;}
	get_right_token() {return right_node;}
	Extra_node() = default;
	
	Extra_Node(Token p_token) {
	 	token = p_token;
	}

	Extra_Node(Token p_oper, Expression_Node p_left_node, Expression_Node p_right_node) {
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~Extra_node() = default;
	vector <Extra_node> nodes;

	void add_node(Extra_Node p_node) {
		nodes.push_back(p_node);
	}
}

#endif