//
// Created by nono on 11/12/23.
//

#ifndef JADA_RETURNEDVALUE_H
#define JADA_RETURNEDVALUE_H

#include <string>
#include <vector>

enum ReturnedValueType {
    None,
    RowCount,
    RowData,
};

class ReturnedValue {

public:

    ReturnedValueType type;

    static ReturnedValue *none();

    static ReturnedValue *rowCount(int affected);

    static ReturnedValue *rowData(std::vector<std::string> columnsName, std::vector<std::vector<std::string>> rows);

    static ReturnedValue *rowData(std::string columnName, std::vector<std::string> rows);

    virtual void display() {

    };
};

#endif //JADA_RETURNEDVALUE_H
