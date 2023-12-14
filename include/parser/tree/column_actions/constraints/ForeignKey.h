//
// Created by nono on 14/11/2023.
//

#ifndef JADA_FOREIGNKEY_H
#define JADA_FOREIGNKEY_H

#include <string>
#include <vector>
#include "../ColumnConstraints.h"
#include "../../field/Field.h"
#include "../../structure/TableReference.h"

class ForeignKey: public ColumnConstraints {

public:

    std::string name;
    std::vector<Field *> columns;
    TableReference * tableReference;
    std::vector<Field *> references;

    explicit ForeignKey(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_FOREIGNKEY_H
