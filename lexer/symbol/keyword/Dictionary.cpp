//
// Created by nono on 11/10/23.
//

#include "DataTypeKeyword.h"
#include "OperatorKeyword.h"
#include "StatementKeyword.h"
#include "Keyword.h"
#include "DelimiterKeyword.h"
#include <string>

int DataTypeKeyword::size = 10;
std::string DataTypeKeyword::stringValues[10] = {
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

int OperatorKeyword::size = 24;
std::string OperatorKeyword::stringValues[24] = {
        ">",
        "<",
        ">=",
        "<=",
        "==",
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

int StatementKeyword::size = 7;
std::string StatementKeyword::stringValues[7] = {
        "SELECT",
        "UPDATE",
        "DELETE",
        "DROP",
        "INSERT",
        "CREATE",
        "ALTER",
};

int Keyword::size = 55;
std::string Keyword::stringValues[55] = {
        "FROM",
        "WHERE",
        "AS",
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
        "DATABASE",
        "TABLE",
        "UNIQUE",
        "PRIMARY",
        "FOREIGN",
        "KEY",
        "CHECK",
        "DEFAULT",
        "INDEX",
        "IS",
        "ORDER",
        "BY",
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

int DelimiterKeyword::size = 5;
std::string DelimiterKeyword::stringValues[5] = {
    "(",
    ")",
    ",",
    ";",
    ".",
};
