#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Token.hpp"

using namespace std;

class Extra_node{
private:
	Token token;
	Token oper;
	Extra_node* left_node;
	Extra_node* right_node;	
public:
	void set_oper(Token p_oper){
		p_oper = oper;
	}
	void set_token(Token p_token){
		p_token = token;
	}
	void set_left_node(Extra_node* p_left_node){
		p_left_node = left_node;
	}
	void set_right_node(Extra_node* p_right_node){
		p_right_node = right_node;
	}

	Token get_oper() {return oper;}
	Token get_token() {return token;}
	Extra_node* get_left_node() {return left_node;}
	Extra_node* get_right_node() {return right_node;}
	Extra_node() = default;
	
	void Extra_Node(Token p_token) {
	 	token = p_token;
	}

	void Extra_Node(Token p_oper, Extra_node* p_left_node, Extra_node* p_right_node) {
		oper = p_oper;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~Extra_node() = default;
	vector <Extra_node> nodes;

	void add_node(Extra_node p_node) {
		nodes.push_back(p_node);
	}
	



};

#endif