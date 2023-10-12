//
// Created by nono on 10/10/23.
//

#ifndef JADA_STATEMENT_H
#define JADA_STATEMENT_H

enum StatementType {
    Select,
    Insert,
    Update,
    Drop,
    DELETE,
};

class Statement {

public:
    StatementType statementType;
};

#endif //JADA_STATEMENT_H
