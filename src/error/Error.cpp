//
// Created by nono on 17/10/2023.
//

#include <stdexcept>
#include "../../include/error/Error.h"
#include "../../include/lexer/symbol/value/IdentifierSymbol.h"
#include "../../include/lexer/symbol/value/StringSymbol.h"
#include "../../include/lexer/symbol/value/NumberSymbol.h"
#include "../../include/lexer/symbol/keyword/StatementSymbol.h"
#include "../../include/lexer/symbol/keyword/OperatorSymbol.h"
#include "../../include/lexer/symbol/keyword/KeywordSymbol.h"
#include "../../include/lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../include/lexer/symbol/keyword/DataTypeSymbol.h"

void Error::syntaxError(const std::string &error) {
    std::string fullError = "Syntax Error: ";
    fullError.append(error);
    throw std::invalid_argument(fullError);
}

void Error::syntaxError(const Symbol *symbolError) {
    std::string fullError = "Syntax Error at: ";
    int tmp;
    char tmp_c;
    std::string s;

    switch (symbolError->symbolValueType) {
        case s_DataType:
            fullError.append(DataTypeSymbol::stringValues[((DataTypeSymbol *) symbolError)->keyword]);
            break;
        case s_Delimiter:
            fullError.append(DelimiterSymbol::stringValues[((DelimiterSymbol *) symbolError)->keyword]);
            break;
        case s_Keyword:
            fullError.append(KeywordSymbol::stringValues[((KeywordSymbol *) symbolError)->keyword]);
            break;
        case s_Operator:
            fullError.append(OperatorSymbol::stringValues[((OperatorSymbol *) symbolError)->keyword]);
            break;
        case s_Statement:
            fullError.append(StatementSymbol::stringValues[((StatementSymbol *) symbolError)->keyword]);
            break;
        case s_Number:
            fullError = "Syntax Error: " + std::to_string(((NumberSymbol *) symbolError)->value);
            break;
        case s_String:
            fullError.append(((StringSymbol *) symbolError)->value);
            break;
        case s_Identifier:
            fullError.append(((IdentifierSymbol *) symbolError)->value);
            break;
        case s_None:
            fullError.append("None");
            break;
    }
    
    throw std::invalid_argument(fullError);
}
