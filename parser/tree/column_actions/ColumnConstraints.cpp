//
// Created by nono on 14/11/2023.
//

#include "ColumnConstraints.h"
#include "constraints/Check.h"
#include "constraints/ForeignKey.h"
#include "constraints/PrimaryKey.h"

Check::Check(std::vector<Symbol *> symbols) : ColumnConstraints() {

    this->condition = nullptr;
    this->type = c_Check;

}

ForeignKey::ForeignKey(std::vector<Symbol *> symbols) : ColumnConstraints() {

    this->type = c_ForeignKey;

}

PrimaryKey::PrimaryKey(std::vector<Symbol *> symbols) : ColumnConstraints() {

    this->type = c_PrimaryKey;

}
