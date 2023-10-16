//
// Created by nono on 16/10/2023.
//

#include <stdexcept>
#include "Statement.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../lexer/symbol/keyword/KeywordSymbol.h"

std::vector<Symbol *> Statement::splitUntilKeywords(std::vector<Symbol *> symbols, int start, const std::vector<int>& keywords) {
    std::vector<Symbol *> fields;
    int parenthesis = 0;

    for (int i = start; i < symbols.size(); i++) {
        if (symbols[i]->symbolValueType == s_Delimiter) {
            if (((DelimiterSymbol*) symbols[i])->keyword == v_ParenthesisLeft) {
                parenthesis += 1;
                fields.push_back(symbols[i]);
                continue;
            } if (((DelimiterSymbol*) symbols[i])->keyword == v_ParenthesisRight) {
                parenthesis -= 1;
                if (parenthesis < 0) {
                    throw std::invalid_argument("Syntax Error");
                }
                fields.push_back(symbols[i]);
                continue;
            }
        }

        if (parenthesis == 0 && symbols[i]->symbolValueType == s_Keyword) {
            for (int keyword : keywords) {
                if (((KeywordSymbol *) symbols[i])->keyword == keyword) {
                    break;
                }
            }
        }

        fields.push_back(symbols[i]);
    }

    return fields;
}
