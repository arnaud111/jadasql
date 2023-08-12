cmake_minimum_required(VERSION 3.25)
project(jada)

set(CMAKE_CXX_STANDARD 11)

add_executable(jada main.cpp sql/parser/SqlStatementParser.h sql/statement/SqlStatement.h sql/statement/SelectStatement.h sql/target/SqlTarget.h list/List.h list/Node.h sql/target/TargetVal.h sql/from/FromClause.h sql/structure/Table.h sql/joint/Joint.h sql/joint/InnerJoin.h sql/joint/LeftJoin.h sql/joint/RightJoin.h sql/where/WhereClause.h sql/where/Expression.h sql/group/GroupClause.h sql/structure/Database.h sql/structure/Field.h sql/where/CompareEnum.h sql/parser/SqlFieldListParser.h sql/parser/StringParser.h string/StringCase.h)
