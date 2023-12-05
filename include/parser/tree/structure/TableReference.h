//
// Created by nono on 16/10/2023.
//

#ifndef JADA_TABLEREFERENCE_H
#define JADA_TABLEREFERENCE_H

#include <string>
#include "DatabaseReference.h"

class TableReference : public Field {

public:
    std::string alias;
    std::string tableName;
    DatabaseReference *databaseReference;

    explicit TableReference(std::vector<Symbol *> symbols);

    void display() override;
};

#endif //JADA_TABLEREFERENCE_H
