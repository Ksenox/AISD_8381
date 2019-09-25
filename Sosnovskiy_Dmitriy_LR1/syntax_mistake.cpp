#include "syntax_mistake.h"

Syntax_mistake::Syntax_mistake(unsigned int mistake_position, mistake_type type_of_mistake) :
    mistake_position(mistake_position), type_of_mistake(type_of_mistake)
{

}

void Syntax_mistake::print_type_of_mistake(QTextBrowser * Answer_text_field)
{
    switch (type_of_mistake) {
        case REDUNANT_BRACKET:
            Answer_text_field->append("! - Содержится лишняя скобка \n");
            break;
        case NO_SYMBOL:
            Answer_text_field->append("! - Отсутствует необходимый символ (А или B) \n");
            break;
        case INCORRECT_SYMBOL:
            Answer_text_field->append("! - Присутствует недопустимый символ \n");
            break;
    }
}

void Syntax_mistake::print_text_to_mistake(QString outtext, QTextBrowser * Answer_text_field)
{
    Answer_text_field->setText(Answer_text_field->toPlainText() + outtext.left(mistake_position));
}


void Syntax_mistake::print_syntax_mistake(QString outtext, QTextBrowser * Answer_text_field)
{
    print_type_of_mistake(Answer_text_field);
    print_text_to_mistake(outtext, Answer_text_field);
}
