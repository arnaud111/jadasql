//
// Created by arnaud on 29/08/2023.
//

#ifndef JADA_LEXER_H
#define JADA_LEXER_H

#include <string>
#include <vector>
#include "symbol/Symbol.h"

using namespace std;

class Lexer {

private:
    int left;
    int right;
    vector<Symbol*> list_symbol;
    string actual_word;
    bool is_operator = false;
    char char_string_definition = 0;
    bool escaped = false;

public:
    vector<Symbol*> scan(const string& request);

private:
    static Symbol* convert_to_symbol(const string& val);
    bool compute_string(const string& request);
    void add_delimiter(const string& request);
    void add_operator(const string& request);
    static Symbol* try_convert_to_identifier(const string& val);
    static Symbol* try_convert_to_number(const string& val);
    static Symbol* try_convert_to_keywords(const string& val);
    static Symbol* try_convert_to_statement(const string& val);
    static Symbol* try_convert_to_datatype(const string& val);
    static Symbol* try_convert_to_operator(const string& val);
    static Symbol* try_convert_to_delimiter(char val);
    static int is_in_array(const string& val, string* array, int array_size);
    static string string_to_upper(const string& val);
};


#endif //JADA_LEXER_H
