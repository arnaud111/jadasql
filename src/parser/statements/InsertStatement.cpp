//
// Created by nono on 13/11/2023.
//

#include "../../../include/parser/tree/statements/InsertStatement.h"
#include "../../../include/error/Error.h"
#include "../../../include/lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../include/lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../include/lexer/symbol/value/IdentifierSymbol.h"

InsertStatement::InsertStatement(std::vector<Symbol *> symbols) {
    std::vector<Symbol *> tmpSymbolsArray;
    std::vector<std::vector<Symbol *>> columnList;
    std::vector<std::vector<Symbol *>> rowList;
    unsigned long long index = 2;

    this->statementType = Insert;
    this->tableReference = nullptr;
    this->columnsExplicit = false;

    if (symbols.size() < 4) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[1])->keyword != k_Into) {
        Error::syntaxError("Expected INSERT INTO");
    }

    tmpSymbolsArray = Statement::splitUntilParenthesisOrKeyword(symbols, index, {k_Values});
    this->tableReference = new TableReference(tmpSymbolsArray);
    index += tmpSymbolsArray.size();

    if (symbols[index]->symbolValueType == s_Delimiter) {
        this->columnsExplicit = true;

        tmpSymbolsArray = getInParenthesis(index, symbols);
        columnList = Statement::splitComa(tmpSymbolsArray);

        for (auto & column : columnList) {
            if (column.size() != 1 || column[0]->symbolValueType != s_Identifier) {
                Error::syntaxError(", ");
            }
            this->columns.push_back(new ColumnReference(((IdentifierSymbol *) column[0])->value));
        }

        index += tmpSymbolsArray.size() + 2;
    }

    if (symbols[index]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[index])->keyword != k_Values) {
        Error::syntaxError("Expected VALUES");
    }

    if (++index == symbols.size()) {
        Error::syntaxError("Expected VALUES data");
    }

    rowList = Statement::splitComa(Statement::cut_symbol_vector(symbols, index, symbols.size()));

    for (auto & row: rowList) {
        tmpSymbolsArray = getInParenthesis(0, row);
        this->values.push_back(Field::createListField(tmpSymbolsArray));
    }

    if (this->values.empty()) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }
}

std::vector<Symbol *> InsertStatement::getInParenthesis(unsigned long long start, std::vector<Symbol *> symbols) {
    std::vector<Symbol *> list;
    int parenthesisCount = 1;

    if (symbols[start]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[start])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[start]);
    }

    for (unsigned long long i = start + 1; i < symbols.size(); i++) {
        if (symbols[i]->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisLeft) {
                parenthesisCount++;
            } else if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisRight) {
                parenthesisCount--;
            }
        }
        if (parenthesisCount == 0) {
            break;
        }
        list.push_back(symbols[i]);
    }
    if (parenthesisCount != 0) {
        Error::syntaxError("Expected ')'");
    }

    return list;
}

ReturnedValue *InsertStatement::execute() {
    return nullptr;
}
