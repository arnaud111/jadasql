//
// Created by nono on 10/10/23.
//

#ifndef JADA_PARSER_H
#define JADA_PARSER_H


#include <vector>
#include "tree/statements/Statement.h"
#include "../lexer/symbol/Symbol.h"

class Parser {

public:
    static std::vector<Statement*> parse(std::vector<Symbol> symbols);

private:
    static Statement* createStatement(Symbol symbol);
};


#endif //JADA_PARSER_H
