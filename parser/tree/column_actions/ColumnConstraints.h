//
// Created by nono on 14/11/2023.
//

#ifndef JADA_COLUMNCONSTRAINTS_H
#define JADA_COLUMNCONSTRAINTS_H

enum ColumnConstrainsType {
    c_Check,
    c_PrimaryKey,
    c_ForeignKey,
};

class ColumnConstraints {

public:

    ColumnConstrainsType type;

};


#endif //JADA_COLUMNCONSTRAINTS_H
