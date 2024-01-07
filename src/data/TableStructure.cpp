//
// Created by nono on 11/12/23.
//

#include <sys/stat.h>
#include <filesystem>
#include <fstream>
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
    std::string file = DatabaseStructure::BASE_DATA_PATH + database + "/" + name + ".tb";

    struct stat sb {};

    return !stat(file.c_str(), &sb);
}

bool TableStructure::createTable(const std::string &database, const std::string &table) {

    std::string fileName = DatabaseStructure::BASE_DATA_PATH + database + "/" + table;

    std::ofstream tableFile(fileName.c_str());
    tableFile.close();

    return true;
}

void TableStructure::insertRow(const std::string& database, const std::string& table, InsertableRow *insertableRow) {

    std::string fileName = DatabaseStructure::BASE_DATA_PATH + database + "/" + table;

    std::ofstream file(fileName, std::ios::binary);

    for (auto & insertableField : insertableRow->listField) {
        file.write(insertableField->to_writable(), insertableField->size_of());
    }

    file.close();
}
