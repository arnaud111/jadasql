//
// Created by nono on 19/12/2023.
//

#ifndef JADA_INFORMATIONSCHEMALINE_H
#define JADA_INFORMATIONSCHEMALINE_H

#include <string>
#include <vector>
#include "parser/tree/column_actions/ColumnDetail.h"
#include "InsertableRow.h"

class InformationSchemaLine {

public:

    std::string database;
    std::string table;
    std::string column;
    DataTypeEnum dataType;
    int size;
    std::string defaultValue;
    bool notNull;
    bool autoIncrement;

    explicit InformationSchemaLine(ColumnDetail * column, std::string table, std::string database);

    explicit InformationSchemaLine(std::vector<Field *> data);

    InsertableRow *toInsertableRow();

    static std::vector<InformationSchemaLine *> get_all_information_schema();

    void display() const;

private:

    static DataType *databaseDT;
    static DataType *tableDT;
    static DataType *columnDT;
    static DataType *dataTypeDT;
    static DataType *sizeDT;
    static DataType *defaultValueDT;
    static DataType *notNullDT;
    static DataType *autoIncrementDT;

    InsertableField *databaseToInsertableField() const;

    InsertableField *tableToInsertableField() const;

    InsertableField *columnToInsertableField() const;

    InsertableField *dataTypeToInsertableField() const;

    InsertableField *sizeToInsertableField() const;

    InsertableField *defaultValueToInsertableField() const;

    InsertableField *notNullToInsertableField() const;

    InsertableField *autoIncrementToInsertableField() const;

    static std::vector<DataType *> get_all_data_types();
};

#endif //JADA_INFORMATIONSCHEMALINE_H
