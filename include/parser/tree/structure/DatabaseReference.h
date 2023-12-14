//
// Created by nono on 16/10/2023.
//

#ifndef JADA_DATABASEREFERENCE_H
#define JADA_DATABASEREFERENCE_H

#include <string>
#include "../field/Field.h"

class DatabaseReference : public Field {

public:
    std::string databaseName;

    explicit DatabaseReference(std::string databaseName);

    explicit DatabaseReference(std::vector<Symbol *> symbols);

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_DATABASEREFERENCE_H
