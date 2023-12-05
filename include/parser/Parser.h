//
// Created by nono on 10/10/23.
//

#ifndef JADA_PARSER_H
#define JADA_PARSER_H


#include <vector>
#include "tree/statements/Statement.h"
#include "../lexer/symbol/Symbol.h"
#include "tree/function/Function.h"

class Parser {

public:
    static std::vector<Statement *> parse(const std::vector<Symbol *> &symbols);

    static Statement *createStatement(std::vector<Symbol *> symbol);

private:
    static std::vector<std::vector<Symbol *>> splitRequests(const std::vector<Symbol *> &symbols);

};


#endif //JADA_PARSER_H
