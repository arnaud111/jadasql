//
// Created by arnaud on 07/08/2023.
//

#ifndef JADA_EXPRESSION_H
#define JADA_EXPRESSION_H

#include <optional>
#include "CompareEnum.h"

using namespace std;

class Expression {
    Expression *expression1;
    CompareEnum compare;
    Expression *expression2;
};

#endif //JADA_EXPRESSION_H
