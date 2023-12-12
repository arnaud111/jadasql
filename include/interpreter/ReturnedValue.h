//
// Created by nono on 11/12/23.
//

#ifndef JADA_RETURNEDVALUE_H
#define JADA_RETURNEDVALUE_H

enum ReturnedValueType {
    None,
    RowCount,
};

class ReturnedValue {

public:

    ReturnedValueType type;

    static ReturnedValue *none();

    static ReturnedValue *rowCount(int affected);
};

#endif //JADA_RETURNEDVALUE_H
