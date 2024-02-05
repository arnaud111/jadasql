//
// Created by nono on 17/10/2023.
//

#include "parser/tree/statements/SelectStatement.h"
#include "parser/tree/structure/ColumnReference.h"
#include "parser/tree/field/ConstStringField.h"
#include "parser/tree/field/ConstNumberField.h"
#include "parser/tree/function/AvgFunction.h"
#include "parser/tree/function/CoalesceFunction.h"
#include "parser/tree/function/ConcatFunction.h"
#include "parser/tree/function/CountFunction.h"
#include "parser/tree/function/FormatFunction.h"
#include "parser/tree/function/IfNullFunction.h"
#include "parser/tree/function/LeftFunction.h"
#include "parser/tree/function/RightFunction.h"
#include "parser/tree/function/MinFunction.h"
#include "parser/tree/function/MaxFunction.h"
#include "parser/tree/function/SumFunction.h"
#include "parser/tree/statements/DropStatement.h"
#include "parser/tree/statements/DeleteStatement.h"
#include "parser/tree/assign/Assign.h"
#include "parser/tree/statements/UpdateStatement.h"
#include "parser/tree/statements/InsertStatement.h"
#include "parser/tree/statements/CreateStatement.h"
#include "parser/tree/datatype/Boolean.h"
#include "parser/tree/datatype/Char.h"
#include "parser/tree/datatype/Date.h"
#include "parser/tree/datatype/DateTime.h"
#include "parser/tree/datatype/Double.h"
#include "parser/tree/datatype/Float.h"
#include "parser/tree/datatype/Int.h"
#include "parser/tree/datatype/Timestamp.h"
#include "parser/tree/datatype/TinyInt.h"
#include "parser/tree/datatype/VarChar.h"
#include "parser/tree/field/NullField.h"
#include "parser/tree/column_actions/ColumnConstraints.h"
#include "parser/tree/column_actions/constraints/Unique.h"
#include "parser/tree/column_actions/constraints/ForeignKey.h"
#include "parser/tree/column_actions/constraints/PrimaryKey.h"
#include "parser/tree/column_actions/constraints/Check.h"
#include "parser/tree/column_actions/ColumnDetail.h"
#include "parser/tree/statements/AlterStatement.h"
#include "parser/tree/statements/ShowStatement.h"
#include "parser/tree/statements/UseStatement.h"

void UseStatement::display() {

    printf("USE ");
    this->database->display();
    printf(";\n");
}

void ShowStatement::display() {
    printf("SHOW ");
    switch (this->type) {
        case ShowDatabases:
            printf("DATABASES");
            break;
        case ShowTables:
            printf("TABLES");
            break;
    }
    printf(";\n");
}

void AlterStatement::display() {
    printf("ALTER TABLE ");
    this->table->display();
    for (auto &m: this->modifications) {
        m->display();
    }
    printf(";\n");
}


void CreateStatement::display() {
    printf("CREATE ");
    switch (this->type) {
        case CreateTable:
            printf("TABLE ");
            break;
        case CreateDatabase:
            printf("DATABASE ");
            break;
    }
    if (this->ifNotExist) {
        printf("IF NOT EXISTS ");
    }
    this->createdField->display();
    if (!this->columns.empty()) {
        printf("(");
        for (auto & c: this->columns) {
            if (c != nullptr) {
                c->display();
                printf(", ");
            }
        }
        printf(")");
    }
    printf(";\n");
}

void InsertStatement::display() {
    printf("INSERT INTO ");
    this->tableReference->display();
    if (this->columnsExplicit) {
        printf("(");
        for (auto & column : this->columns) {
            column->display();
            printf(", ");
        }
        printf(") ");
    }
    printf("VALUES ");
    for (auto & row : this->values) {
        printf("(");
        for (auto & value : row) {
            value->display();
        }
        printf("), ");
    }
    printf(";\n");
}

void UpdateStatement::display() {
    printf("UPDATE ");
    this->tableReference->display();
    printf("SET ");
    for (auto & assign : this->set) {
        assign->display();
    }
    if (this->where != nullptr) {
        printf("WHERE ");
        this->where->display();
    }
    printf(";\n");
}

