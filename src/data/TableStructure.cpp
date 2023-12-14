//
// Created by nono on 11/12/23.
//

#include <sys/stat.h>
#include <filesystem>
#include "../../include/data/TableStructure.h"
#include "data/DatabaseStructure.h"

std::vector<std::string> TableStructure::getListTable(const std::string& database) {

    std::vector<std::string> listTable;

    for(auto& element : std::filesystem::recursive_directory_iterator(DatabaseStructure::BASE_DATA_PATH + database)) {
        if (element.is_regular_file()) {
            listTable.push_back(element.path().filename().string());
        }
    }

    return listTable;
}

bool TableStructure::tableExist(const std::string& database, const std::string &name) {
    std::string file = DatabaseStructure::BASE_DATA_PATH + database + "/" + name;

    struct stat sb {};

    return !stat(file.c_str(), &sb);
}
