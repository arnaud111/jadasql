cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 11)

add_executable(jada main.cpp
        list/List.h
        list/Node.h
        lexer/Lexer.cpp
        lexer/Lexer.h
        lexer/symbol/Symbol.h
        parser/tree/statements/SelectStatement.h
        parser/tree/condition/Condition.h
        parser/tree/from/From.h
        parser/tree/from/Joint.h
        parser/tree/condition/LogicalKeyword.h
        parser/tree/expression/Expression.h
        parser/Parser.cpp
        parser/Parser.h
        parser/tree/statements/Statement.h
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
        parser/tree/field/Field.h
        parser/tree/field/ConstNumberField.h
        parser/tree/field/ConstStringField.h
        parser/tree/condition/Condition.cpp
        parser/tree/structure/ColumnReference.h
        parser/tree/structure/DatabaseReference.h
        parser/tree/structure/TableReference.h
        parser/tree/tree_item/TreeItemDisplay.cpp
        parser/tree/tree_item/TreeItem.h
        parser/tree/function/SumFunction.h
        parser/tree/function/RightFunction.h
        parser/tree/function/MinFunction.h
        parser/tree/function/MaxFunction.h
        parser/tree/function/LeftFunction.h
        parser/tree/function/IfNullFunction.h
        parser/tree/function/Function.cpp
        parser/tree/function/FormatFunction.h
        parser/tree/function/CountFunction.h
        parser/tree/function/ConcatFunction.h
        parser/tree/function/CoalesceFunction.h
        parser/tree/function/AvgFunction.h
        error/Error.cpp
        parser/tree/condition/OperationPriority.h)
