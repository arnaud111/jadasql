//
// Created by arnaud on 29/08/2023.
//

#include "Lexer.h"
#include "symbol/keyword/DataTypeSymbol.h"
#include "symbol/keyword/OperatorSymbol.h"
#include "symbol/keyword/KeywordSymbol.h"
#include "symbol/value/StringSymbol.h"
#include "symbol/value/NumberSymbol.h"
#include "symbol/keyword/DelimiterSymbol.h"
#include "symbol/keyword/StatementSymbol.h"
#include "symbol/value/IdentifierSymbol.h"
#include "../error/Error.h"

vector<Symbol *> Lexer::scan(const string &request) {

    for (right = 0, left = 0; right < request.size(); right++) {
        if (is_operator) {
            if (request[right] != '<' && request[right] != '>' && request[right] != '=' && request[right] != '+' &&
                request[right] != '-' && request[right] != '*' && request[right] != '/' && request[right] != '%' &&
                request[right] != '&' && request[right] != '|' && request[right] != '^') {
                add_operator(request);
                is_operator = false;
                left = right;
            }
        }
        if (char_string_definition) {
            if (compute_string(request))
                left = right + 1;
        } else {
            if (request[right] == '"' || request[right] == '\'') {
                char_string_definition = request[right];
                if (left != right) {
                    list_symbol.push_back(convert_to_symbol(request.substr(left, right - left)));
                }
                left = right + 1;
            } else if (request[right] == ' ' || request[right] == '\t' || request[right] == '\n' ||
                       request[right] == '(' || request[right] == ')' || request[right] == ',' ||
                       request[right] == ';' || request[right] == '.' || request[right] == '@') {
                if (left != right) {
                    list_symbol.push_back(convert_to_symbol(request.substr(left, right - left)));
                }
                add_delimiter(request);
                left = right + 1;
            } else if (
                    (request[right] == '<' || request[right] == '>' || request[right] == '=' || request[right] == '+' ||
                     request[right] == '-' || request[right] == '*' || request[right] == '/' || request[right] == '%' ||
                     request[right] == '&' || request[right] == '|' || request[right] == '^') && !is_operator) {
                if (left != right) {
                    list_symbol.push_back(convert_to_symbol(request.substr(left, right - left)));
                }
                is_operator = true;
                left = right;
            }
        }
    }

    if (left < right) {
        list_symbol.push_back(convert_to_symbol(request.substr(left, right - left)));
    }

    return list_symbol;
}

void Lexer::add_operator(const string &request) {

    actual_word = request.substr(left, right - left);

    Symbol *symbolValue = try_convert_to_operator(actual_word);

    if (symbolValue != nullptr) {
        list_symbol.push_back(symbolValue);
    } else {
        Error::syntaxError(actual_word);
    }
}

void Lexer::add_delimiter(const string &request) {

    Symbol *symbolValue = try_convert_to_delimiter(request[right]);

    if (symbolValue != nullptr) {
        list_symbol.push_back(symbolValue);
    }
}

bool Lexer::compute_string(const string &request) {
    if (escaped) {
        escaped = false;
        return false;
    }
    if (request[right] == char_string_definition) {
        if (left != right) {
            list_symbol.push_back(new StringSymbol(request.substr(left, right - left)));
        }
        char_string_definition = 0;
        return true;
    } else if (request[right] == '\\') {
        escaped = true;
    }
    return false;
}

Symbol *Lexer::convert_to_symbol(const string &val) {

    Symbol *symbol;

    symbol = try_convert_to_keywords(val);
    if (symbol == nullptr) {
        symbol = try_convert_to_statement(val);
    }
    if (symbol == nullptr) {
        symbol = try_convert_to_operator(val);
    }
    if (symbol == nullptr) {
        symbol = try_convert_to_datatype(val);
    }
    if (symbol == nullptr) {
        symbol = try_convert_to_number(val);
    }
    if (symbol == nullptr) {
        symbol = try_convert_to_identifier(val);
    }

    if (symbol == nullptr) {
        Error::syntaxError(val);
    }

    return symbol;
}

Symbol *Lexer::try_convert_to_identifier(const string &val) {

    IdentifierSymbol *symbolValue = nullptr;

    if ((val[0] < 65 || val[0] > 90) && (val[0] < 97 || val[0] > 122) && val[0] != '_') {
        return symbolValue;
    }

    for (int i = 1; i < val.size(); i++) {
        if ((val[i] < 65 || val[i] > 90) && (val[i] < 97 || val[i] > 122) && (val[i] < 48 || val[i] > 57) &&
            val[i] != '_') {
            return symbolValue;
        }
    }

    symbolValue = new IdentifierSymbol(val);

    return symbolValue;
}

Symbol *Lexer::try_convert_to_number(const string &val) {

    int number = 0;

    for (char c: val) {
        if (c < 48 || c > 57) {
            return nullptr;
        }
        number *= 10;
        number += c - 48;
    }

    return new NumberSymbol(number);
}

Symbol *Lexer::try_convert_to_statement(const string &val) {
    StatementSymbol *statementKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), StatementSymbol::stringValues, StatementSymbol::size);
    if (tmp != -1) {
        statementKeyword = new StatementSymbol(tmp);
    }

    return statementKeyword;
}

Symbol *Lexer::try_convert_to_keywords(const string &val) {
    KeywordSymbol *keyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), KeywordSymbol::stringValues, KeywordSymbol::size);
    if (tmp != -1) {
        keyword = new KeywordSymbol(tmp);
    }

    return keyword;
}

Symbol *Lexer::try_convert_to_datatype(const string &val) {
    DataTypeSymbol *dataTypeKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), DataTypeSymbol::stringValues, DataTypeSymbol::size);
    if (tmp != -1) {
        dataTypeKeyword = new DataTypeSymbol(tmp);
    }

    return dataTypeKeyword;
}

Symbol *Lexer::try_convert_to_operator(const string &val) {
    OperatorSymbol *operatorKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), OperatorSymbol::stringValues, OperatorSymbol::size);
    if (tmp != -1) {
        operatorKeyword = new OperatorSymbol(tmp);
    }

    return operatorKeyword;
}

Symbol *Lexer::try_convert_to_delimiter(char val) {
    DelimiterSymbol *delimiterKeyword = nullptr;
    int tmp;
    string s;
    s.push_back(val);

    tmp = is_in_array(s, DelimiterSymbol::stringValues, DelimiterSymbol::size);
    if (tmp != -1) {
        delimiterKeyword = new DelimiterSymbol(tmp);
    }

    return delimiterKeyword;
}

int Lexer::is_in_array(const string &val, string *array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (array[i] == val) {
            return i;
        }
    }
    return -1;
}

string Lexer::string_to_upper(const string &val) {

    string upper;

    for (char c: val) {
        upper.push_back(toupper(c));
    }

    return upper;
}
