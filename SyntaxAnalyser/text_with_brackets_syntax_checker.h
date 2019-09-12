#ifndef TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
#define TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
#include <stack.h>
#include <syntax_mistake.h>
#include <fstream>
#include <QFile>
#include <QTextStream>
class Text_with_brackets_syntax_checker
{
public:
    Text_with_brackets_syntax_checker();

    bool check_text_with_brackets_syntax(const char* text, unsigned int text_size, unsigned int left_border_position, int counter);

    bool check_element_syntax(char element, unsigned int left_border_position);

    bool comparing_brackets_types(char left_bracket, char right_bracket);

    bool is_element_a_left_bracket(char element);

    bool is_element_a_right_bracket(char element);

    unsigned int find_right_bracket_pair(const char* left_bracket_element, unsigned int text_size);

};

#endif // TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
