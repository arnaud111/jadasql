//
// Created by nono on 16/10/2023.
//

#ifndef JADA_COLUMNREFERENCE_H
#define JADA_COLUMNREFERENCE_H

#include <string>
#include <utility>
#include "../field/Field.h"

class ColumnReference : public Field {

public:
    std::string tableName;
    std::string columnName;

    explicit ColumnReference(std::string columnName) {
        this->fieldType = f_Column;
        this->columnName = std::move(columnName);
    }

    explicit ColumnReference(std::string columnName, std::string tableName) {
        this->fieldType = f_Column;
        this->columnName = std::move(columnName);
        this->tableName = std::move(tableName);
    }

    void display() override;

    ReturnedValue *execute(ExecutionData *executionData) override;
};

#endif //JADA_COLUMNREFERENCE_H
