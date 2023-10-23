#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"

int main() {

    string request;
    cout << "SQL -> ";
    getline(cin, request);
    printf("---LEXER---\n");
    Lexer lexicalScanner = Lexer();
    vector<Symbol *> result = lexicalScanner.scan(request);

    for (auto &i: result) {
        i->display();
    }

    printf("---PARSER---\n");

    vector<Statement *> listStatement = Parser::parse(result);

    printf("size : %zu\n", listStatement.size());

    for (auto &i: listStatement) {
        i->display();
    }

    return 0;
}

// SELECT DISTINCT T.col, _Uwu1, "UwU\"'", 3, MAX(CONCAT("test", c.coucou)), (SELECT 1) FROM test@t_test T GROUP BY test1 ORDER BY test2 LIMIT 1
