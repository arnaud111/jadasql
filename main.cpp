#include <iostream>
#include "parser/Lexer.h"

int main() {

    string request;
    cout << "SQL -> ";
    getline (cin, request);
    Lexer lexicalScanner = Lexer();
    vector<Symbol> result = lexicalScanner.scan(request);

    for (auto & i : result) {
        printf("\"%s\", %u\n", i.value.c_str(), i.group);
    }

    return 0;
}

// INSERT INTO test,(test AS t) FROM users.test IS not NULL "test\"'uwu" <= 3|*=1 test;
