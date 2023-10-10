//
// Created by nono on 10/10/23.
//

#ifndef JADA_PARSER_H
#define JADA_PARSER_H


#include <vector>
#include "tree/statements/Statement.h"
#include "../lexer/Symbol.h"

class Parser {

public:
    static std::vector<Statement*> parse(std::vector<Symbol> symbols);
};


#endif //JADA_PARSER_H
