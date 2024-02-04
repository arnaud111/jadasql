//
// Created by nono on 16/10/2023.
//

#include "parser/tree/statements/SelectStatement.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "lexer/symbol/value/NumberSymbol.h"
#include "error/Error.h"
#include "data/DatabaseStructure.h"
#include "data/TableStructure.h"
#include "data/InformationSchemaLine.h"
#include "parser/tree/field/ConstStringField.h"
#include "parser/tree/field/ConstNumberField.h"
#include "interpreter/values/ReturnedBool.h"

SelectStatement::SelectStatement(const std::vector<Symbol *> &symbols) : Statement() {
    std::vector<Symbol *> splitSymbols;
    int index = 1;

    if (symbols.size() < 2) {
        Error::syntaxError("SELECT");
    }

    this->statementType = Select;
    this->from = nullptr;
    this->where = nullptr;
    this->asc = true;
    this->limit = -1;
    this->distinct = SelectStatement::isDistinct(symbols);

    if (this->distinct) {
        index = 2;
    }

    splitSymbols = SelectStatement::splitUntilKeywords(symbols, index, {k_From, k_Where, k_Group, k_Order, k_Limit});
    this->field = Field::createListField(splitSymbols);
    index += (int) splitSymbols.size();

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_From) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {k_Where, k_Group, k_Order, k_Limit});
        this->from = new From(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_Where) {
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {k_Group, k_Order, k_Limit});
        this->where = Field::convertToField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_Group) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword ||
            ((KeywordSymbol *) symbols[index])->keyword != k_By) {
            Error::syntaxError("GROUP");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {k_Order, k_Limit});
        this->groupBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_Order) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Keyword ||
            ((KeywordSymbol *) symbols[index])->keyword != k_By) {
            Error::syntaxError("ORDER");
        }
        splitSymbols = SelectStatement::splitUntilKeywords(symbols, index + 1, {k_Limit, k_Asc, k_Desc});
        this->orderBy = Field::createListField(splitSymbols);
        index += (int) splitSymbols.size() + 1;
        if (index == symbols.size()) return;
        if (((KeywordSymbol *) symbols[index])->keyword == k_Desc) {
            this->asc = false;
            index++;
        } else if (((KeywordSymbol *) symbols[index])->keyword == k_Asc) {
            index++;
        }
    }

    if (index == symbols.size()) return;

    if (((KeywordSymbol *) symbols[index])->keyword == k_Limit) {
        index++;
        if (index == symbols.size() || symbols[index]->symbolValueType != s_Number) {
            Error::syntaxError("LIMIT");
        }
        this->limit = ((NumberSymbol *) symbols[index])->value;
        if (this->limit < 0) {
            Error::syntaxError("LIMIT");
        }
    }

    if (index + 1 != symbols.size()) {
        Error::syntaxError("After SELECT");
    }
}

bool SelectStatement::isDistinct(std::vector<Symbol *> symbols) {
    if (symbols[1]->symbolValueType == s_Keyword) {
        if (((KeywordSymbol *) symbols[1])->keyword == k_Distinct) {
            return true;
        }
        Error::syntaxError("SELECT");
    }
    return false;
}

ReturnedValue *SelectStatement::execute(ExecutionData *executionData) {

    std::string database;
    std::vector<InformationSchemaLine *> columnsInformation;
    std::vector<std::string> columnsNameReturned;
    std::vector<std::string> columnsName;
    std::vector<std::vector<std::string>> columnData;
    std::vector<std::string> columnDataTmp;
    std::vector<std::vector<Field *>> columnDataFields;
    std::vector<DataType *> dataTypes;
    std::vector<int> indexReturned;
    bool found;

    if (((TableReference *) this->from->table)->databaseReference != nullptr) {
        database = ((TableReference *) this->from->table)->databaseReference->databaseName;
    }

    if (database.empty()) {
        Error::runtimeError("No Database Selected");
    }
    if (!DatabaseStructure::databaseExist(database)) {
        Error::runtimeError("Database Does Not Exist");
    }

    if (!TableStructure::tableExist(database, ((TableReference *) this->from->table)->tableName)) {
        Error::runtimeError("Table Does Not Exist");
    }

    columnsInformation = InformationSchemaLine::get_information_schema_for_table(database, ((TableReference *) this->from->table)->tableName);

    for (auto &selected: this->field) {
        if (selected->fieldType != f_Column) {
            Error::runtimeError("Not implemented");
        }

        columnsNameReturned.push_back(((ColumnReference *) selected)->columnName);
        found = false;
        for (int i = 0; i < columnsInformation.size(); i++) {
            if (columnsInformation[i]->column == ((ColumnReference *) selected)->columnName) {
                found = true;
                indexReturned.push_back(i);
            }
        }

        if (!found) {
            Error::runtimeError("Column not found");
        }
    }

    dataTypes.reserve(columnsInformation.size());
    for (auto &information: columnsInformation) {
        dataTypes.push_back(DataType::convertToDataType(information->dataType, information->size));
        columnsName.push_back(information->column);
    }

    columnDataFields = TableStructure::selectAllInTable(database, ((TableReference *) this->from->table)->tableName, dataTypes);

    for (auto &dataField: columnDataFields) {
        if (this->where == nullptr || ((ReturnedBool *) ((Operation *) this->where)->executeWhere(dataField, columnsName))->value) {
            columnDataTmp = {};
            for (auto &index: indexReturned) {
                if (dataField[index]->fieldType == f_ConstString) {
                    columnDataTmp.push_back(((ConstStringField *) dataField[index])->value);
                } else {
                    columnDataTmp.push_back(std::to_string(((ConstNumberField *) dataField[index])->value));
                }
            }
            columnData.push_back(columnDataTmp);
        }
    }

    return ReturnedValue::rowData(columnsNameReturned, columnData);
}
