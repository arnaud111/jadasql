cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(jada main.cpp
        src/index/UniqueIndex.cpp
        src/lexer/Lexer.cpp
        src/parser/Parser.cpp
        src/lexer/symbol/keyword/Dictionary.cpp
        src/parser/tree/statements/Statement.cpp
        src/parser/tree/statements/SelectStatement.cpp
        src/parser/tree/from/From.cpp
        src/parser/tree/field/Field.cpp
        src/parser/tree/tree_item/TreeItemDisplay.cpp
        src/parser/tree/function/Function.cpp
        src/error/Error.cpp
        src/parser/tree/operation/Operation.cpp
        src/parser/tree/statements/UpdateStatement.cpp
        src/parser/tree/statements/DeleteStatement.cpp
        src/parser/tree/statements/DropStatement.cpp
        src/parser/tree/statements/InsertStatement.cpp
        src/parser/tree/statements/CreateStatement.cpp
        src/parser/tree/statements/AlterStatement.cpp
        src/parser/tree/column_actions/ColumnModification.cpp
        src/parser/tree/structure/Reference.cpp
        src/parser/tree/assign/Assign.cpp
        src/parser/tree/column_actions/ColumnDetail.cpp
        src/parser/tree/datatype/DataType.cpp
        src/parser/tree/column_actions/ColumnConstraints.cpp
        src/parser/tree/from/Joint.cpp
        src/parser/tree/from/Joint.cpp
        src/parser/tree/column_actions/ColumnCreationInfo.cpp
        src/data/DatabaseStructure.cpp
        src/data/TableStructure.cpp
        src/interpreter/ReturnedValue.cpp
        src/interpreter/values/ReturnedRowCount.cpp
        src/parser/tree/statements/ShowStatement.cpp
        src/parser/tree/statements/UseStatement.cpp
        src/interpreter/values/ReturnedRowData.cpp
        src/data/InformationSchemaLine.cpp src/data/InsertableField.cpp src/data/InsertableRow.cpp
        src/parser/tree/datatype/DataTypeExecute.cpp
        src/parser/tree/datatype/DataTypeRead.cpp)
