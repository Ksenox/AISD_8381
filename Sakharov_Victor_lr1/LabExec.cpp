#include "LabExec.h"

void SkipSpaces (std::string& str, int& pos) {
    while (str.length() > 0 && str[0] == ' ') {
        str = str.substr(1);
        pos++;
    }
}

void Skip (std::string& str, int& pos, const int indent, int n) {
    if (str.length() >= n) {
        ProceedOutput(str.substr(0, n), indent);
        str = str.substr(n);
        pos++;
        SkipSpaces(str, pos);
    }
}

//Проверка, что str начинается с aim и дальше находится не_буква
bool FindWord (std::string& str, int& pos, const int indent, const char* aim) {
    int len = strlen(aim);
    if (!str.compare(0, len, aim) && (len == str.length() || (len < str.length() && (!isalnum(str[len]) || !isalnum(aim[0]))))) {
        Skip(str, pos, indent, len);
        return true;
    }
    return false;
}

bool CheckStatement (std::string& str) {
    std::string copy = string(str);
    int position = 0;
    if (Statement(copy, position, 1)) {
        if (copy.empty()) {
            return true;
        }
        else ProceedError("End of string expected. \"" + copy + "\" left", position);
    }
    cout << "> " << str << endl << "> ";
    for (int i = 0; i < str.length() - copy.length(); ++i) {
        cout << " ";
    }
    cout << "^" << endl;
    return false;
}

// TRUE  |  FALSE | Name | NOT (Operand) | Operation (OperandList)
bool Statement (std::string& str, int& pos, const int indent) {
    if (FindWord(str, pos, indent, TRUE_S)) {
        return true;
    }
    else if (FindWord(str, pos, indent, FALSE_S)) {
        return true;
    }
    else if (Name(str, pos, indent)) {
        return true;
    }
    else if (FindWord(str, pos, indent, NOT_S)) {
        if (FindWord(str, pos, indent, OPEN_BRACKET)) {
            if (Operand(str, pos, indent + 1)) {
                if (FindWord(str, pos, indent, CLOSE_BRACKET)) {
                    return true;
                }
                else ProceedError("')' expected", pos);
            }
            else ProceedError("Operand expected", pos);
        }
        else ProceedError("'(' expected", pos);
    }
    else if (Operation(str, pos, indent + 1)) {
        if (FindWord(str, pos, indent, OPEN_BRACKET)) {
            if (OperandList(str, pos, indent + 1)) {
                if (FindWord(str, pos, indent, CLOSE_BRACKET)) {
                    return true;
                }
                else ProceedError("')' expected", pos);
            }
            else ProceedError("List of operands expected", pos);
        }
        else ProceedError("'(' expected", pos);
    }
    ProceedError("Statement expected", pos);
    return false;
}

// Letter
bool Name (std::string& str, int& pos, const int indent) {
    if ((str.length() == 1 && isalpha(str[0])) || (str.length() > 1 && isalpha(str[0]) && !isalnum(str[1]))) {
        Skip(str, pos, indent);
        return true;
    }
    return false;
}

// AND | OR
bool Operation (std::string& str, int& pos, const int indent) {
    if (FindWord(str, pos, indent, AND_S)) {
        return true;
    }
    else if (FindWord(str, pos, indent, OR_S)) {
        return true;
    }
    return false;
}

// Operand | Operand, OperandList
bool OperandList (std::string& str, int& pos, int indent, bool first) {
    if (Operand(str, pos, indent + 1)) {
        if (FindWord(str, pos, indent, COMMA)) {
            return OperandList(str, pos, indent, false);
        }
        return true;
    }
    //if (first) ProceedError("Operand expected", pos);
    return false;
}

// Statement
bool Operand (std::string& str, int& pos, const int indent) {
    return Statement(str, pos, indent);
}


