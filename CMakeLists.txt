cmake_minimum_required(VERSION 3.24.2)
project(jada)

set(CMAKE_CXX_STANDARD 11)

add_executable(jada main.cpp tree/statement/SqlStatement.h tree/statement/SelectStatement.h tree/target/SqlTarget.h list/List.h list/Node.h tree/target/TargetVal.h tree/from/FromClause.h tree/structure/Table.h tree/joint/Joint.h tree/joint/InnerJoin.h tree/joint/LeftJoin.h tree/joint/RightJoin.h tree/where/WhereClause.h tree/where/Expression.h tree/group/GroupClause.h tree/structure/Database.h tree/structure/Field.h tree/where/CompareEnum.h string/StringCase.h parser/Lexer.cpp parser/Lexer.h parser/Group.h parser/Symbol.h)
