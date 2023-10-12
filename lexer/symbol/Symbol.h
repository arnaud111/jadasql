//
// Created by arnaud on 29/08/2023.
//

#ifndef JADA_SYMBOL_H
#define JADA_SYMBOL_H

#include "Group.h"
#include "SymbolValue.h"

class Symbol {

public:
    Group group;
    SymbolValue* value;
};

#endif //JADA_SYMBOL_H
