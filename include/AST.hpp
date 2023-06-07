#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Token.hpp"

using namespace std;

class AST_Node {
private:

	Token token;
	AST_Node* left_node;
	AST_Node* right_node;	
	AST_Node* parent;

public:

	AST_Node() = default;
	
	AST_Node(Token p_token) {
	 	token = p_token;
	}

	AST_Node(Token p_token, AST_Node* p_left_node, AST_Node* p_right_node) {
		token = p_token;
		left_node = p_left_node;
		right_node = p_right_node;
	}

	~AST_Node() = default;

	vector<AST_Node*> nodes;
	void add_node(AST_Node* p_node) {
		nodes.push_back(p_node);
	}
	
	void set_token(Token p_token) { token = p_token; }
	void set_left_node(AST_Node* p_left_node) { left_node = p_left_node; }
	void set_right_node(AST_Node* p_right_node) { right_node = p_right_node; }
	void set_parent(AST_Node* p_parent) { parent = p_parent; }

	Token get_token() { return token; }
	AST_Node* get_left_node() { return left_node; }
	AST_Node* get_right_node() { return right_node; }
	AST_Node* get_parent() { return parent; }

	friend ostream &operator<< (ostream& out, AST_Node& node) {
		out << node.token.get_lexeme() << endl;
		return out;
	}
};

AST_Node* insert_left(AST_Node* root, AST_Node* p_node) {
    if (root == nullptr) {
        return nullptr;
    }
    root->set_left_node(insert_left(root->get_left_node(), p_node));

    return root;
}

AST_Node* insert_right(AST_Node* root, AST_Node* p_node) {
	if (root == nullptr) {
		return nullptr;
	}
	root->set_right_node(insert_right(root->get_right_node(), p_node));

	return root;
}

void print_tree(AST_Node* root, string prefix = "", bool is_left = true) {
	if (root == nullptr) {
		return;
	}

	cout << prefix;
	cout << (is_left ? "|-- " : "`-- ");
	cout << *root << endl;

	print_tree(root->get_left_node(), prefix + (is_left ? "|   " : "    "), true);
	print_tree(root->get_right_node(), prefix + (is_left ? "|   " : "    "), false);
}

#endif
