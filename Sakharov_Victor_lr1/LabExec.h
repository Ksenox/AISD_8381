#ifndef LABEXEC_H
#define LABEXEC_H

#include "structs.h"
#include "LabIo.h"

#define TRUE_S "TRUE"
#define FALSE_S "FALSE"
#define NOT_S "NOT"
#define AND_S "AND"
#define OR_S "OR"
#define OPEN_BRACKET "("
#define CLOSE_BRACKET ")"
#define COMMA ","

/*22. Построить синтаксический анализатор для определённого далее понятия логическое_выражение.
логическое_выражение ::= TRUE  |  FALSE | идентификатор | NOT (операнд) | операция (операнды)
идентификатор::=буква
операция::= AND | OR
операнды::= операнд | операнд, операнды
операнд::= логическое_выражение*/

void SkipSpaces (std::string& str, int& pos);

void Skip (std::string& str, int& pos, int indent, int n = 1);

bool FindWord (string& str, int& pos, int indent, const char* aim);

bool CheckStatement (std::string& str);

bool Statement (std::string& str, int& pos, int indent);

bool Name (std::string& str, int& pos, int indent);

bool Operation (std::string& str, int& pos, int indent);

bool OperandList (std::string& str, int& pos, int indent, bool first = true);

bool Operand (std::string& str, int& pos, int indent);

#endif //LABEXEC_H
