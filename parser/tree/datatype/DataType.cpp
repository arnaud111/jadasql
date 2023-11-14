//
// Created by nono on 14/11/2023.
//

#include "DataType.h"
#include "Boolean.h"
#include "Char.h"
#include "Date.h"
#include "DateTime.h"
#include "Double.h"
#include "Float.h"
#include "Int.h"
#include "Timestamp.h"
#include "TinyInt.h"
#include "VarChar.h"
#include "../../../lexer/symbol/keyword/DataTypeSymbol.h"
#include "../../../lexer/symbol/keyword/DelimiterSymbol.h"
#include "../../../error/Error.h"
#include "../../../lexer/symbol/value/NumberSymbol.h"

Boolean::Boolean() : DataType() {
    this->type = d_Boolean;
}

Char::Char(): DataType() {
    this->type = d_Char;
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
            case v_Char:
                return new Char();
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
            case v_Varchar:
                break;
        }
    } else if (symbols.size() == 4 && symbols[0]->symbolValueType == s_DataType && ((DataTypeSymbol *) symbols[0])->keyword == v_Varchar) {
        return new VarChar(symbols);
    }

    return nullptr;
}
