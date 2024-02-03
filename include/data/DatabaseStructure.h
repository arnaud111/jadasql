//
// Created by nono on 11/12/23.
//

#ifndef JADA_DATABASESTRUCTURE_H
#define JADA_DATABASESTRUCTURE_H

#include <string>
#include <vector>

class DatabaseStructure {

public:

    static const std::string BASE_DATA_PATH;

    static bool createDatabase(const std::string& name);

    static bool removeDatabase(const std::string& name);

    static std::vector<std::string> getListDatabase();

    static bool databaseExist(const std::string& name);

};

#endif //JADA_DATABASESTRUCTURE_H
