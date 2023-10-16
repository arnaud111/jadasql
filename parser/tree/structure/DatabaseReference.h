//
// Created by nono on 16/10/2023.
//

#ifndef JADA_DATABASEREFERENCE_H
#define JADA_DATABASEREFERENCE_H

#include <string>

class DatabaseReference {

public:
    std::string databaseName;

    explicit DatabaseReference(std::string databaseName) {
        this->databaseName = std::move(databaseName);
    }
};

#endif //JADA_DATABASEREFERENCE_H
