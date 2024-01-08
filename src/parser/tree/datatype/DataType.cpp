//
// Created by nono on 14/11/2023.
//

#include "parser/tree/datatype/DataType.h"
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
#include "lexer/symbol/keyword/DataTypeSymbol.h"
#include "lexer/symbol/keyword/DelimiterSymbol.h"
#include "error/Error.h"
#include "lexer/symbol/value/NumberSymbol.h"

Boolean::Boolean() : DataType() {
    this->type = d_Boolean;
    this->size = sizeof(bool);
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
    this->size = 10;
}

DateTime::DateTime(): DataType() {
    this->type = d_DateTime;
    this->size = 19;
}

Double::Double(): DataType() {
    this->type = d_Double;
    this->size = sizeof(double);
}

Float::Float(): DataType() {
    this->type = d_Float;
    this->size = sizeof(float);
}

Int::Int(): DataType() {
    this->type = d_Int;
    this->size = sizeof(int);
}

Timestamp::Timestamp(): DataType() {
    this->type = d_Timestamp;
    this->size = 13;
}

TinyInt::TinyInt(): DataType() {
    this->type = d_TinyInt;
    this->size = sizeof(short);
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

VarChar::VarChar(int size) {
    this->type = d_VarChar;
    this->size = size;
}

Char::Char(int size) {
    this->type = d_Char;
    this->size = size;
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

ReturnedValue *Boolean::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Char::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Date::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *DateTime::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Double::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Float::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Int::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Timestamp::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *TinyInt::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *VarChar::execute(ExecutionData *executionData) {
    return nullptr;
}
