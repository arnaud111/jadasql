//
// Created by nono on 16/10/2023.
//

#ifndef JADA_TABLEREFERENCE_H
#define JADA_TABLEREFERENCE_H

#include <string>
#include <utility>
#include "DatabaseReference.h"
#include "../tree_item/TreeItem.h"

class TableReference : public TreeItem {

public:
    std::string alias;
    std::string tableName;
    DatabaseReference *databaseReference;

    explicit TableReference(std::string tableName) {
        this->tableName = std::move(tableName);
        this->databaseReference = nullptr;
    }

    explicit TableReference(std::string tableName, std::string alias) {
        this->tableName = std::move(tableName);
        this->alias = std::move(alias);
        this->databaseReference = nullptr;
    }

    explicit TableReference(std::string tableName, DatabaseReference *databaseReference) {
        this->tableName = std::move(tableName);
        this->databaseReference = databaseReference;
    }

    explicit TableReference(std::string tableName, DatabaseReference *databaseReference, std::string alias) {
        this->tableName = std::move(tableName);
        this->alias = std::move(alias);
        this->databaseReference = databaseReference;
    }

    void display() override;
};

#endif //JADA_TABLEREFERENCE_H
