#include <iostream>
#include "parser/LexicalScanner.h"

int main() {

    string request;
    cout << "SQL -> ";
    getline (cin, request);
    LexicalScanner lexicalScanner = LexicalScanner();
    vector<Symbol> result = lexicalScanner.scan(request);

    for (auto & i : result) {
        printf("\"%s\", %u\n", i.value.c_str(), i.group);
    }

    return 0;
}

// INSERT INTO test,(test AS t) FROM users.test IS not NULL "test\"'uwu" <= 3|*=1 test;
