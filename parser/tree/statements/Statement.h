//
// Created by nono on 10/10/23.
//

#ifndef JADA_STATEMENT_H
#define JADA_STATEMENT_H

#include "../field/Field.h"
#include "../tree_item/TreeItem.h"

enum StatementType {
    Select,
    Insert,
    Update,
    Drop,
    Delete,
    Create,
    Alter,
};

class Statement : public Field {

public:
    StatementType statementType;

    static std::vector<Symbol *> splitUntilKeywords(std::vector<Symbol *> symbols, unsigned long long start, const std::vector<int> &keywords);

    static std::vector<Symbol *> splitUntilParenthesisOrKeyword(std::vector<Symbol *> symbols, unsigned long long start, const std::vector<int> &keywords);

    static std::vector<std::vector<Symbol *>> splitComa(const std::vector<Symbol *>& symbols);
};

#endif //JADA_STATEMENT_H
