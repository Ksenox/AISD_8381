#include "text_with_brackets_syntax_checker.h"

Text_with_brackets_syntax_checker::Text_with_brackets_syntax_checker()
{
    QFile log("D:\\ProgrammFiles\\QtProjects\\untitled1\\Logs.txt");
    log.open(QIODevice::WriteOnly);
    log.write("");
    log.close();
}

bool Text_with_brackets_syntax_checker::check_text_with_brackets_syntax(const char* text,
                                                                        unsigned int text_size,
                                                                        unsigned int left_border_position,
                                                                        int counter)
{
    QFile log("D:\\ProgrammFiles\\QtProjects\\untitled1\\Logs.txt");
    log.open(QIODevice::Append);
    log.write("Text_with_brackets_syntax_checker called ");
    log.write("Args= ");
    log.write(text);
    log.write("\n");
    log.close();

    for(unsigned int i = 0; i < text_size; i++)
    {
        if(is_element_a_left_bracket(text[i]) == true )
        {
            unsigned int right_bracket_position = find_right_bracket_pair(text + i, text_size - i);

            if(right_bracket_position == 0) throw Syntax_mistake(left_border_position + 1, REDUNANT_BRACKET);
            if(right_bracket_position == 1) throw Syntax_mistake(left_border_position + 1, NO_SYMBOL);

            check_text_with_brackets_syntax(text + i + 1, right_bracket_position - 1, left_border_position + 1, counter + 1);

            i = left_border_position + right_bracket_position;

            left_border_position = left_border_position + right_bracket_position + 1;
        }
        else
        {
             check_element_syntax(*(text + i), left_border_position);
             left_border_position += 1;
        }
    }

    return true;
}


bool Text_with_brackets_syntax_checker::check_element_syntax(char element, unsigned int left_border_position)
{
    if(is_element_a_right_bracket(element) == true) throw Syntax_mistake(left_border_position, REDUNANT_BRACKET);
    if(element != 'A' && element != 'B') throw Syntax_mistake(left_border_position, INCORRECT_SYMBOL);
    return true;
}


bool Text_with_brackets_syntax_checker::is_element_a_left_bracket(char symbol)
{
    switch(symbol)
    {
        case '{': return true;
        case '(': return true;
        case '[': return true;
        default: return false;
    }
}

bool Text_with_brackets_syntax_checker::is_element_a_right_bracket(char symbol)
{
    switch(symbol)
    {
        case '}': return true;
        case ')': return true;
        case ']': return true;
        default: return false;
    }
}

bool Text_with_brackets_syntax_checker::comparing_brackets_types(char left_bracket, char right_bracket)
{
    if(left_bracket == '(' && right_bracket == ')') return true;
    if(left_bracket == '{' && right_bracket == '}') return true;
    if(left_bracket == '[' && right_bracket == ']') return true;

    return false;
}

unsigned int Text_with_brackets_syntax_checker::find_right_bracket_pair(const char* left_bracket_element, unsigned int text_size)
{
    Stack stack;
    stack.add_to_stack(left_bracket_element[0]);
    unsigned int i = 1;
    while(stack.is_empty() != true && i < text_size)
    {
        if(is_element_a_left_bracket(left_bracket_element[i]) == true)
        {
            stack.add_to_stack(left_bracket_element[i]);
        }
        else if(is_element_a_right_bracket(left_bracket_element[i]) == true)
        {
            char left_bracket = stack.get_last_element();
            char right_bracket = left_bracket_element[i];

            if(comparing_brackets_types(left_bracket, right_bracket) == true)
            {
                stack.remove_last_element();
            }
            else
            {
                return 0;
            }
        }

        i++;
    }

    if(i == text_size && stack.is_empty() == false) return 0;

    return i-1;
}
