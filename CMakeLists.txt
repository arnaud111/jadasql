cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(jada main.cpp
        src/index/UniqueIndex.cpp
        src/lexer/Lexer.cpp
        src/parser/Parser.cpp
        src/lexer/symbol/keyword/Dictionary.cpp
        src/parser/statements/Statement.cpp
        src/parser/statements/SelectStatement.cpp
        src/parser/from/From.cpp
        src/parser/field/Field.cpp
        src/parser/tree_item/TreeItemDisplay.cpp
        src/parser/function/Function.cpp
        src/error/Error.cpp
        src/parser/operation/Operation.cpp
        src/parser/statements/UpdateStatement.cpp
        src/parser/statements/DeleteStatement.cpp
        src/parser/statements/DropStatement.cpp
        src/parser/statements/InsertStatement.cpp
        src/parser/statements/CreateStatement.cpp
        src/parser/statements/AlterStatement.cpp
        src/parser/column_actions/ColumnModification.cpp
        src/parser/structure/Reference.cpp
        src/parser/assign/Assign.cpp
        src/parser/column_actions/ColumnDetail.cpp
        src/parser/datatype/DataType.cpp
        src/parser/column_actions/ColumnConstraints.cpp
        src/parser/from/Joint.cpp
        src/parser/from/Joint.cpp
        src/parser/column_actions/ColumnCreationInfo.cpp
)
