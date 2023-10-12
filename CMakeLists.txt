cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 11)

add_executable(jada main.cpp list/List.h list/Node.h lexer/Lexer.cpp lexer/Lexer.h lexer/symbol/Group.h lexer/symbol/Symbol.h parser/tree/statements/SelectStatement.h parser/tree/condition/Condition.h parser/tree/from/From.h parser/tree/condition/LogicalKeyword.h parser/tree/expression/Expression.h parser/Parser.cpp parser/Parser.h parser/tree/statements/Statement.h
        lexer/symbol/keyword/StatementKeyword.h
        lexer/symbol/keyword/OperatorKeyword.h
        lexer/symbol/keyword/DataTypeKeyword.h
        lexer/symbol/keyword/DelimiterKeyword.h
        lexer/symbol/SymbolValue.h
        lexer/symbol/StringSymbolValue.h
        lexer/symbol/keyword/Dictionary.cpp
        lexer/symbol/keyword/Keyword.h
        lexer/symbol/NumberSymbolValue.h)
