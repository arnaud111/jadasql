//
// Created by nono on 17/10/2023.
//

#ifndef JADA_ERROR_H
#define JADA_ERROR_H

#include <string>
#include "../lexer/symbol/Symbol.h"

class Error {

public:
    static void syntaxError(const std::string &error);

    static void syntaxError(const Symbol *symbolError);
};


#endif //JADA_ERROR_H
