//
// Created by a833444 on 07/08/2023.
//

#ifndef JADA_SQLSTATEMENTPARSER_H
#define JADA_SQLSTATEMENTPARSER_H


#include "../statement/SqlStatement.h"
#include "../statement/SelectStatement.h"
#include "StringParser.h"

class SqlStatementParser {

public:

    static SqlStatement* statement_from_string(string input) {

        vector<string> exploded = StringParser::explode("SELECT test AS yo, (SELECT 1) FROM users", ' ');
        if (exploded.empty()) return nullptr;

        if (exploded[0] == "SELECT") {
            return new SelectStatement(exploded);
        }

        return nullptr;
    }
};


#endif //JADA_SQLSTATEMENTPARSER_H
