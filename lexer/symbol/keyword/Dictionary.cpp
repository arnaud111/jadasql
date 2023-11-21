//
// Created by nono on 11/10/23.
//

#include "DataTypeSymbol.h"
#include "OperatorSymbol.h"
#include "StatementSymbol.h"
#include "KeywordSymbol.h"
#include "DelimiterSymbol.h"
#include <string>

int DataTypeSymbol::size = 10;
std::string DataTypeSymbol::stringValues[10] = {
        "CHAR",
        "VARCHAR",
        "TINYINT",
        "BOOLEAN",
        "INT",
        "FLOAT",
        "DOUBLE",
        "DATE",
        "DATETIME",
        "TIMESTAMP",
};

int OperatorSymbol::size = 23;
std::string OperatorSymbol::stringValues[23] = {
        ">",
        "<",
        ">=",
        "<=",
        "!=",
        "<>",
        "=",
        "+",
        "-",
        "*",
        "/",
        "%",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "&",
        "|",
        "^",
        "&=",
        "|*=",
        "^-=",
};

int StatementSymbol::size = 7;
std::string StatementSymbol::stringValues[7] = {
        "SELECT",
        "UPDATE",
        "DELETE",
        "DROP",
        "INSERT",
        "CREATE",
        "ALTER",
};

int KeywordSymbol::size = 64;
std::string KeywordSymbol::stringValues[64] = {
        "FROM",
        "VALUES",
        "WHERE",
        "DISTINCT",
        "AS",
        "IF",
        "AND",
        "OR",
        "NOT",
        "NULL",
        "SET",
        "LIMIT",
        "LIKE",
        "IN",
        "BETWEEN",
        "JOIN",
        "ON",
        "UNION",
        "HAVING",
        "EXISTS",
        "ANY",
        "ALL",
        "CASE",
        "WHEN",
        "THEN",
        "ELSE",
        "END",
        "SOME",
        "INTO",
        "MODIFY",
        "CHANGE",
        "ADD",
        "DATABASE",
        "TABLE",
        "UNIQUE",
        "PRIMARY",
        "FOREIGN",
        "REFERENCES",
        "KEY",
        "CHECK",
        "DEFAULT",
        "AUTO_INCREMENT",
        "INDEX",
        "IS",
        "ORDER",
        "BY",
        "ASC",
        "DESC",
        "INNER",
        "LEFT",
        "RIGHT",
        "CROSS",
        "GROUP",
        "MAX",
        "SUM",
        "COUNT",
        "CONCAT",
        "FORMAT",
        "MIN",
        "AVG",
        "IFNULL",
        "COALESCE",
};

int DelimiterSymbol::size = 6;
std::string DelimiterSymbol::stringValues[6] = {
        ")",
        "(",
        "@",
        ",",
        ";",
        ".",
};
