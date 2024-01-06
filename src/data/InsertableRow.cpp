//
// Created by nono on 19/12/2023.
//

#include <utility>

#include "../../include/data/InsertableRow.h"

InsertableRow::InsertableRow(std::vector<InsertableField *> listField) {

    this->listField = std::move(listField);

}
