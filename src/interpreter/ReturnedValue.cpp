//
// Created by nono on 12/12/23.
//

#include "../../include/interpreter/ReturnedValue.h"
#include "interpreter/values/ReturnedRowCount.h"


ReturnedValue *ReturnedValue::none() {

    auto *returnedValue = new ReturnedValue();
    returnedValue->type = None;

    return returnedValue;
}

ReturnedValue *ReturnedValue::rowCount(int affected) {
    return new ReturnedRowCount(affected);
}
