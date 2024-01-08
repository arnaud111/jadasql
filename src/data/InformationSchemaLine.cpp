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
DataType *InformationSchemaLine::dataTypeDT = new TinyInt();
DataType *InformationSchemaLine::sizeDT = new Int();
DataType *InformationSchemaLine::defaultValueDT = new VarChar(256);
DataType *InformationSchemaLine::notNullDT = new Boolean();
DataType *InformationSchemaLine::autoIncrementDT = new Boolean();

InformationSchemaLine::InformationSchemaLine(ColumnDetail * column, std::string table, std::string database) {

    this->database = std::move(database);
    this->table = std::move(table);
    this->column = column->name->columnName;
    this->autoIncrement = column->autoIncrement;
    this->notNull = column->notNull;
    this->dataType = column->dataType->type;
    this->size = column->dataType->size;

    this->database.push_back(0);
    this->table.push_back(0);
    this->column.push_back(0);

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

InsertableRow *InformationSchemaLine::toInsertableRow() {

    std::vector<InsertableField *> insertableFields;

    insertableFields.push_back(databaseToInsertableField());
    insertableFields.push_back(tableToInsertableField());
    insertableFields.push_back(columnToInsertableField());
    insertableFields.push_back(dataTypeToInsertableField());
    insertableFields.push_back(sizeToInsertableField());
    insertableFields.push_back(defaultValueToInsertableField());
    insertableFields.push_back(notNullToInsertableField());
    insertableFields.push_back(autoIncrementToInsertableField());

    return new InsertableRow(insertableFields);
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
    TableStructure::selectAllInTable("information_schema", "columns", {});
    return {};
}
