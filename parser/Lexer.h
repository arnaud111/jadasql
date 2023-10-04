//
// Created by arnaud on 29/08/2023.
//

#ifndef JADA_LEXER_H
#define JADA_LEXER_H

#include <string>
#include <vector>
#include "Symbol.h"

using namespace std;

class Lexer {

public:
    vector<Symbol> scan(const string& request);

private:
    static Symbol convert_to_symbol(const string& val);
    void add_word(const string& word);
    bool check_next_multi_keyword(string& word_added);
    void compute_word(const string& request);
    bool compute_string(const string& request);
    void add_delimiter(const string& request);
    void add_operator(const string& request);
    static bool is_full_text(const string& val);
    static bool is_number(const string& val);
    static bool is_in_keywords(const string& val);
    static int is_in_multi_keywords(string val);
    static bool is_in_functions(const string& val);
    static bool is_in_data_types(const string& val);
    static bool is_in_operators(const string& val);
    static bool is_in_array(const string& val, string* array, int array_size);
    static string string_to_upper(const string& val);

private:
    int left;
    int right;
    vector<Symbol> list_symbol;
    Symbol symbol_tmp;
    string actual_word;
    bool is_multi_keywords = false;
    bool is_operator = false;
    char char_string_definition = 0;
    bool escaped = false;

    static int keywords_size;
    static string keywords[28];

    static int multi_keywords_size;
    static string multi_keywords[22];

    static int functions_size;
    static string functions[9];

    static int data_types_size;
    static string data_types[10];

    static int operators_size;
    static string operators[24];
};


#endif //JADA_LEXER_H
