//
// Created by nono on 13/11/2023.
//

#include "parser/tree/statements/CreateStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "parser/tree/structure/DatabaseReference.h"
#include "parser/tree/structure/TableReference.h"
#include "lexer/symbol/keyword/DelimiterSymbol.h"
#include "parser/tree/column_actions/ColumnConstraints.h"
#include "data/DatabaseStructure.h"
#include "data/TableStructure.h"
#include "data/InformationSchemaLine.h"

CreateStatement::CreateStatement(std::vector<Symbol *> symbols) {

    this->createdField = nullptr;
    this->ifNotExist = false;
    this->statementType = Create;

    if (symbols.size() < 3) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    } if (symbols[1]->symbolValueType != s_Keyword) {
        Error::syntaxError(symbols[1]);
    }

    switch (((KeywordSymbol *) symbols[1])->keyword) {
        case k_Table:
            this->type = CreateTable;
            this->createTable(symbols);
            break;
        case k_Database:
            this->type = CreateDatabase;
            this->createDatabase(symbols);
            break;
        default:
            Error::syntaxError(symbols[1]);
            break;
    }
}

void CreateStatement::createTable(std::vector<Symbol *> symbols) {

    unsigned long long index = 2;
    std::vector<Symbol *> tmpSymbolList;

    if (symbols.size() > 5) {
        if (symbols[2]->symbolValueType == s_Keyword &&
            symbols[3]->symbolValueType == s_Keyword &&
            symbols[4]->symbolValueType == s_Keyword &&
            ((KeywordSymbol *)symbols[2])->keyword == k_If &&
            ((KeywordSymbol *)symbols[3])->keyword == k_Not &&
            ((KeywordSymbol *)symbols[4])->keyword == k_Exists) {
            this->ifNotExist = true;
            index = 5;
        }
    }

    tmpSymbolList = Statement::splitUntilParenthesisOrKeyword(symbols, index, {});
    this->createdField = new TableReference(tmpSymbolList);
    index += tmpSymbolList.size();

    if (symbols[index]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[index])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[index]);
    } if (symbols[symbols.size() - 1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, index + 1, symbols.size() - 1);

    for (auto &col: Statement::splitComa(tmpSymbolList)) {
        if (col.empty()) {
            Error::syntaxError("After CREATE TABLE");
        }
        this->columns.push_back(ColumnCreationInfo::convertToColumnCreationInfo(col));
    }
}

void CreateStatement::createDatabase(std::vector<Symbol *> symbols) {

    char index = 2;

    if (symbols.size() > 5) {
        if (symbols[2]->symbolValueType == s_Keyword &&
            symbols[3]->symbolValueType == s_Keyword &&
            symbols[4]->symbolValueType == s_Keyword &&
            ((KeywordSymbol *)symbols[2])->keyword == k_If &&
            ((KeywordSymbol *)symbols[3])->keyword == k_Not &&
            ((KeywordSymbol *)symbols[4])->keyword == k_Exists) {
            this->ifNotExist = true;
            index = 5;
        }
    }

    this->createdField = new DatabaseReference(Statement::cut_symbol_vector(symbols, index, symbols.size()));
}

ReturnedValue *CreateStatement::execute(ExecutionData *executionData) {
    if (this->type == CreateTable)
        return executeCreateTable(executionData);
    return executeCreateDatabase(executionData);
}

ReturnedValue *CreateStatement::executeCreateDatabase(ExecutionData *executionData) const {

    bool created = DatabaseStructure::createDatabase(((DatabaseReference *) this->createdField)->databaseName);

    if (!created) {
        if (this->ifNotExist) {
            return ReturnedValue::rowCount(0);
        }
        Error::runtimeError("Database already exist");
    }

    return ReturnedValue::rowCount(1);
}

ReturnedValue *CreateStatement::executeCreateTable(ExecutionData *executionData) const {

    std::string database = executionData->databaseUsed;

    if (((TableReference *) this->createdField)->databaseReference != nullptr) {
        database = ((TableReference *) this->createdField)->databaseReference->databaseName;
    }

    if (database.empty()) {
        Error::runtimeError("No Database Selected");
    }
    if (!DatabaseStructure::databaseExist(database)) {
        Error::runtimeError("Database Does Not Exist");
    }

    if (TableStructure::tableExist(database, ((TableReference *) this->createdField)->tableName)) {
        if (this->ifNotExist) {
            return ReturnedValue::rowCount(0);
        } else {
            Error::runtimeError("Table already exist");
        }
    }

    TableStructure::createTable(database, ((TableReference *) this->createdField)->tableName);

    for (auto column : this->columns) {
        if (column->columnCreationType == t_ColumnDetail) {
            auto *line = new InformationSchemaLine((ColumnDetail *) column, ((TableReference *) this->createdField)->tableName, database);
            TableStructure::insertRow("information_schema", "columns", line->toInsertableRow());
        }
    }

    return ReturnedValue::rowCount(1);
}
