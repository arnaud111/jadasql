//
// Created by nono on 12/12/23.
//

#include "parser/tree/statements/ShowStatement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "data/DatabaseStructure.h"
#include "data/TableStructure.h"


ShowStatement::ShowStatement(std::vector<Symbol *> symbols) {

    if (symbols.size() != 2) {
        Error::syntaxError(symbols[0]);
    }

    switch (((KeywordSymbol *) symbols[1])->keyword) {
        case k_Databases:
            this->type = ShowDatabases;
            break;
        case k_Tables:
            this->type = ShowTables;
            break;
        default:
            Error::syntaxError(symbols[1]);
            break;
    }
}

ReturnedValue *ShowStatement::execute(ExecutionData *executionData) {

    switch (this->type) {
        case ShowDatabases:
            return ReturnedValue::rowData("Databases", DatabaseStructure::getListDatabase());
        case ShowTables:
            if (executionData->databaseUsed.empty()) {
                Error::runtimeError("No Database Selected");
            }
            return ReturnedValue::rowData("Tables", TableStructure::getListTable(executionData->databaseUsed));
    }

    return ReturnedValue::none();
}
