//
// Created by nono on 12/12/23.
//

#ifndef JADA_RETURNEDROWDATA_H
#define JADA_RETURNEDROWDATA_H

#include <vector>
#include <string>
#include "interpreter/ReturnedValue.h"

class ReturnedRowData: public ReturnedValue {

public:

    std::vector<std::string> columnsName;
    std::vector<std::vector<std::string>> rows;

    explicit ReturnedRowData(std::vector<std::string> columnsName, std::vector<std::vector<std::string>> rows);

    explicit ReturnedRowData(std::string columnName, const std::vector<std::string>& rows);

    void display() override;
};

#endif //JADA_RETURNEDROWDATA_H
