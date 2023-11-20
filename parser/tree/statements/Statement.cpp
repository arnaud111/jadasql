//
// Created by nono on 16/10/2023.
//

#include "Statement.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../error/Error.h"

std::vector<Symbol *> Statement::splitUntilKeywords(std::vector<Symbol *> symbols, unsigned long long start, const std::vector<int> &keywords) {
    std::vector<Symbol *> fields;
    int parenthesis = 0;

    for (unsigned long long i = start; i < symbols.size(); i++) {
        if (symbols[i]->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisLeft) {
                parenthesis += 1;
                fields.push_back(symbols[i]);
                continue;
            }
            if (((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisRight) {
                parenthesis -= 1;
                if (parenthesis < 0) {
                    Error::syntaxError(")");
                }
                fields.push_back(symbols[i]);
                continue;
            }
        }

        if (parenthesis == 0 && symbols[i]->symbolValueType == s_Keyword) {
            if (keywords.empty()) {
                return fields;
            }
            for (int keyword: keywords) {
                if (((KeywordSymbol *) symbols[i])->keyword == keyword) {
                    return fields;
                }
            }
        }

        fields.push_back(symbols[i]);
    }

    return fields;
}

std::vector<Symbol *> Statement::splitUntilParenthesisOrKeyword(std::vector<Symbol *> symbols, unsigned long long start, const std::vector<int> &keywords) {
    std::vector<Symbol *> fields;

    for (unsigned long long i = start; i < symbols.size(); i++) {
        if (symbols[i]->symbolValueType == s_Delimiter && ((DelimiterSymbol *) symbols[i])->keyword == v_ParenthesisLeft) {
            break;
        }

        if (symbols[i]->symbolValueType == s_Keyword) {
            for (int keyword: keywords) {
                if (((KeywordSymbol *) symbols[i])->keyword == keyword) {
                    return fields;
                }
            }
        }

        fields.push_back(symbols[i]);
    }

    return fields;
}

std::vector<std::vector<Symbol *>> Statement::splitComa(const std::vector<Symbol *>& symbols) {
    std::vector<std::vector<Symbol *>> fields;
    std::vector<Symbol *> tmpArray;
    int parenthesis = 0;

    for (auto & symbol : symbols) {
        if (symbol->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol *) symbol)->keyword == v_Comma && parenthesis == 0) {
                fields.push_back(tmpArray);
                tmpArray = {};
                continue;
            }
            if (((DelimiterSymbol *) symbol)->keyword == v_ParenthesisLeft) {
                parenthesis += 1;
            } else if (((DelimiterSymbol *) symbol)->keyword == v_ParenthesisRight) {
                parenthesis -= 1;
                if (parenthesis < 0) {
                    Error::syntaxError("Expected ')'");
                }
            }
        }
        tmpArray.push_back(symbol);
    }
    fields.push_back(tmpArray);

    return fields;
}

std::vector<Symbol *> Statement::cut_symbol_vector(const std::vector<Symbol *> &symbols, unsigned long long start, unsigned long long end) {
    std::vector<Symbol *> newListSymbol;

    for (unsigned long long i = start; i < end; i++) {
        newListSymbol.push_back(symbols[i]);
    }

    return newListSymbol;
}
