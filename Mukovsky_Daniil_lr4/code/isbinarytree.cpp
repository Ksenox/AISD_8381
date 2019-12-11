#include "isbinarytree.h"

bool isBinaryTreereg(QString input)
{
    QRegExp reg( "^\\([A-z]+(\\([A-z]+((?1)|[A-z]*)\\)(\\([A-z]+((?1)|[A-z]*)\\))?)?\\)$" );
    return reg.exactMatch(input);
}
