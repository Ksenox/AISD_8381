#ifndef TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
#define TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
#include <stack.h>
#include <syntax_mistake.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <string>
class Text_with_brackets_syntax_checker
{
public:
    Text_with_brackets_syntax_checker();

    bool check_text_with_brackets_syntax(char* text, unsigned int text_size, unsigned int left_border_position);

    bool check_element_syntax(char element, unsigned int left_border_position);

    void write_to_logs_file(char *current_text, unsigned int text_size);

    bool comparing_brackets_types(char left_bracket, char right_bracket);

    bool is_element_a_left_bracket(char element);

    bool is_element_a_right_bracket(char element);

    unsigned int find_right_bracket_pair(char* left_bracket_element, unsigned int text_size, unsigned int left_border_position);

private:
    int recursion_depth;
    QFile *logs_file;

};

#endif // TEXT_WITH_BRACKETS_SYNTAX_CHECKER_H
