#include "parser/LexicalScanner.h"

int main() {

    LexicalScanner lexicalScanner;
    vector<Symbol> result = lexicalScanner.scan("SELECT test FROM users;");

    for (auto & i : result) {
        printf("\"%s\", %u\n", i.value.c_str(), i.group);
    }

    return 0;
}
