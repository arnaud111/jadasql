//
// Created by nono on 14/11/2023.
//

#include "../../../include/parser/tree/datatype/DataType.h"
#include "../../../include/parser/tree/datatype/Boolean.h"
#include "../../../include/parser/tree/datatype/Char.h"
#include "../../../include/parser/tree/datatype/Date.h"
#include "../../../include/parser/tree/datatype/DateTime.h"
#include "../../../include/parser/tree/datatype/Double.h"
#include "../../../include/parser/tree/datatype/Float.h"
#include "../../../include/parser/tree/datatype/Int.h"
#include "../../../include/parser/tree/datatype/Timestamp.h"
#include "../../../include/parser/tree/datatype/TinyInt.h"
#include "../../../include/parser/tree/datatype/VarChar.h"
#include "../../../include/lexer/symbol/keyword/DataTypeSymbol.h"
#include "../../../include/lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../include/error/Error.h"
#include "../../../include/lexer/symbol/value/NumberSymbol.h"

Boolean::Boolean() : DataType() {
    this->type = d_Boolean;
}

Char::Char(std::vector<Symbol *> symbol): DataType() {
    this->type = d_Char;

    if (symbol[1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbol[1])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbol[1]);
    }

    if (symbol[3]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbol[3])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbol[3]);
    }

    if (symbol[2]->symbolValueType != s_Number) {
        Error::syntaxError(symbol[2]);
    }

    this->size = ((NumberSymbol *) symbol[2])->value;
}

Date::Date(): DataType() {
    this->type = d_Date;
}

DateTime::DateTime(): DataType() {
    this->type = d_DateTime;
}

Double::Double(): DataType() {
    this->type = d_Double;
}

Float::Float(): DataType() {
    this->type = d_Float;
}

Int::Int(): DataType() {
    this->type = d_Int;
}

Timestamp::Timestamp(): DataType() {
    this->type = d_Timestamp;
}

TinyInt::TinyInt(): DataType() {
    this->type = d_TinyInt;
}

VarChar::VarChar(std::vector<Symbol *> symbol): DataType() {
    this->type = d_VarChar;

    if (symbol[1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbol[1])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbol[1]);
    }

    if (symbol[3]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbol[3])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbol[3]);
    }

    if (symbol[2]->symbolValueType != s_Number) {
        Error::syntaxError(symbol[2]);
    }

    this->size = ((NumberSymbol *) symbol[2])->value;
}

DataType *DataType::convertToDataType(std::vector<Symbol *> symbols) {

    if (symbols.size() == 1 && symbols[0]->symbolValueType == s_DataType) {
        switch (((DataTypeSymbol *) symbols[0])->keyword) {
            case v_Varchar:
            case v_Char:
                break;
            case v_Tinyint:
                return new TinyInt();
            case v_Boolean:
                return new Boolean();
            case v_Int:
                return new Int();
            case v_Float:
                return new Float();
            case v_Double:
                return new Double();
            case v_Date:
                return new Date();
            case v_Datetime:
                return new DateTime();
            case v_Timestamp:
                return new Timestamp();
        }
    } else if (symbols.size() == 4 && symbols[0]->symbolValueType == s_DataType) {
        if (((DataTypeSymbol *) symbols[0])->keyword == v_Varchar) {
            return new VarChar(symbols);
        } else if (((DataTypeSymbol *) symbols[0])->keyword == v_Char) {
            return new Char(symbols);
        }
    }

    return nullptr;
}

ReturnedValue *Boolean::execute() {
    return nullptr;
}

ReturnedValue *Char::execute() {
    return nullptr;
}

ReturnedValue *Date::execute() {
    return nullptr;
}

ReturnedValue *DateTime::execute() {
    return nullptr;
}

ReturnedValue *Double::execute() {
    return nullptr;
}

ReturnedValue *Float::execute() {
    return nullptr;
}

ReturnedValue *Int::execute() {
    return nullptr;
}

ReturnedValue *Timestamp::execute() {
    return nullptr;
}

ReturnedValue *TinyInt::execute() {
    return nullptr;
}

ReturnedValue *VarChar::execute() {
    return nullptr;
}
