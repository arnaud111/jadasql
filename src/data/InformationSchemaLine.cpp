//
// Created by nono on 19/12/2023.
//

#include <utility>

#include "../../include/data/InformationSchemaLine.h"
#include "error/Error.h"
#include "parser/tree/field/ConstNumberField.h"
#include "parser/tree/field/ConstStringField.h"
#include "parser/tree/datatype/VarChar.h"
#include "parser/tree/datatype/TinyInt.h"
#include "parser/tree/datatype/Int.h"
#include "parser/tree/datatype/Boolean.h"
#include "data/TableStructure.h"

DataType *InformationSchemaLine::databaseDT = new VarChar(256);
DataType *InformationSchemaLine::tableDT = new VarChar(256);
DataType *InformationSchemaLine::columnDT = new VarChar(256);
DataType *InformationSchemaLine::dataTypeDT = new Int();
DataType *InformationSchemaLine::sizeDT = new Int();
DataType *InformationSchemaLine::defaultValueDT = new VarChar(256);
DataType *InformationSchemaLine::notNullDT = new Int();
DataType *InformationSchemaLine::autoIncrementDT = new Int();

InformationSchemaLine::InformationSchemaLine(ColumnDetail * column, std::string table, std::string database) {

    this->database = std::move(database);
    this->table = std::move(table);
    this->column = column->name->columnName;
    this->autoIncrement = column->autoIncrement;
    this->notNull = column->notNull;
    this->dataType = column->dataType->type;
    this->size = column->dataType->size;

    if (column->defaultValue != nullptr) {
        switch (column->defaultValue->fieldType) {
            case f_ConstString:
                this->defaultValue = "NULL";
                break;
            case f_ConstNumber:
                this->defaultValue = std::to_string(((ConstNumberField *) column->defaultValue)->value);
                break;
            case f_Null:
                this->defaultValue = ((ConstStringField *) column->defaultValue)->value;
                break;
            default:
                Error::runtimeError("Default value must be a constant value");
                break;
        }
    }
}

InformationSchemaLine::InformationSchemaLine(std::vector<Field *> data) {

//    if (data.size() != 8) {
    if (data.size() != 7) {
        Error::runtimeError("Data size doesn't match");
    }

    if (data[0]->fieldType != f_ConstString
    || data[1]->fieldType != f_ConstString
    || data[2]->fieldType != f_ConstString
    || data[3]->fieldType != f_ConstNumber
    || data[4]->fieldType != f_ConstNumber
    //|| data[5]->fieldType != f_ConstString
    || data[5]->fieldType != f_ConstNumber
    || data[6]->fieldType != f_ConstNumber) {
        Error::runtimeError("Data types doesn't match");
    }

    this->database = ((ConstStringField *) data[0])->value;
    this->table = ((ConstStringField *) data[1])->value;
    this->column = ((ConstStringField *) data[2])->value;
    this->dataType = static_cast<DataTypeEnum>(((ConstNumberField *) data[3])->value);
    this->size = ((ConstNumberField *) data[4])->value;
    //this->defaultValue = ((ConstStringField *) data[5])->value;
    this->defaultValue = "";
    this->notNull = ((ConstNumberField *) data[5])->value;
    this->autoIncrement = ((ConstNumberField *) data[6])->value;
}

InsertableRow *InformationSchemaLine::toInsertableRow() {

    std::vector<InsertableField *> insertableFields;

    insertableFields.push_back(databaseToInsertableField());
    insertableFields.push_back(tableToInsertableField());
    insertableFields.push_back(columnToInsertableField());
    insertableFields.push_back(dataTypeToInsertableField());
    insertableFields.push_back(sizeToInsertableField());
    //insertableFields.push_back(defaultValueToInsertableField());
    insertableFields.push_back(notNullToInsertableField());
    insertableFields.push_back(autoIncrementToInsertableField());

    return new InsertableRow(insertableFields);
}

std::vector<DataType *> InformationSchemaLine::get_all_data_types() {
    return {
            InformationSchemaLine::databaseDT,
            InformationSchemaLine::tableDT,
            InformationSchemaLine::columnDT,
            InformationSchemaLine::dataTypeDT,
            InformationSchemaLine::sizeDT,
            //InformationSchemaLine::defaultValueDT,
            InformationSchemaLine::notNullDT,
            InformationSchemaLine::autoIncrementDT,
    };
}

InsertableField *InformationSchemaLine::databaseToInsertableField() const {

    auto *value = new ConstStringField(this->database);

    return new InsertableField(databaseDT, value);
}

InsertableField *InformationSchemaLine::tableToInsertableField() const {

    auto *value = new ConstStringField(this->table);

    return new InsertableField(tableDT, value);
}

InsertableField *InformationSchemaLine::columnToInsertableField() const {

    auto *value = new ConstStringField(this->column);

    return new InsertableField(columnDT, value);
}

InsertableField *InformationSchemaLine::dataTypeToInsertableField() const {

    auto *value = new ConstNumberField(this->dataType);

    return new InsertableField(dataTypeDT, value);
}

InsertableField *InformationSchemaLine::sizeToInsertableField() const {

    auto *value = new ConstNumberField(this->size);

    return new InsertableField(sizeDT, value);
}

InsertableField *InformationSchemaLine::defaultValueToInsertableField() const {

    auto *value = new ConstStringField(this->defaultValue);

    return new InsertableField(defaultValueDT, value);
}

InsertableField *InformationSchemaLine::notNullToInsertableField() const {

    auto *value = new ConstNumberField(this->notNull);

    return new InsertableField(notNullDT, value);
}

InsertableField *InformationSchemaLine::autoIncrementToInsertableField() const {

    auto *value = new ConstNumberField(this->autoIncrement);

    return new InsertableField(autoIncrementDT, value);
}

std::vector<InformationSchemaLine *> InformationSchemaLine::get_all_information_schema() {
    std::vector<std::vector<Field *>> lines = TableStructure::selectAllInTable("information_schema", "columns", InformationSchemaLine::get_all_data_types());
    std::vector<InformationSchemaLine *> informationSchemaLines;

    informationSchemaLines.reserve(lines.size());
    for (auto &line: lines) {
        informationSchemaLines.push_back(new InformationSchemaLine(line));
    }

    return informationSchemaLines;
}

std::vector<InformationSchemaLine *> InformationSchemaLine::get_information_schema_for_table(std::string database, std::string table) {
    std::vector<std::vector<Field *>> lines = TableStructure::selectAllInTable("information_schema", "columns", InformationSchemaLine::get_all_data_types());
    std::vector<InformationSchemaLine *> informationSchemaLines;
    InformationSchemaLine *tmpLine;

    informationSchemaLines.reserve(lines.size());
    for (auto &line: lines) {
        tmpLine = new InformationSchemaLine(line);
        if (tmpLine->database == database && tmpLine->table == table) {
            informationSchemaLines.push_back(tmpLine);
        }
    }

    return informationSchemaLines;
}

void InformationSchemaLine::display() const {
    printf("database: %s, table: %s, column: %s, data type: %d, size: %d, default value: %s, not null: %d, auto increment: %d\n", this->database.c_str(), this->table.c_str(), this->column.c_str(), this->dataType, this->size, this->defaultValue.c_str(), this->notNull, this->autoIncrement);
}
