//
// Created by nono on 16/10/2023.
//

#ifndef JADA_FIELD_H
#define JADA_FIELD_H

#include <vector>
#include "../../../lexer/symbol/Symbol.h"

class Field {

public:

    static std::vector<Field*> createListField(const std::vector<Symbol*>& symbols);
};

#endif //JADA_FIELD_H
