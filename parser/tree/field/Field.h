//
// Created by nono on 16/10/2023.
//

#ifndef JADA_FIELD_H
#define JADA_FIELD_H

#include <vector>
#include "../../../lexer/symbol/Symbol.h"
#include "../tree_item/TreeItem.h"
#include "../operation/OperationPriority.h"

enum FieldType {
    f_Column,
    f_Statement,
    f_Function,
    f_ConstString,
    f_ConstNumber,
    f_Reference,
    f_Operation,
};

class Field : public TreeItem {

public:

    FieldType fieldType;

    static std::vector<Field *> createListField(const std::vector<Symbol *> &symbols);

    static int tryConvertToOperatorEnum(Symbol *symbol);

    static Field *convertToField(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToColumnReference(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToConst(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToFunction(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToStatement(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToOperation(const std::vector<Symbol *> &symbols);

    static Field *tryConvertToFunctionField(const std::vector<Symbol *> &symbols, int function);
};

#endif //JADA_FIELD_H
