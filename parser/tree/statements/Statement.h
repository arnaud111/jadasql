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
};

class Statement : public Field {

public:
    StatementType statementType;

    static std::vector<Symbol *>
    splitUntilKeywords(std::vector<Symbol *> symbols, int start, const std::vector<int> &keywords);
};

#endif //JADA_STATEMENT_H
