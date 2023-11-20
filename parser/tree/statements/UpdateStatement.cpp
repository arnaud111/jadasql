//
// Created by nono on 13/11/2023.
//

#include "UpdateStatement.h"
#include "../../../error/Error.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"

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
