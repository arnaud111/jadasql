//
// Created by nono on 13/11/2023.
//

#include "parser/tree/statements/UpdateStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "data/TableStructure.h"
#include "parser/tree/operation/Operation.h"
#include "interpreter/values/ReturnedBool.h"
#include "data/InformationSchemaLine.h"
#include "data/DatabaseStructure.h"

UpdateStatement::UpdateStatement(std::vector<Symbol *> symbols) {
    std::vector<Symbol *> tmpArraySymbol;
    unsigned long long index = 1;

    this->statementType = Update;
    this->where = nullptr;
    this->tableReference = nullptr;

    if (symbols.size() < 6) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpArraySymbol = Statement::splitUntilKeywords(symbols, index, {k_Set});
    this->tableReference = new TableReference(tmpArraySymbol);

    if (index + tmpArraySymbol.size() == symbols.size()) {
        Error::syntaxError("SET not found");
    }
    index += tmpArraySymbol.size() + 1;

    tmpArraySymbol = Statement::splitUntilKeywords(symbols, index, {k_Where});
    this->set = Assign::convert_to_list_assign(tmpArraySymbol);

    index += tmpArraySymbol.size();
    if (symbols.size() > index) {
        tmpArraySymbol = Statement::cut_symbol_vector(symbols, index + 1, symbols.size());
        this->where = Field::convertToField(tmpArraySymbol);
    }
}

ReturnedValue *UpdateStatement::execute(ExecutionData *executionData) {

    std::string database;
    std::vector<InformationSchemaLine *> columnsInformation;
    std::vector<std::string> columnsName;
    std::vector<DataType *> dataTypes;
    std::vector<std::vector<Field *>> columnDataFields;
    std::vector<InsertableRow *> columnData;
    std::vector<InsertableField *> rowInsertable;
    Field *newValue;
    int rowAffected = 0;

    if (((TableReference *) this->tableReference)->databaseReference != nullptr) {
        database = ((TableReference *) this->tableReference)->databaseReference->databaseName;
    }

    if (database.empty()) {
        Error::runtimeError("No Database Selected");
    }
    if (!DatabaseStructure::databaseExist(database)) {
        Error::runtimeError("Database Does Not Exist");
    }

    if (!TableStructure::tableExist(database, ((TableReference *) this->tableReference)->tableName)) {
        Error::runtimeError("Table Does Not Exist");
    }

    columnsInformation = InformationSchemaLine::get_information_schema_for_table(database, ((TableReference *) this->tableReference)->tableName);

    dataTypes.reserve(columnsInformation.size());
    for (auto &information: columnsInformation) {
        dataTypes.push_back(DataType::convertToDataType(information->dataType, information->size));
        columnsName.push_back(information->column);
    }

    columnDataFields = TableStructure::selectAllInTable(database, ((TableReference *) this->tableReference)->tableName, dataTypes);

    for (auto &dataField: columnDataFields) {
        if (this->where == nullptr || ((ReturnedBool *) ((Operation *) this->where)->executeWhere(dataField, columnsName))->value) {
            rowInsertable = {};
            for (int i = 0; i < dataField.size(); i++) {
                newValue = dataField[i];
                for (auto &change: this->set) {
                    if (change->column->columnName == columnsInformation[i]->column) {
                        if (change->value->fieldType != newValue->fieldType) {
                            Error::runtimeError("Not implemented");
                        }
                        newValue = change->value;
                    }
                }
                rowInsertable.push_back(new InsertableField(dataTypes[i], newValue));
            }
            columnData.push_back(new InsertableRow(rowInsertable));
            rowAffected++;
        } else {
            rowInsertable = {};
            for (int i = 0; i < dataField.size(); i++) {
                rowInsertable.push_back(new InsertableField(dataTypes[i], dataField[i]));
            }
            columnData.push_back(new InsertableRow(rowInsertable));
        }
    }

    TableStructure::replace(database, ((TableReference *) this->tableReference)->tableName, columnData);

    return ReturnedValue::rowCount(rowAffected);
}
