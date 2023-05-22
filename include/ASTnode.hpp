#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <vector>
#include <string>

#include "trio.hpp"

using namespace std;

class ASTnode {
public:

	ASTnode() = default;

	~ASTnode() = default;

private:
	
	string data;

	ASTnode* parent;

	vector<ASTnode*> children;
};

#endif
