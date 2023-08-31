//
// Created by a833444 on 29/08/2023.
//

#include "LexicalScanner.h"

vector<Symbol> LexicalScanner::scan(string request) {

    int left = 0;
    int right = 0;
    vector<Symbol> list_symbol;
    Symbol symbol_tmp;
    string word_tmp;

    for (char c : request) {
        if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) {
            right++;
        } else {
            if (c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')' || c == ',' || c == ';') {
                if (left != right) {
                    word_tmp = request.substr(left, right - left);
                    list_symbol.push_back(convert_to_symbol(word_tmp));
                }
                if (c == '(' || c == ')' || c == ',' || c == ';') {
                    symbol_tmp.value = c;
                    symbol_tmp.group = Delimiter;
                    list_symbol.push_back(symbol_tmp);
                }
                right++;
                left = right;
            } else {
                throw "Syntax Error";
            }
        }
    }

    return list_symbol;
}

Symbol LexicalScanner::convert_to_symbol(string val) {

    Symbol symbol;

    if (is_in_keywords(val)) {
        symbol.value = string_to_upper(val);
        symbol.group = Keyword;
    } else if (is_in_operators(val)) {
        symbol.value = val;
        symbol.group = Operator;
    } else if (is_in_data_types(val)) {
        symbol.value = string_to_upper(val);
        symbol.group = DataType;
    } else if (is_in_double_keywords(val)) {
        symbol.value = string_to_upper(val);
        symbol.group = DoubleKeyword;
    } else if (is_in_functions(val)) {
        symbol.value = string_to_upper(val);
        symbol.group = Function;
    } else {
        symbol.value = val;
        symbol.group = Identifier;
    }

    return symbol;
}

bool LexicalScanner::is_in_keywords(string val) {
    return is_in_array(string_to_upper(val), keywords, keywords_size);
}

bool LexicalScanner::is_in_double_keywords(string val) {
    return is_in_array(string_to_upper(val), double_keywords, double_keywords_size);
}

bool LexicalScanner::is_in_functions(string val) {
    return is_in_array(string_to_upper(val), functions, functions_size);
}

bool LexicalScanner::is_in_data_types(string val) {
    return is_in_array(string_to_upper(val), data_types, data_types_size);
}

bool LexicalScanner::is_in_operators(string val) {
    return is_in_array(val, operators, operators_size);
}

bool LexicalScanner::is_in_array(string val, string *array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (array[i] == val) {
            return true;
        }
    }
    return false;
}

string LexicalScanner::string_to_upper(string val) {

    string upper;

    for (char c : val) {
        upper.push_back(toupper(c));
    }

    return upper;
}