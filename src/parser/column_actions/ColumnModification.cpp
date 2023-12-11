//
// Created by nono on 13/11/2023.
//

#include "../../../include/parser/tree/column_actions/ColumnModification.h"
#include "../../../include/error/Error.h"
#include "../../../include/lexer/symbol/keyword/KeywordSymbol.h"
#include "../../../include/lexer/symbol/keyword/StatementSymbol.h"
#include "../../../include/lexer/symbol/value/IdentifierSymbol.h"
#include "../../../include/parser/tree/statements/Statement.h"

ColumnModification::ColumnModification(std::vector<Symbol *> symbols) {

    std::vector<Symbol *> tmpSymbolList;

    this->dataType = nullptr;

    if (symbols.size() < 2) {
        printf("here\n");
        Error::syntaxError(symbols[symbols.size() - 1]);
    }

    if (symbols[0]->symbolValueType == s_Keyword) {
        switch (((KeywordSymbol *) symbols[0])->keyword) {
            case k_Add:
                this->modificationType = m_Add;
                break;
            case k_Modify:
                this->modificationType = m_Modify;
                break;
            case k_Change:
                this->modificationType = m_Change;
                break;
            default:
                Error::syntaxError(symbols[0]);
        }
    } else if (symbols[0]->symbolValueType == s_Statement) {
        switch (((StatementSymbol *) symbols[0])->keyword) {
            case v_Drop:
                this->modificationType = m_Drop;
                break;
            default:
                Error::syntaxError(symbols[0]);
        }
    } else {
        Error::syntaxError(symbols[0]);
    }

    if (symbols[1]->symbolValueType != s_Identifier) {
        Error::syntaxError(symbols[1]);
    }

    this->columnReference = new ColumnReference(((IdentifierSymbol *) symbols[1])->value);

    switch (this->modificationType) {
        case m_Add:
        case m_Modify:
            this->dataType = DataType::convertToDataType(Statement::cut_symbol_vector(symbols, 2, symbols.size()));
            if (this->dataType == nullptr) {
                Error::syntaxError(symbols[symbols.size() - 1]);
            }
            break;
        case m_Change:
            this->renameValue = new ColumnReference(((IdentifierSymbol *) symbols[2])->value);
            if (symbols.size() > 3) {
                Error::syntaxError(symbols[4]);
            }
            break;
        case m_Drop:
            if (symbols.size() > 2) {
                Error::syntaxError(symbols[3]);
            }
            break;
    }
}

ReturnedValue *ColumnModification::execute() {
    return nullptr;
}
