//
// Created by nono on 16/10/2023.
//

#ifndef JADA_DATABASEREFERENCE_H
#define JADA_DATABASEREFERENCE_H

#include <string>
#include "../tree_item/TreeItem.h"

class DatabaseReference : public TreeItem {

public:
    std::string databaseName;

    explicit DatabaseReference(std::string databaseName) {
        this->databaseName = std::move(databaseName);
    }

    void display() override;
};

#endif //JADA_DATABASEREFERENCE_H
