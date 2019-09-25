#ifndef SYNTAX_MISTAKE_H
#define SYNTAX_MISTAKE_H
#include <QTextBrowser>
enum mistake_type{
    REDUNANT_BRACKET,
    INCORRECT_SYMBOL,
    NO_SYMBOL
};



class Syntax_mistake
{
public:
    Syntax_mistake(unsigned int mistake_position, mistake_type type_of_mistake);
    void print_syntax_mistake(QString outtext, QTextBrowser * Answer_text_field);
private:
    void print_type_of_mistake(QTextBrowser * Answer_text_field);
    void print_text_to_mistake(QString outtext, QTextBrowser * Answer_text_field);
    unsigned int mistake_position;
    mistake_type type_of_mistake;
};

#endif // SYNTAX_MISTAKE_H
