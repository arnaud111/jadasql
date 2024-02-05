//
// Created by nono on 13/11/2023.
//

#include "parser/tree/statements/DeleteStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "data/DatabaseStructure.h"
#include "data/TableStructure.h"
#include "data/InformationSchemaLine.h"
#include "parser/tree/operation/Operation.h"
#include "interpreter/values/ReturnedBool.h"

DeleteStatement::DeleteStatement(std::vector<Symbol *> symbols) {

    this->statementType = Delete;
    this->table = nullptr;
    this->where = nullptr;

    if (symbols.size() < 3) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[1])->keyword != k_From) {
        Error::syntaxError(symbols[1]);
    }

    std::vector<Symbol *> tableSymbols = Statement::splitUntilKeywords(symbols, 2, {k_Where});
    this->table = new TableReference(tableSymbols);
    if (symbols.size() > tableSymbols.size() + 2) {
        if (symbols.size() == tableSymbols.size() + 3) {
            Error::syntaxError(symbols[symbols.size() - 1]);
        }
        if (symbols[tableSymbols.size() + 2]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[tableSymbols.size() + 2])->keyword != k_Where) {
            Error::syntaxError(symbols[tableSymbols.size() + 2]);
        }
        this->where = Field::convertToField(Statement::cut_symbol_vector(symbols, tableSymbols.size() + 3, symbols.size()));
    }
}

ReturnedValue *DeleteStatement::execute(ExecutionData *executionData) {

    std::string database;
    std::vector<InformationSchemaLine *> columnsInformation;
    std::vector<std::string> columnsName;
    std::vector<DataType *> dataTypes;
    std::vector<std::vector<Field *>> columnDataFields;
    std::vector<InsertableRow *> columnData;
    std::vector<InsertableField *> rowInsertable;
    int rowAffected = 0;

    if (((TableReference *) this->table)->databaseReference != nullptr) {
        database = ((TableReference *) this->table)->databaseReference->databaseName;
    }

    if (database.empty()) {
        Error::runtimeError("No Database Selected");
    }
    if (!DatabaseStructure::databaseExist(database)) {
        Error::runtimeError("Database Does Not Exist");
    }

    if (!TableStructure::tableExist(database, ((TableReference *) this->table)->tableName)) {
        Error::runtimeError("Table Does Not Exist");
    }

    columnsInformation = InformationSchemaLine::get_information_schema_for_table(database, ((TableReference *) this->table)->tableName);

    dataTypes.reserve(columnsInformation.size());
    for (auto &information: columnsInformation) {
        dataTypes.push_back(DataType::convertToDataType(information->dataType, information->size));
        columnsName.push_back(information->column);
    }

    columnDataFields = TableStructure::selectAllInTable(database, ((TableReference *) this->table)->tableName, dataTypes);

    for (auto &dataField: columnDataFields) {
        if (this->where != nullptr && !((ReturnedBool *) ((Operation *) this->where)->executeWhere(dataField, columnsName))->value) {
            rowInsertable = {};
            for (int i = 0; i < dataField.size(); i++) {
                rowInsertable.push_back(new InsertableField(dataTypes[i], dataField[i]));
            }
            columnData.push_back(new InsertableRow(rowInsertable));
        } else {
            rowAffected++;
        }
    }

    TableStructure::replace(database, ((TableReference *) this->table)->tableName, columnData);

    return ReturnedValue::rowCount(rowAffected);
}
