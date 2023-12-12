//
// Created by nono on 11/12/23.
//

#include <sys/stat.h>
#include <filesystem>
#include "../../include/data/DatabaseStructure.h"

const std::string DatabaseStructure::BASE_DATA_PATH = "./data/";

bool DatabaseStructure::createDatabase(const std::string& name) {

    std::string dir = BASE_DATA_PATH + name;
    int created;

    if (databaseExist(name)) {
        return false;
    }

    created = mkdir(dir.c_str(), 0777);

    return !created;
}

std::vector<std::vector<std::string>> DatabaseStructure::getListDatabase() {

    std::vector<std::vector<std::string>> listDatabases;

    for(auto& element : std::filesystem::recursive_directory_iterator(BASE_DATA_PATH)) {
        if (element.is_directory()) {
            listDatabases.push_back({element.path().filename().string()});
        }
    }

    return listDatabases;
}

bool DatabaseStructure::databaseExist(const std::string& name) {

    std::string dir = BASE_DATA_PATH + name;

    struct stat sb {};

    return !stat(dir.c_str(), &sb);
}
