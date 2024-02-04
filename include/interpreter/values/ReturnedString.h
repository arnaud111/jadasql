//
// Created by nono on 04/02/24.
//

#ifndef JADA_RETURNEDSTRING_H
#define JADA_RETURNEDSTRING_H

#include "../ReturnedValue.h"

class ReturnedString: public ReturnedValue {

public:

    std::string value;

    explicit ReturnedString(std::string value);

    void display() override;
};

#endif //JADA_RETURNEDSTRING_H
