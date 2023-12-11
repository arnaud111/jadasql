//
// Created by nono on 13/11/2023.
//

#include "../../../include/parser/tree/statements/DeleteStatement.h"
#include "../../../include/error/Error.h"
#include "../../../include/lexer/symbol/keyword/KeywordSymbol.h"

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

ReturnedValue *DeleteStatement::execute() {
    return nullptr;
}
