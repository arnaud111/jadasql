//
// Created by nono on 17/10/2023.
//

#include "../statements/SelectStatement.h"
#include "../structure/ColumnReference.h"
#include "../field/ConstStringField.h"
#include "../field/ConstNumberField.h"
#include "../function/FunctionField.h"

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

void FunctionField::display() {
    switch (this->function) {
        case f_Left:
            printf("LEFT() ");
            break;
        case f_Right:
            printf("RIGHT() ");
            break;
        case f_Max:
            printf("MAX() ");
            break;
        case f_Min:
            printf("MIN() ");
            break;
        case f_Sum:
            printf("SUM() ");
            break;
        case f_Count:
            printf("COUNT() ");
            break;
        case f_Concat:
            printf("CONCAT() ");
            break;
        case f_Format:
            printf("FORMAT() ");
            break;
        case f_Avg:
            printf("AVG() ");
            break;
        case f_IfNull:
            printf("IFNULL() ");
            break;
        case f_Coalesce:
            printf("COALESCE() ");
            break;
    }
}
