cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 11)

add_executable(jada main.cpp list/List.h list/Node.h lexer/Lexer.cpp lexer/Lexer.h lexer/symbol/Symbol.h parser/tree/statements/SelectStatement.h parser/tree/condition/Condition.h parser/tree/from/From.h parser/tree/condition/LogicalKeyword.h parser/tree/expression/Expression.h parser/Parser.cpp parser/Parser.h parser/tree/statements/Statement.h
        lexer/symbol/keyword/StatementSymbol.h
        lexer/symbol/keyword/OperatorSymbol.h
        lexer/symbol/keyword/DataTypeSymbol.h
        lexer/symbol/keyword/DelimiterSymbol.h
        lexer/symbol/value/StringSymbol.h
        lexer/symbol/keyword/Dictionary.cpp
        lexer/symbol/keyword/KeywordSymbol.h
        lexer/symbol/value/NumberSymbol.h
        lexer/symbol/value/IdentifierSymbol.h
        parser/tree/statements/Statement.cpp
        parser/tree/statements/SelectStatement.cpp
        parser/tree/from/From.cpp
        parser/tree/field/Field.cpp
        parser/tree/condition/Condition.cpp
        parser/tree/structure/ColumnReference.h)
