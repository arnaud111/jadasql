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
        parser/tree/operation/Operation.h
        parser/tree/from/From.h
        parser/tree/from/Joint.h
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
        parser/tree/operation/OperationPriority.h parser/tree/operation/Operation.cpp parser/tree/statements/UpdateStatement.cpp parser/tree/statements/UpdateStatement.h parser/tree/statements/DeleteStatement.cpp parser/tree/statements/DeleteStatement.h parser/tree/statements/DropStatement.cpp parser/tree/statements/DropStatement.h parser/tree/statements/InsertStatement.cpp parser/tree/statements/InsertStatement.h parser/tree/statements/CreateStatement.cpp parser/tree/statements/CreateStatement.h parser/tree/statements/AlterStatement.cpp parser/tree/statements/AlterStatement.h parser/tree/column_actions/ColumnModification.cpp parser/tree/column_actions/ColumnModification.h parser/tree/structure/Reference.cpp parser/tree/assign/Assign.cpp parser/tree/assign/Assign.h parser/tree/column_actions/ColumnDetail.cpp parser/tree/column_actions/ColumnDetail.h parser/tree/datatype/DataType.cpp parser/tree/datatype/DataType.h parser/tree/column_actions/ColumnConstraints.cpp parser/tree/column_actions/ColumnConstraints.h parser/tree/column_actions/constraints/PrimaryKey.h parser/tree/column_actions/constraints/ForeignKey.h parser/tree/column_actions/constraints/Check.h parser/tree/datatype/Char.h parser/tree/datatype/VarChar.h parser/tree/datatype/TinyInt.h parser/tree/datatype/Boolean.h parser/tree/datatype/Int.h parser/tree/datatype/Float.h parser/tree/datatype/Double.h parser/tree/datatype/Date.h parser/tree/datatype/DateTime.h parser/tree/datatype/Timestamp.h parser/tree/from/Joint.cpp parser/tree/from/Joint.cpp parser/tree/column_actions/constraints/Unique.h parser/tree/field/NullField.h parser/tree/column_actions/ColumnCreationInfo.h parser/tree/column_actions/ColumnCreationInfo.cpp)
