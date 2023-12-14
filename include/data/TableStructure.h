//
// Created by nono on 11/12/23.
//

#ifndef JADA_TABLESTRUCTURE_H
#define JADA_TABLESTRUCTURE_H

#include <string>
#include <vector>

class TableStructure {

public:

    static std::vector<std::string> getListTable(const std::string& database);

    static bool tableExist(const std::string& database, const std::string& name);
};

#endif //JADA_TABLESTRUCTURE_H
