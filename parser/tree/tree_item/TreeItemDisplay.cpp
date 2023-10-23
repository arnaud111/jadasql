//
// Created by nono on 17/10/2023.
//

#include "../statements/SelectStatement.h"
#include "../structure/ColumnReference.h"
#include "../field/ConstStringField.h"
#include "../field/ConstNumberField.h"
#include "../function/AvgFunction.h"
#include "../function/CoalesceFunction.h"
#include "../function/ConcatFunction.h"
#include "../function/CountFunction.h"
#include "../function/FormatFunction.h"
#include "../function/IfNullFunction.h"
#include "../function/LeftFunction.h"
#include "../function/RightFunction.h"
#include "../function/MinFunction.h"
#include "../function/MaxFunction.h"
#include "../function/SumFunction.h"

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
    }
    if (limit != -1) {
        printf("LIMIT %d", this->limit);
    }
    printf(";\n");
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
        case Join:
            printf("JOIN ");
            break;
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
    table->display();
    printf("ON ");
    on->display();
}

void From::display() {
    table->display();
    for (auto &i: listJoint) {
        i->display();
    }
}

void Condition::display() {
    this->expression1->display();
    switch (*this->logicalKeyword) {
        case AND:
            printf("AND ");
            break;
        case OR:
            printf("OR ");
            break;
    }
    this->expression2->display();
}

void ConstStringField::display() {
    printf("\"%s\" ", this->value.c_str());
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
