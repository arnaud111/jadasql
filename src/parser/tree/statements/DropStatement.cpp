//
// Created by nono on 13/11/2023.
//

#include "parser/tree/statements/DropStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "parser/tree/structure/DatabaseReference.h"
#include "lexer/symbol/value/IdentifierSymbol.h"
#include "parser/tree/structure/TableReference.h"
#include "data/TableStructure.h"
#include "data/DatabaseStructure.h"

DropStatement::DropStatement(const std::vector<Symbol *> &symbols) {

    int field_pos = 2;
    this->statementType = Drop;
    this->ifExist = false;
    this->droppedField = nullptr;

    if (symbols.size() < 3) {
        Error::syntaxError("DROP");
    }

    this->type = getDropType(symbols[1]);

    if (symbols.size() > 4 && symbols[2]->symbolValueType == s_Keyword && symbols[3]->symbolValueType == s_Keyword
        && ((KeywordSymbol *) symbols[2])->keyword == k_If && ((KeywordSymbol *) symbols[3])->keyword == k_Exists) {
        this->ifExist = true;
        field_pos += 2;
    }

    if (this->type == DropDatabase) {
        if (symbols.size() != field_pos + 1) {
            Error::syntaxError(symbols[symbols.size() - 1]);
        }
        if (symbols[field_pos]->symbolValueType == s_Identifier) {
            this->droppedField = new DatabaseReference(((IdentifierSymbol *) symbols[field_pos])->value);
        }
    } else {
        if (symbols.size() != field_pos + 1 && symbols.size() != field_pos + 3) {
            Error::syntaxError(symbols[symbols.size() - 1]);
        }
        this->droppedField = new TableReference(Statement::cut_symbol_vector(symbols, field_pos, symbols.size()));
    }

    if (this->droppedField == nullptr) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }
}

DropStatementTypeEnum DropStatement::getDropType(Symbol *symbol) {
    if (symbol->symbolValueType != s_Keyword) {
        Error::syntaxError(symbol);
    }

    if (((KeywordSymbol *) symbol)->keyword == k_Table) {
        return DropTable;
    } if (((KeywordSymbol *) symbol)->keyword == k_Database) {
        return DropDatabase;
    }

    Error::syntaxError(symbol);
    return DropTable;
}

ReturnedValue *DropStatement::execute(ExecutionData *executionData) {

    std::string database = executionData->databaseUsed;

    switch (this->type) {
        case DropTable:
            if (((TableReference *) this->droppedField)->databaseReference != nullptr) {
                database = ((TableReference *) this->droppedField)->databaseReference->databaseName;
            }

            if (database.empty()) {
                Error::runtimeError("No Database Selected");
            }
            if (!DatabaseStructure::databaseExist(database)) {
                Error::runtimeError("Database Does Not Exist");
            }

            if (TableStructure::removeTable(database, ((TableReference *) this->droppedField)->tableName)) {
                return ReturnedValue::rowCount(1);
            }
            break;
        case DropDatabase:
            if (!DatabaseStructure::databaseExist(((DatabaseReference *) this->droppedField)->databaseName)) {
                Error::runtimeError("Database Does Not Exist");
            }
            if (DatabaseStructure::removeDatabase(((DatabaseReference *) this->droppedField)->databaseName)) {
                return ReturnedValue::rowCount(1);
            }
            break;
    }

    return ReturnedValue::rowCount(0);
}
