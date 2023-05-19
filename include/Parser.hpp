#ifndef PARSER_HPP
#define PARSER_HPP
#pragma once

#include <vector>
#include <string>

#include "ASTnode.hpp"
#include "trio.hpp"

class Parser {
public:

	Parser() = default;

	Parser(vector<trio<int, string, string>> input_grammar) { grammar = std::move(input_grammar); } 

	~Parser() = default;

private:

	vector<trio<int, string, string>> grammar;

public:

	void generate_AST() {
		
		return ;
	}
};

#endif