void DeleteStatement::display() {
    printf("DELETE FROM ");
    this->table->display();
    if (this->where != nullptr) {
        printf("WHERE ");
        this->where->display();
    }
    printf(";\n");
}

void DropStatement::display() {
    printf("DROP ");
    switch (this->type) {
        case DropTable:
            printf("TABLE ");
            break;
        case DropDatabase:
            printf("DATABASE ");
            break;
    }
    if (this->ifExist) {
        printf("IF EXISTS ");
    }
    this->droppedField->display();
    printf(";\n");
}

void SelectStatement::display() {
    printf("SELECT ");
    if (this->distinct) {
        printf("DISTINCT ");
    }
    for (int i = 0; i < this->field.size(); i++) {
        this->field[i]->display();
        if (i != this->field.size() - 1) {
            printf(", ");
        }
    }
    if (this->from != nullptr) {
        printf("FROM ");
        this->from->display();
    }
    if (this->where != nullptr) {
        printf("WHERE ");
        this->where->display();
    }
    if (!this->groupBy.empty()) {
        printf("GROUP BY ");
        for (int i = 0; i < this->groupBy.size(); i++) {
            this->groupBy[i]->display();
            if (i != this->groupBy.size() - 1) {
                printf(", ");
            }
        }
    }
    if (!this->orderBy.empty()) {
        printf("ORDER BY ");
        for (int i = 0; i < this->orderBy.size(); i++) {
            this->orderBy[i]->display();
            if (i != this->orderBy.size() - 1) {
                printf(", ");
            }
        }
        if (this->asc) {
            printf("ASC ");
        } else {
            printf("DESC ");
        }
    }
    if (limit != -1) {
        printf("LIMIT %d", this->limit);
    }
    printf(";\n");
}

void ColumnModification::display() {
    switch (this->modificationType) {
        case m_Add:
            printf("ADD ");
            break;
        case m_Drop:
            printf("DROP ");
            break;
        case m_Modify:
            printf("MODIFY ");
            break;
        case m_Change:
            printf("CHANGE ");
            break;
    }
    this->columnReference->display();
    if (this->dataType != nullptr) {
        this->dataType->display();
    }
    if (this->renameValue != nullptr) {
        this->renameValue->display();
    }
}

void ColumnDetail::display() {
    this->name->display();
    this->dataType->display();
    if (this->notNull) {
        printf("NOT NULL ");
    }
    if (this->defaultValue) {
        printf("DEFAULT ");
        this->defaultValue->display();
    }
    if (this->autoIncrement) {
        printf("AUTO_INCREMENT ");
    }
}

void Unique::display() {
    printf("UNIQUE(");
    for (auto &col: this->columns) {
        col->display();
    }
    printf(", ");
    printf(") ");
}

void ForeignKey::display() {
    printf("FOREIGN KEY(");
    for (auto &col: this->columns) {
        col->display();
        printf(", ");
    }
    printf(") REFERENCES ");
    this->tableReference->display();
    printf("(");
    for (auto &col: this->references) {
        col->display();
        printf(", ");
    }
    printf(") ");
}

void PrimaryKey::display() {
    printf("PRIMARY KEY(");
    for (auto &col: this->columns) {
        col->display();
        printf(", ");
    }
    printf(") ");
}

void Check::display() {
    printf("CHECK(");
    this->condition->display();
    printf(") ");
}

void Boolean::display() {
    printf("BOOL ");
}

void Char::display() {
    printf("CHAR(%llu) ", this->size);
}

void Date::display() {
    printf("DATE ");
}

void DateTime::display() {
    printf("DATETIME ");
}

void Double::display() {
    printf("DOUBLE ");
}

void Float::display() {
    printf("FLOAT ");
}

void Int::display() {
    printf("INT ");
}

void Timestamp::display() {
    printf("TIMESTAMP ");
}

void TinyInt::display() {
    printf("TINYINT ");
}

void VarChar::display() {
    printf("VARCHAR(%llu) ", this->size);
}

void NullField::display() {
    printf("NULL ");
}

void Assign::display() {
    this->column->display();
    printf(" = ");
    this->value->display();
}

