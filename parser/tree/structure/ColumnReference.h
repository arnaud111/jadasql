//
// Created by nono on 16/10/2023.
//

#ifndef JADA_COLUMNREFERENCE_H
#define JADA_COLUMNREFERENCE_H

#include <string>
#include <utility>

class ColumnReference {

public:
    std::string tableName;
    std::string columnName;

    explicit ColumnReference(std::string columnName) {
        this->columnName = std::move(columnName);
    }

    explicit ColumnReference(std::string columnName, std::string tableName) {
        this->columnName = std::move(columnName);
        this->tableName = std::move(tableName);
    }
};

#endif //JADA_COLUMNREFERENCE_H
