#include "Parser.h"

Parser::Parser(std::list<Token> token_list) {

	this->tokens = token_list;
}

bool Parser::CheckSyntax() {

	auto pos = tokens.begin();
	
	while (lang(pos) && pos != tokens.end());
	
	if (pos != tokens.end()) {

		std::cout << "Parser error" << std::endl;
		return false;
	}

	return true;
}

bool Parser::lang(std::list<Token>::iterator &lex_pos) {

	auto start = lex_pos;
	
	if (!assign_expr(lex_pos)) {
		lex_pos = start;

		if (!if_expr(lex_pos)) {
			lex_pos = start;

			if (!while_expr(lex_pos)) {

				return false;
			}
		}
	}
	
	return true;
}

bool Parser::assign_expr(std::list<Token>::iterator &lex_pos) {

	if (!VAR(lex_pos) || !ASSIGN_OP(lex_pos))
		return false;

	if (value_expr(lex_pos)) {

		while (value_expr(lex_pos));

		if (END_ST(lex_pos))
			return true;
	}
	
	return false;
}

bool Parser::value_expr(std::list<Token>::iterator &lex_pos) {

	if (!value(lex_pos))
		return false;

	while (OP(lex_pos))
		if (!value(lex_pos))
			return false;	

	return true;
}

bool Parser::if_expr(std::list<Token>::iterator &lex_pos) {

	if (!IF_KW(lex_pos) || !L_BR(lex_pos) || !logic_expr(lex_pos) || !R_BR(lex_pos) || !lang(lex_pos))
		return false;

	return true;
}

bool Parser::while_expr(std::list<Token>::iterator &lex_pos) {

	if (!WHILE_KW(lex_pos) || !L_BR(lex_pos) || !logic_expr(lex_pos) || !R_BR(lex_pos) || !lang(lex_pos))
		return false;

	return true;
}

bool Parser::logic_expr(std::list<Token>::iterator &lex_pos) {

	if (comp_expr(lex_pos)) {

		while (LOG_OP(lex_pos))
			if (!comp_expr(lex_pos))
				return false;

		return true;
	}

	return false;
}

bool Parser::comp_expr(std::list<Token>::iterator &lex_pos) {

	if (value(lex_pos)) {

		if (COMP_OP(lex_pos) && !value(lex_pos))
			return false;
		
		return true;
	}

	return false;
}

bool Parser::value(std::list<Token>::iterator &lex_pos) {

	if (!VAR(lex_pos) && !DIGIT(lex_pos))
		return false;

	return true;
}

bool Parser::IF_KW(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "IF_KW") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::WHILE_KW(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "WHILE_KW") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::VAR(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "VAR") {
		++lex_pos;
		return true;
	}
		
	return false;
}

bool Parser::DIGIT(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "DIGIT") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::ASSIGN_OP(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "ASSIGN_OP") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::OP(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "OP") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::LOG_OP(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "LOG_OP") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::COMP_OP(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "COMP_OP") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::END_ST(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "END_ST") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::L_BR(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "L_BR") {
		++lex_pos;
		return true;
	}

	return false;
}

bool Parser::R_BR(std::list<Token>::iterator &lex_pos) {

	if (lex_pos->GetType() == "R_BR") {
		++lex_pos;
		return true;
	}

	return false;
}

Parser::~Parser() {}