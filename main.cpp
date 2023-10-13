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

    printf("%zu\n", result.size());

    for (auto & i : result) {
        printf("a %d\n", i.value->symbolValueType);
    }
/*
    vector<Statement*> listStatement = Parser::parse(result);
    SelectStatement* selectStatement = (SelectStatement*) listStatement[0];
    SelectStatement* selectStatement2 = (SelectStatement*) listStatement[1];

    printf("%d\n", selectStatement->limit);
    printf("%d\n", selectStatement2->limit);
*/
    return 0;
}

// INSERT into test,(test AS t) FROM users.test IS not NULL "test\"'uwu" <= 3|*=1 test;
