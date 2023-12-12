//
// Created by nono on 12/12/23.
//

#include "../../../include/interpreter/values/ReturnedRowCount.h"


ReturnedRowCount::ReturnedRowCount(int affected) : ReturnedValue() {

    this->type = RowCount;
    this->affected = affected;

}
