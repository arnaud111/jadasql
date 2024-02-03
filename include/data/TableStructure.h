//
// Created by nono on 11/12/23.
//

#ifndef JADA_TABLESTRUCTURE_H
#define JADA_TABLESTRUCTURE_H

#include <string>
#include <vector>
#include "InsertableRow.h"

class TableStructure {

public:

    static std::vector<std::string> getListTable(const std::string& database);

    static bool tableExist(const std::string& database, const std::string& name);

    static bool createTable(const std::string& database, const std::string& table);

    static bool removeTable(const std::string& database, const std::string& table);

    static void insertRow(const std::string& database, const std::string& table, InsertableRow *insertableRow);

    static std::vector<std::vector<Field *>> selectAllInTable(const std::string &database, const std::string &table, std::vector<DataType *> columnsDataType);

private:

    static std::vector<Field *> selectNextLine(std::ifstream *file, std::vector<DataType *> columnsDataType);
};

#endif //JADA_TABLESTRUCTURE_H
