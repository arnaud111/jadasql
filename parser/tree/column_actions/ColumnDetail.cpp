//
// Created by nono on 14/11/2023.
//

#include "ColumnDetail.h"

ColumnDetail::ColumnDetail(std::vector<Symbol *> symbols) {

    this->dataType = nullptr;
    this->defaultValue = nullptr;
    this->name = nullptr;
    this->unique = false;
    this->notNull = false;

}
