//
// Created by nono on 12/12/23.
//

#include <utility>

#include "../../../include/interpreter/values/ReturnedRowData.h"


ReturnedRowData::ReturnedRowData(std::vector<std::string> columnsName, std::vector<std::vector<std::string>> rows) : ReturnedValue() {

    this->type = RowData;
    this->columnsName = std::move(columnsName);
    this->rows = std::move(rows);

}

ReturnedRowData::ReturnedRowData(std::string columnName, const std::vector<std::string>& rows) : ReturnedValue() {

    std::vector<std::vector<std::string>> realRows;

    realRows.reserve(rows.size());
    for (auto &row: rows) {
        realRows.push_back({row});
    }

    this->type = RowData;
    this->columnsName = {std::move(columnName)};
    this->rows = realRows;

}

void ReturnedRowData::display() {

    for (unsigned long long i = 0; i < this->columnsName.size(); i++) {
        printf("|%s|", this->columnsName[i].c_str());
    }
    printf("\n");

    for (unsigned long long i = 0; i < this->rows.size(); i++) {
        for (unsigned long long j = 0; j < this->rows[i].size(); j++) {
            printf("|%s|", this->rows[i][j].c_str());
        }
        printf("\n");
    }
}