void TableReference::display() {
    if (this->databaseReference != nullptr) {
        printf("%s@", this->databaseReference->databaseName.c_str());
    }
    printf("%s ", this->tableName.c_str());
    if (!this->alias.empty()) {
        printf("%s ", this->alias.c_str());
    }
}

void DatabaseReference::display() {
    printf("%s ", databaseName.c_str());
}

void ColumnReference::display() {
    if (!this->tableName.empty()) {
        printf("%s.", this->tableName.c_str());
    }
    printf("%s ", this->columnName.c_str());
}

void Joint::display() {
    switch (this->joinType) {
        case InnerJoin:
            printf("INNER JOIN ");
            break;
        case LeftJoin:
            printf("LEFT JOIN ");
            break;
        case RightJoin:
            printf("RIGHT JOIN ");
            break;
    }
    if (this->table != nullptr) {
        this->table->display();
    }
    if (this->on != nullptr) {
        printf("ON ");
        this->on->display();
    }
}

void From::display() {
    table->display();
    for (auto &i: listJoint) {
        i->display();
    }
}

void Operation::display() {
    printf("(");
    this->field1->display();
    switch (this->operation) {
        case o_Or:
            printf("OR ");
            break;
        case o_And:
            printf("AND ");
            break;
        case o_Not:
            printf("NOT ");
            break;
        case o_In:
            printf("IN ");
            break;
        case o_Between:
            printf("BETWEEN ");
            break;
        case o_Like:
            printf("LIKE ");
            break;
        case o_Some:
            printf("SOME ");
            break;
        case o_Exists:
            printf("EXISTS ");
            break;
        case o_Greater:
            printf("> ");
            break;
        case o_GreaterEqual:
            printf(">= ");
            break;
        case o_Lower:
            printf("< ");
            break;
        case o_LowerEqual:
            printf("<= ");
            break;
        case o_NotEqual:
            printf("<> ");
            break;
        case o_Equal:
            printf("= ");
            break;
        case o_BitAnd:
            printf("& ");
            break;
        case o_BitOr:
            printf("| ");
            break;
        case o_BitXor:
            printf("^ ");
            break;
        case o_Add:
            printf("+ ");
            break;
        case o_Sub:
            printf("- ");
            break;
        case o_Mul:
            printf("* ");
            break;
        case o_Div:
            printf("/ ");
            break;
        case o_Mod:
            printf("%% ");
            break;
    }
    this->field2->display();
    printf(")");
}

void ConstStringField::display() {
    printf("\"%s\" (size : %zu)", this->value.c_str(), this->value.size());
}

void ConstNumberField::display() {
    printf("%d ", this->value);
}

void AvgFunction::display() {
    printf("AVG(");
    field->display();
    printf(") ");
}

void CoalesceFunction::display() {
    printf("COALESCE(");
    for (int i = 0; i < fields.size(); i++) {
        fields[i]->display();
        if (i < fields.size() - 1)
            printf(", ");
    }
    printf(") ");
}

void ConcatFunction::display() {
    printf("CONCAT(");
    for (int i = 0; i < fields.size(); i++) {
        fields[i]->display();
        if (i < fields.size() - 1)
            printf(", ");
    }
    printf(") ");
}

void CountFunction::display() {
    printf("COUNT(");
    field->display();
    printf(") ");
}

void FormatFunction::display() {
    printf("FORMAT(");
    field1->display();
    printf(", ");
    field2->display();
    printf(") ");
}

void IfNullFunction::display() {
    printf("IFNULL(");
    field1->display();
    printf(", ");
    field2->display();
    printf(") ");
}

void LeftFunction::display() {
    printf("LEFT(");
    field1->display();
    printf(", ");
    field2->display();
    printf(") ");
}

void RightFunction::display() {
    printf("RIGHT(");
    field1->display();
    printf(", ");
    field2->display();
    printf(") ");
}

void MinFunction::display() {
    printf("MIN(");
    field->display();
    printf(") ");
}

void MaxFunction::display() {
    printf("MAX(");
    field->display();
    printf(") ");
}

void SumFunction::display() {
    printf("SUM(");
    field->display();
    printf(") ");
}
