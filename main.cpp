#include "include/lexer/Lexer.h"
#include "include/parser/Parser.h"

int main() {

    string request = "SELECT DISTINCT T.col, _Uwu1, \"UwU\\\"'\", 3, MAX(CONCAT(\"test\", c.coucou)) FROM test@t_test T LEFT JOIN ta ON ta.id = T.id INNER JOIN tt ON 1 + 1 = 2 % 1 WHERE 1 > (1 % 1) GROUP BY test1, 1 ORDER BY test2, 1 DESC LIMIT 1;"
                     "DROP TABLE IF EXISTS test;"
                     "DELETE FROM test WHERE 1 = 1 AND 1 > 2 + 3 * 5;"
                     "UPDATE test SET a = 1 WHERE aaa < BBBB;"
                     "INSERT INTO test (a, b, c) VALUES (\"val\"), (2);"
                     "CREATE DATABASE IF NOT EXISTS db;"
                     "CREATE TABLE tt("
                     "    PersonID int AUTO_INCREMENT,\n"
                     "    LastName varchar(255) DEFAULT NULL,\n"
                     "    FirstName varchar(255) DEFAULT 'test',\n"
                     "    Address varchar(255) NOT NULL,\n"
                     "    City varchar(255) NOT NULL DEFAULT 'test' AUTO_INCREMENT,"
                     "CHECK(PersonID > 2),"
                     "UNIQUE(LastName, FirstName),"
                     "PRIMARY KEY (PersonID, LastName, FirstName),"
                     "FOREIGN KEY (PersonID, LastName, FirstName) REFERENCES tt@aa(id, tmp, name)"
                     ");"
                     "ALTER TABLE tmp ADD aaa VARCHAR(256),"
                     "CHANGE aaa bbb,"
                     "MODIFY bbb INT,"
                     "DROP bbb;";
    printf("---LEXER---\n");
    Lexer lexicalScanner = Lexer();
    vector<Symbol *> result = lexicalScanner.scan(request);

    /*for (auto &i: result) {
        i->display();
    }*/

    printf("---PARSER---\n");

    vector<Statement *> listStatement = Parser::parse(result);

    printf("size : %zu\n", listStatement.size());

    for (auto &i: result) {
        delete i;
    }

    for (auto &i: listStatement) {
        i->display();
        delete i;
    }

    return 0;
}
