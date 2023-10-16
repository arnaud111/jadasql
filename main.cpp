#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "parser/tree/statements/SelectStatement.h"

int main() {

    string request;
    cout << "SQL -> ";
    getline (cin, request);
    Lexer lexicalScanner = Lexer();
    vector<Symbol*> result = lexicalScanner.scan(request);

    for (auto & i : result) {
        i->display();
    }

    vector<Statement*> listStatement = Parser::parse(result);

    printf("size : %zu\n", listStatement.size());

    return 0;
}

// INSERT into test,(test AS t) FROM users.test IS not NULL "test\"'uwu" <= 3|*=1 test;
// Select 1; Select 2
// SELECT * FROM test GROUP BY test1 ORDER BY test2 LIMIT 1
