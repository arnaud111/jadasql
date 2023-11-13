//
// Created by nono on 23/10/2023.
//

#ifndef JADA_OPERATIONPRIORITY_H
#define JADA_OPERATIONPRIORITY_H

enum OperationPriorityEnum {
    o_Or,
    o_And,
    o_Not,
    o_In,
    o_Between,
    o_Like,
    o_Some,
    o_Exists,
    o_Greater,
    o_GreaterEqual,
    o_Lower,
    o_LowerEqual,
    o_NotEqual,
    o_Equal,
    o_BitAnd,
    o_BitOr,
    o_BitXor,
    o_Add,
    o_Sub,
    o_Mul,
    o_Div,
    o_Mod,
};

class OperationPriority {

public:

};

#endif //JADA_OPERATIONPRIORITY_H
