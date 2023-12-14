//
// Created by nono on 12/12/23.
//

#include <utility>

#include "../../include/interpreter/ReturnedValue.h"
#include "interpreter/values/ReturnedRowCount.h"
#include "interpreter/values/ReturnedRowData.h"


ReturnedValue *ReturnedValue::none() {

    auto *returnedValue = new ReturnedValue();
    returnedValue->type = None;

    return returnedValue;
}

ReturnedValue *ReturnedValue::rowCount(int affected) {
    return new ReturnedRowCount(affected);
}

ReturnedValue *ReturnedValue::rowData(std::vector<std::string> columnsName, std::vector<std::vector<std::string>> rows) {
    return new ReturnedRowData(std::move(columnsName), std::move(rows));
}

ReturnedValue *ReturnedValue::rowData(std::string columnName, std::vector<std::string> rows) {
    return new ReturnedRowData(std::move(columnName), rows);
}
