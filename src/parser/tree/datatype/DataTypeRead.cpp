//
// Created by nono on 03/02/24.
//

#include <fstream>
#include "parser/tree/datatype/Boolean.h"
#include "parser/tree/datatype/Char.h"
#include "parser/tree/datatype/Date.h"
#include "parser/tree/datatype/DateTime.h"
#include "parser/tree/datatype/Double.h"
#include "parser/tree/datatype/Float.h"
#include "parser/tree/datatype/Int.h"
#include "parser/tree/datatype/Timestamp.h"
#include "parser/tree/datatype/TinyInt.h"
#include "parser/tree/datatype/VarChar.h"
#include "parser/tree/field/ConstNumberField.h"
#include "parser/tree/field/ConstStringField.h"

Field *Boolean::readFromFile(std::ifstream *file) {
    char value;

    file->read(&value, 1);

    if (value) {
        return new ConstNumberField(1);
    }
    return new ConstNumberField(0);
}

Field *Char::readFromFile(std::ifstream *file) {
    std::string value;
    char tmp;

    for (int i = 0; i < this->size; i++) {
        file->read(&tmp, 1);
        value.push_back(tmp);
    }

    return new ConstStringField(value);
}

Field *Date::readFromFile(std::ifstream *file) {
    return nullptr;
}

Field *DateTime::readFromFile(std::ifstream *file) {
    return nullptr;
}

Field *Double::readFromFile(std::ifstream *file) {
    return nullptr;
}

Field *Float::readFromFile(std::ifstream *file) {
    return nullptr;
}

Field *Int::readFromFile(std::ifstream *file) {
    int value;

    file->read(reinterpret_cast<char*>(&value), this->size);

    return new ConstNumberField(value);
}

Field *Timestamp::readFromFile(std::ifstream *file) {
    return nullptr;
}

Field *TinyInt::readFromFile(std::ifstream *file) {
    int value;

    file->read(reinterpret_cast<char*>(&value), this->size);

    return new ConstNumberField(value);
}

Field *VarChar::readFromFile(std::ifstream *file) {
    std::string value;
    char tmp;

    for (int i = 0; i < this->size; i++) {
        file->read(&tmp, 1);
        if (tmp == 0) {
            break;
        }
        value.push_back(tmp);
    }

    return new ConstStringField(value);
}
