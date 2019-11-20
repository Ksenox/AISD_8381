#include "shellsort.h"

ShellSort::ShellSort()
{

}

QString ShellSort::Shell(QString str_n, int sequence, int flag){
    QStringList array = str_n.split(" ");

    int* a = new int[array.length()];
    for (int i = 0; i < array.length(); ++i)
            a[i] = array[i].toInt();

    int inc, i, j, s, inc_array[40];
    int size = array.length()-1;
    switch(sequence)
    {
        case 0:
            { s = incrementShell(inc_array, size); break; }
        case 1:
            { s = incrementSedgewick(inc_array, size); break; }
        case 2:
            { s = incrementHibbard(inc_array, size); break; }
        case 3:
            { s = incrementPratt(inc_array, size); break; }
        default:
            { exit(1); }
    }
    while (s >= 0)
    {
        inc = inc_array[s--];
        for (i = inc; i < size; i++)
        {
            int temp = a[i];
            for (j = i-inc; (j >= 0) && (a[j] > temp); j -= inc)
                a[j+inc] = a[j];
            a[j+inc] = temp;
            if(flag == 1)
            {
                QString arrayStr = QString::number(inc) + " : ";
                for(int k = 0; k < size; k++)
                {
                    if(a[k] == a[j+inc] && a[j+inc] != a[i])
                        arrayStr += "[" + QString::number(a[k]) + "]" + " ";
                    else
                        arrayStr += QString::number(a[k]) + " ";
                }
                QMessageBox out;
                out.setInformativeText("Ок - шаг алгоритма\nCancel - остановка");
                out.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                out.setIcon(QMessageBox::Information);
                out.setDefaultButton(QMessageBox::Ok);
                out.setText(arrayStr);
                out.setStyleSheet("QLabel{ width:250 px; font-size: 14px; } QPushButton{ width:125px; font-size: 18px; }");
                int res = out.exec();
                if (res == QMessageBox::Cancel)
                    return arrayStr;
            }
        }
    }
    QString arrayStr;
    for(int i = 0; i < size; i++)
        arrayStr += QString::number(a[i]) + " ";
    return arrayStr;
}

int ShellSort::incrementShell(int inc[], int size)
{
    if(size == 1) inc[0] = 1;
    int s = -1;
    size /= 2;
    while(size > 0)
        { inc[++s] = size; size /= 2; }
    reverseArray(inc, inc+s);
    return s >= 0 ? s : 0;
}

int ShellSort::incrementSedgewick(int inc[], int size)
{
    int pf = 1;//pow(2, s)
    int ps = 1;//pow(2, s/2)
    int pt = 1;//pow(2, (s+1)/2)
    int s = -1;
    do
    {
        if (++s % 2)
            inc[s] = 8*pf - 6*pt + 1;
        else
        {
            inc[s] = 9*pf - 9*ps + 1;
            ps *= 2;
            pt *= 2;
        }
        pf *= 2;
    } while(3*inc[s] < size);
    return s > 0 ? --s : 0;
}

int ShellSort::incrementHibbard(int inc[], int size)
{
    int s = -1, i = 1;
    while(pow(2, i) - 1 <= size)
        inc[++s] = int(pow(2, i++) - 1);
    return s--;
}

int ShellSort::incrementPratt(int inc[], int size)
{
    int pow2, pow3 = 1;
    int s = -1;
    size /= 2;
    while (pow3 <= size)
    {
        pow2 = pow3;
        while (pow2 <= size)
        {
            inc[++s] = pow2;
            pow2 = pow2 * 2;
        }
        pow3 = pow3 * 3;
    }
    std::sort(inc, inc+s+1);
    return s;
}

void ShellSort::reverseArray(int a[], int b[])
{
   if (a < b)
   { *a += *b; *b = *a - *b; *a -= *b;
       reverseArray(a + 1, b - 1); }
}
