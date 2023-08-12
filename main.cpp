#include "sql/statement/SqlStatement.h"
#include "sql/parser/SqlStatementParser.h"

int main() {

    SqlStatement* s = SqlStatementParser::statement_from_string("SELECT test AS yo, (SELECT 1) FROM users");
    s->compute();

    return 0;
}
