//
// Created by arnaud on 29/08/2023.
//

#include <stdexcept>
#include "Lexer.h"
#include "symbol/keyword/DataTypeKeyword.h"
#include "symbol/keyword/OperatorKeyword.h"
#include "symbol/keyword/Keyword.h"
#include "symbol/StringSymbolValue.h"
#include "symbol/NumberSymbolValue.h"
#include "symbol/keyword/DelimiterKeyword.h"
#include "symbol/keyword/StatementKeyword.h"
#include "symbol/IdentifierSymbolValue.h"

vector<Symbol> Lexer::scan(const string &request) {

    for (right = 0, left = 0; right < request.size(); right++) {
        if (is_operator) {
            if (request[right] != '<' && request[right] != '>' && request[right] != '=' && request[right] != '+' && request[right] != '-' && request[right] != '*' && request[right] != '/' && request[right] != '%' && request[right] != '&' && request[right] != '|' && request[right] != '^') {
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
            } else if (request[right] == ' ' || request[right] == '\t' || request[right] == '\n' || request[right] == '(' || request[right] == ')' || request[right] == ',' || request[right] == ';' || request[right] == '.') {
                if (left != right) {
                    list_symbol.push_back(convert_to_symbol(request.substr(left, right - left)));
                }
                add_delimiter(request);
                left = right + 1;
            } else if ((request[right] == '<' || request[right] == '>' || request[right] == '=' || request[right] == '+' || request[right] == '-' || request[right] == '*' || request[right] == '/' || request[right] == '%' || request[right] == '&' || request[right] == '|' || request[right] == '^') && !is_operator) {
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

void Lexer::add_operator(const string& request) {

    actual_word = request.substr(left, right - left);

    SymbolValue * symbolValue = try_convert_to_operator(actual_word);

    if (symbolValue != nullptr) {
        symbol_tmp.value = symbolValue;
        symbol_tmp.group = g_Operator;
        list_symbol.push_back(symbol_tmp);
    } else {
        throw invalid_argument("Syntax Error");
    }

}

void Lexer::add_delimiter(const string& request) {

    SymbolValue * symbolValue = try_convert_to_delimiter(request[right]);

    if (symbolValue != nullptr) {
        symbol_tmp.value = symbolValue;
        symbol_tmp.group = g_Delimiter;
        list_symbol.push_back(symbol_tmp);
    }
}

bool Lexer::compute_string(const string& request) {
    if (escaped) {
        escaped = false;
        return false;
    }
    if (request[right] == char_string_definition) {
        if (left != right) {
            symbol_tmp.value = new StringSymbolValue(request.substr(left, right - left));
            symbol_tmp.group = g_String;
            list_symbol.push_back(symbol_tmp);
        }
        char_string_definition = 0;
        return true;
    } else if (request[right] == '\\') {
        escaped = true;
    }
    return false;
}

Symbol Lexer::convert_to_symbol(const string &val) {

    Symbol symbol = Symbol();

    symbol.value = try_convert_to_keywords(val);
    symbol.group = g_Keyword;
    if (symbol.value == nullptr) {
        symbol.value = try_convert_to_statement(val);
        symbol.group = g_StatementKeyword;
    } if (symbol.value == nullptr) {
        symbol.value = try_convert_to_operator(val);
        symbol.group = g_Operator;
    } if (symbol.value == nullptr) {
        symbol.value = try_convert_to_datatype(val);
        symbol.group = g_DataType;
    } if (symbol.value == nullptr) {
        symbol.value = try_convert_to_number(val);
        symbol.group = g_Number;
    } if (symbol.value == nullptr) {
        symbol.value = try_convert_to_identifier(val);
        symbol.group = g_Identifier;
    }

    if (symbol.value == nullptr) {
        throw invalid_argument("Syntax Error");
    }

    return symbol;
}

SymbolValue * Lexer::try_convert_to_identifier(const string& val) {

    IdentifierSymbolValue * symbolValue = nullptr;

    for (char c: val) {
        if ((c < 65 || c > 90) && (c < 97 || c > 122)) {
            return symbolValue;
        }
    }

    symbolValue = new IdentifierSymbolValue(val);

    return symbolValue;
}

SymbolValue * Lexer::try_convert_to_number(const string& val) {

    int number = 0;

    for (char c: val) {
        if (c < 48 || c > 57) {
            return nullptr;
        }
        number *= 10;
        number += c - 48;
    }

    return new NumberSymbolValue(number);
}

SymbolValue * Lexer::try_convert_to_statement(const string &val) {
    StatementKeyword* statementKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), StatementKeyword::stringValues, StatementKeyword::size);
    if (tmp != -1) {
        statementKeyword = new StatementKeyword(tmp);
    }

    return statementKeyword;
}

SymbolValue * Lexer::try_convert_to_keywords(const string &val) {
    Keyword* keyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), Keyword::stringValues, Keyword::size);
    if (tmp != -1) {
        keyword = new Keyword(tmp);
    }

    return keyword;
}

SymbolValue* Lexer::try_convert_to_datatype(const string &val) {
    DataTypeKeyword* dataTypeKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), DataTypeKeyword::stringValues, DataTypeKeyword::size);
    if (tmp != -1) {
        dataTypeKeyword = new DataTypeKeyword(tmp);
    }

    return dataTypeKeyword;
}

SymbolValue * Lexer::try_convert_to_operator(const string &val) {
    OperatorKeyword* operatorKeyword = nullptr;
    int tmp;

    tmp = is_in_array(string_to_upper(val), OperatorKeyword::stringValues, OperatorKeyword::size);
    if (tmp != -1) {
        operatorKeyword = new OperatorKeyword(tmp);
    }

    return operatorKeyword;
}

SymbolValue * Lexer::try_convert_to_delimiter(char val) {
    DelimiterKeyword* delimiterKeyword = nullptr;
    int tmp;
    string s;
    s.push_back(val);

    tmp = is_in_array(s, DelimiterKeyword::stringValues, DelimiterKeyword::size);
    if (tmp != -1) {
        delimiterKeyword = new DelimiterKeyword(tmp);
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
