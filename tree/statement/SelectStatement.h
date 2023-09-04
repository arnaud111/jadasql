//
// Created by arnaud on 07/08/2023.
//

#ifndef JADA_SELECTSTATEMENT_H
#define JADA_SELECTSTATEMENT_H

#include <vector>
#include <iostream>
#include <string>
#include "../structure/Field.h"
#include "../from/FromClause.h"
#include "../where/WhereClause.h"
#include "../group/GroupClause.h"
#include "../parser/SqlStatementParser.h"
#include "../parser/SqlFieldListParser.h"

using namespace std;

class SelectStatement: public SqlStatement {
     vector<Field> fieldList;
     FromClause fromClause;
     WhereClause whereClause;
     GroupClause groupClause;

public:

    SelectStatement(vector<string> input_exploded) {
        this->fieldList = SqlFieldListParser::list_fields_from_string({input_exploded.begin() + 1, input_exploded.end()});

        std::cout << this->fieldList.size() << std::endl;
    }

    void compute() override {
        std::cout << "Compute" << std::endl;
    }
};

#endif //JADA_SELECTSTATEMENT_H
