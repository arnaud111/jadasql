//
// Created by nono on 19/12/2023.
//

#include "../../include/data/InsertableField.h"
#include "parser/tree/datatype/Char.h"
#include "parser/tree/datatype/Date.h"
#include "parser/tree/datatype/DateTime.h"
#include "parser/tree/datatype/Timestamp.h"
#include "parser/tree/datatype/VarChar.h"
#include "parser/tree/field/ConstNumberField.h"
#include "parser/tree/field/ConstStringField.h"

InsertableField::InsertableField(DataType *dataType, Field *value) {

    this->dataType = dataType;
    this->value = value;

}

const char *InsertableField::to_writable() {
    switch (this->dataType->type) {
        case d_Char:
        case d_Date:
        case d_DateTime:
        case d_Timestamp:
        case d_VarChar:
            return reinterpret_cast<const char*>(((ConstStringField *) this->value)->value.c_str());
        case d_Boolean:
        case d_Double:
        case d_Float:
        case d_Int:
        case d_TinyInt:
            return reinterpret_cast<const char*>(&((ConstNumberField *) this->value)->value);
    }
    return nullptr;
}

int InsertableField::size_of() {

    switch (this->dataType->type) {
        case d_Boolean:
            return sizeof(bool);
        case d_Char:
            return sizeof(char) * ((ConstStringField *) this->value)->value.size();
        case d_Date:
            return sizeof(char) * ((Date *) this->dataType)->size;
        case d_DateTime:
            return sizeof(char) * ((DateTime *) this->dataType)->size;
        case d_Double:
            return sizeof(double);
        case d_Float:
            return sizeof(float);
        case d_Int:
            return sizeof(int);
        case d_Timestamp:
            return sizeof(char) * ((Timestamp *) this->dataType)->size;
        case d_TinyInt:
            return sizeof(short);
        case d_VarChar:
            return sizeof(char) * ((ConstStringField *) this->value)->value.size();
    }
}

void InsertableField::display() const {
    printf("InsertableField ");
    this->dataType->display();
    this->value->display();
    printf(";\n");
}
