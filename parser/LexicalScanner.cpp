//
// Created by arnaud on 29/08/2023.
//

#include <stdexcept>
#include "LexicalScanner.h"

int LexicalScanner::operators_size = 24;
string LexicalScanner::operators[24] = {
        ">",
        "<",
        ">=",
        "<=",
        "==",
        "!=",
        "<>",
        "=",
        "+",
        "-",
        "/",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "&=",
        "^-=",
        "|*=",
        "*",
        "&",
        "|",
        "^",
        "%"
};

int LexicalScanner::keywords_size = 28;
string LexicalScanner::keywords[28] = {
        "SELECT",
        "FROM",
        "WHERE",
        "AS",
        "AND",
        "OR",
        "NOT",
        "NULL",
        "UPDATE",
        "SET",
        "DELETE",
        "LIMIT",
        "LIKE",
        "IN",
        "BETWEEN",
        "JOIN",
        "ON",
        "UNION",
        "HAVING",
        "EXISTS",
        "ANY",
        "ALL",
        "CASE",
        "WHEN",
        "THEN",
        "ELSE",
        "END",
        "SOME"
};

int LexicalScanner::multi_keywords_size = 22;
string LexicalScanner::multi_keywords[22] = {
        "INSERT INTO",
        "CREATE DATABASE",
        "DROP DATABASE",
        "DROP TABLE",
        "ALTER TABLE",
        "NOT NULL",
        "UNIQUE",
        "PRIMARY KEY",
        "FOREIGN KEY",
        "CHECK",
        "DEFAULT",
        "CREATE INDEX",
        "CREATE TABLE",
        "IS NULL",
        "IS NOT NULL",
        "ORDER BY",
        "INNER JOIN",
        "LEFT JOIN",
        "RIGHT JOIN",
        "CROSS JOIN",
        "UNION ALL",
        "GROUP BY",
};

int LexicalScanner::functions_size = 9;
string LexicalScanner::functions[9] = {
        "MAX",
        "SUM",
        "COUNT",
        "CONCAT",
        "FORMAT",
        "MIN",
        "AVG",
        "IFNULL",
        "COALESCE",
};

int LexicalScanner::data_types_size = 10;
string LexicalScanner::data_types[10] = {
        "CHAR",
        "VARCHAR",
        "TINYINT",
        "BOOLEAN",
        "INT",
        "FLOAT",
        "DOUBLE",
        "DATE",
        "DATETIME",
        "TIMESTAMP"
};

vector<Symbol> LexicalScanner::scan(const string &request) {

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
                compute_word(request);
                left = right + 1;
            } else if (request[right] == ' ' || request[right] == '\t' || request[right] == '\n' || request[right] == '(' || request[right] == ')' || request[right] == ',' || request[right] == ';' || request[right] == '.') {
                compute_word(request);
                add_delimiter(request);
                left = right + 1;
            } else if ((request[right] == '<' || request[right] == '>' || request[right] == '=' || request[right] == '+' || request[right] == '-' || request[right] == '*' || request[right] == '/' || request[right] == '%' || request[right] == '&' || request[right] == '|' || request[right] == '^') && !is_operator) {
                compute_word(request);
                is_operator = true;
            }
        }
    }

    if (left < right) {
        compute_word(request);
    }

    return list_symbol;
}

void LexicalScanner::add_operator(const string& request) {

    actual_word = request.substr(left, right - left);

    if (is_in_operators(actual_word)) {
        symbol_tmp.value = actual_word;
        symbol_tmp.group = Operator;
        list_symbol.push_back(symbol_tmp);
    } else {
        throw invalid_argument("Syntax Error");
    }

}

void LexicalScanner::add_delimiter(const string& request) {
    if (request[right] == '(' || request[right] == ')' || request[right] == ',' || request[right] == ';' || request[right] == '.') {
        symbol_tmp.value = request[right];
        symbol_tmp.group = Delimiter;
        list_symbol.push_back(symbol_tmp);
    }
}

bool LexicalScanner::compute_string(const string& request) {
    if (escaped) {
        escaped = false;
        return false;
    }
    if (request[right] == char_string_definition) {
        if (left != right) {
            symbol_tmp.value = request.substr(left, right - left);
            symbol_tmp.group = String;
            list_symbol.push_back(symbol_tmp);
        }
        char_string_definition = 0;
        return true;
    } else if (request[right] == '\\') {
        escaped = true;
    }
    return false;
}

void LexicalScanner::compute_word(const string& request) {
    if (left != right) {
        add_word(request.substr(left, right - left));
    }
    left = right;
}

void LexicalScanner::add_word(const string& word) {

    string word_added;

    if (is_multi_keywords) {
        word_added = string_to_upper(word);
        is_multi_keywords = check_next_multi_keyword(word_added);
    } else {
        actual_word = word;
        if (is_in_multi_keywords(actual_word)) {
            actual_word = string_to_upper(actual_word);
            is_multi_keywords = true;
        } else {
            list_symbol.push_back(convert_to_symbol(actual_word));
        }
    }
}

bool LexicalScanner::check_next_multi_keyword(string &word_added) {

    actual_word.append(" ");
    actual_word.append(word_added);
    switch (is_in_multi_keywords(actual_word)) {
        case 2:
            symbol_tmp.value = actual_word;
            symbol_tmp.group = MultiKeyword;
            list_symbol.push_back(symbol_tmp);
            return false;
        case 0:
            throw invalid_argument("Syntax Error");
    }

    return true;
}

Symbol LexicalScanner::convert_to_symbol(const string &val) {

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
    } else if (is_in_functions(val)) {
        symbol.value = string_to_upper(val);
        symbol.group = Function;
    } else if (is_number(val)) {
        symbol.value = val;
        symbol.group = Number;
    } else if (is_full_text(val)) {
        symbol.value = val;
        symbol.group = Identifier;
    } else {
        throw invalid_argument("Syntax Error");
    }

    return symbol;
}

bool LexicalScanner::is_full_text(const string& val) {

    for (char c: val) {
        if ((c < 65 || c > 90) && (c < 97 || c > 122)) {
            return false;
        }
    }

    return true;
}

bool LexicalScanner::is_number(const string& val) {

    for (char c: val) {
        if (c < 48 || c > 57) {
            return false;
        }
    }

    return true;
}

int LexicalScanner::is_in_multi_keywords(string val) {

    bool part;

    for (int i = 0; i < multi_keywords_size; i++) {
        part = true;
        for (int j = 0; j < val.size(); j++) {
            if (j >= multi_keywords[i].size() || multi_keywords[i][j] != val[j]) {
                part = false;
            }
        }
        if (part) {
            if (val.size() == multi_keywords[i].size()) {
                return 2;
            }
            return 1;
        }
    }

    return 0;
}

bool LexicalScanner::is_in_keywords(const string &val) {
    return is_in_array(string_to_upper(val), keywords, keywords_size);
}

bool LexicalScanner::is_in_functions(const string &val) {
    return is_in_array(string_to_upper(val), functions, functions_size);
}

bool LexicalScanner::is_in_data_types(const string &val) {
    return is_in_array(string_to_upper(val), data_types, data_types_size);
}

bool LexicalScanner::is_in_operators(const string &val) {
    return is_in_array(val, operators, operators_size);
}

bool LexicalScanner::is_in_array(const string &val, string *array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (array[i] == val) {
            return true;
        }
    }
    return false;
}

string LexicalScanner::string_to_upper(const string &val) {

    string upper;

    for (char c: val) {
        upper.push_back(toupper(c));
    }

    return upper;
}
