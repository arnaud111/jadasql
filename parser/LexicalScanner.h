//
// Created by a833444 on 29/08/2023.
//

#ifndef JADA_LEXICALSCANNER_H
#define JADA_LEXICALSCANNER_H

#include <string>
#include <vector>
#include "Symbol.h"

using namespace std;

class LexicalScanner {

public:
    vector<Symbol> scan(string request);

private:
    Symbol convert_to_symbol(string val);
    bool is_in_keywords(string val);
    bool is_in_double_keywords(string val);
    bool is_in_functions(string val);
    bool is_in_data_types(string val);
    bool is_in_operators(string val);
    static bool is_in_array(string val, string* array, int array_size);
    static string string_to_upper(string val);

private:
    int keywords_size = 3;
    string keywords[3] = {
            "SELECT",
            "FROM",
            "WHERE"
    };

    int double_keywords_size = 2;
    string double_keywords[2] = {
            "INSERT INTO",
            "CREATE TABLE"
    };

    int functions_size = 2;
    string functions[2] = {
            "MAX",
            "SUM"
    };

    int data_types_size = 10;
    string data_types[10] = {
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

    int operators_size = 6;
    string operators[6] = {
            ">",
            "<",
            ">=",
            "<=",
            "==",
            "!="
    };
};


#endif //JADA_LEXICALSCANNER_H
