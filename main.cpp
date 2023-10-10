#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "parser/tree/statements/SelectStatement.h"

int main() {

    string request;
    cout << "SQL -> ";
    getline (cin, request);
    Lexer lexicalScanner = Lexer();
    vector<Symbol> result = lexicalScanner.scan(request);

    for (auto & i : result) {
        printf("\"%s\", %u\n", i.value.c_str(), i.group);
    }

    vector<Statement*> listStatement = Parser::parse(result);
    SelectStatement* selectStatement = (SelectStatement*) listStatement[0];
    SelectStatement* selectStatement2 = (SelectStatement*) listStatement[1];

    printf("%d\n", selectStatement->limit);
    printf("%d\n", selectStatement2->limit);

    return 0;
}

// INSERT INTO test,(test AS t) FROM users.test IS not NULL "test\"'uwu" <= 3|*=1 test;
