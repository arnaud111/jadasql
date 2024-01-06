//
// Created by nono on 12/12/23.
//

#include "parser/tree/statements/UseStatement.h"
#include "error/Error.h"
#include "lexer/symbol/value/IdentifierSymbol.h"
#include "data/DatabaseStructure.h"


UseStatement::UseStatement(std::vector<Symbol *> symbols) {

    if (symbols.size() != 2) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Identifier) {
        Error::syntaxError(symbols[1]);
    }

    this->database = new DatabaseReference(((IdentifierSymbol *) symbols[1])->value);
}

ReturnedValue *UseStatement::execute(ExecutionData *executionData) {

    std::vector<std::string> databases = DatabaseStructure::getListDatabase();

    for (auto &databaseName: databases) {
        if (databaseName == this->database->databaseName) {
            executionData->databaseUsed = this->database->databaseName;
            return ReturnedValue::none();
        }
    }

    Error::syntaxError("Database does not exist");

    return nullptr;
}
