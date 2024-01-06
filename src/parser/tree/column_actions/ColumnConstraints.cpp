//
// Created by nono on 14/11/2023.
//

#include "parser/tree/column_actions/ColumnConstraints.h"
#include "parser/tree/column_actions/constraints/Check.h"
#include "parser/tree/column_actions/constraints/ForeignKey.h"
#include "parser/tree/column_actions/constraints/PrimaryKey.h"
#include "parser/tree/column_actions/constraints/Unique.h"
#include "parser/tree/statements/Statement.h"
#include "error/Error.h"
#include "lexer/symbol/keyword/KeywordSymbol.h"
#include "lexer/symbol/keyword/DelimiterSymbol.h"
#include "lexer/symbol/value/IdentifierSymbol.h"

Check::Check(std::vector<Symbol *> symbols) : ColumnConstraints() {

    std::vector<Symbol *> tmpSymbolList;

    this->condition = nullptr;
    this->columnConstrainsType = c_Check;
    this->columnCreationType = t_ColumnConstraints;

    if (symbols.size() < 4) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[0])->keyword != k_Check) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[1])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[1]);
    }
    if (symbols[symbols.size() - 1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, 2, symbols.size() - 1);

    this->condition = Field::convertToField(tmpSymbolList);

    if (this->condition == nullptr) {
        Error::syntaxError(symbols[2]);
    }
}

ForeignKey::ForeignKey(std::vector<Symbol *> symbols) : ColumnConstraints() {

    std::vector<Symbol *> tmpSymbolList;
    this->tableReference = nullptr;
    this->columnConstrainsType = c_ForeignKey;
    this->columnCreationType = t_ColumnConstraints;
    unsigned long long index = 0;

    if (symbols.size() < 5) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[0])->keyword != k_Foreign) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[1])->keyword != k_Key) {
        Error::syntaxError(symbols[1]);
    }

    if (symbols[2]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[2])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[2]);
    }

    tmpSymbolList = Statement::splitUntilRightParenthesis(symbols, 3);

    for (auto &col: Statement::splitComa(tmpSymbolList)) {
        if (col.size() != 1 || col[0]->symbolValueType != s_Identifier) {
            Error::syntaxError("FOREIGN KEY");
        }
        this->columns.push_back(new ColumnReference(((IdentifierSymbol *) col[0])->value));
    }

    if (this->columns.empty()) {
        Error::syntaxError("Empty FOREIGN KEY Constraint");
    }

    if (symbols[4 + tmpSymbolList.size()]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[4 + tmpSymbolList.size()])->keyword != k_References) {
        Error::syntaxError("REFERENCES not found in FOREIGN KEY constraint");
    }

    if (symbols[5 + tmpSymbolList.size()]->symbolValueType != s_Identifier) {
        Error::syntaxError("TABLE not found after REFERENCES in FOREIGN KEY constraint");
    }
    index = 5 + tmpSymbolList.size();
    tmpSymbolList = Statement::splitUntilParenthesisOrKeyword(symbols, index, {});
    this->tableReference = new TableReference(tmpSymbolList);
    index += tmpSymbolList.size();

    if (symbols[index]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[index])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[index]);
    }
    if (symbols[symbols.size() - 1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, index + 1, symbols.size() - 1);

    for (auto &col: Statement::splitComa(tmpSymbolList)) {
        if (col.size() != 1 || col[0]->symbolValueType != s_Identifier) {
            Error::syntaxError("REFERENCES ");
        }
        this->references.push_back(new ColumnReference(((IdentifierSymbol *) col[0])->value));
    }

    if (this->references.empty()) {
        Error::syntaxError("Empty REFERENCE in FOREIGN KEY Constraint");
    }
}

PrimaryKey::PrimaryKey(std::vector<Symbol *> symbols) : ColumnConstraints() {

    std::vector<Symbol *> tmpSymbolList;
    this->columnConstrainsType = c_PrimaryKey;
    this->columnCreationType = t_ColumnConstraints;

    if (symbols.size() < 5) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[0])->keyword != k_Primary) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[1])->keyword != k_Key) {
        Error::syntaxError(symbols[1]);
    }

    if (symbols[2]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[2])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[2]);
    }
    if (symbols[symbols.size() - 1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, 3, symbols.size() - 1);

    for (auto &col: Statement::splitComa(tmpSymbolList)) {
        if (col.size() != 1 || col[0]->symbolValueType != s_Identifier) {
            Error::syntaxError("PRIMARY KEY");
        }
        this->columns.push_back(new ColumnReference(((IdentifierSymbol *) col[0])->value));
    }

    if (this->columns.empty()) {
        Error::syntaxError("Empty PRIMARY KEY Constraint");
    }
}

Unique::Unique(std::vector<Symbol *> symbols) : ColumnConstraints() {

    std::vector<Symbol *> tmpSymbolList;
    this->columnConstrainsType = c_Unique;
    this->columnCreationType = t_ColumnConstraints;

    if (symbols.size() < 4) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType != s_Keyword || ((KeywordSymbol *) symbols[0])->keyword != k_Unique) {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[1])->keyword != v_ParenthesisLeft) {
        Error::syntaxError(symbols[1]);
    }
    if (symbols[symbols.size() - 1]->symbolValueType != s_Delimiter || ((DelimiterSymbol *) symbols[symbols.size() - 1])->keyword != v_ParenthesisRight) {
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    tmpSymbolList = Statement::cut_symbol_vector(symbols, 2, symbols.size() - 1);

    for (auto &col: Statement::splitComa(tmpSymbolList)) {
        if (col.size() != 1 || col[0]->symbolValueType != s_Identifier) {
            Error::syntaxError("UNIQUE");
        }
        this->columns.push_back(new ColumnReference(((IdentifierSymbol *) col[0])->value));
    }

    if (this->columns.empty()) {
        Error::syntaxError("Empty UNIQUE Constraint");
    }
}

ColumnConstraints *ColumnConstraints::convertToColumnConstraints(std::vector<Symbol *> symbols) {

    ColumnConstraints *columnConstraints = nullptr;

    if (symbols.empty()) {
        return columnConstraints;
    }

    if (symbols[0]->symbolValueType != s_Keyword) {
        return columnConstraints;
    }

    if (((KeywordSymbol *) symbols[0])->keyword == k_Unique) {
        columnConstraints = new Unique(symbols);
    } else if (((KeywordSymbol *) symbols[0])->keyword == k_Primary) {
        columnConstraints = new PrimaryKey(symbols);
    } else if (((KeywordSymbol *) symbols[0])->keyword == k_Foreign) {
        columnConstraints = new ForeignKey(symbols);
    } else if (((KeywordSymbol *) symbols[0])->keyword == k_Check) {
        columnConstraints = new Check(symbols);
    }

    return columnConstraints;
}

ReturnedValue *Check::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *ForeignKey::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *PrimaryKey::execute(ExecutionData *executionData) {
    return nullptr;
}

ReturnedValue *Unique::execute(ExecutionData *executionData) {
    return nullptr;
}
