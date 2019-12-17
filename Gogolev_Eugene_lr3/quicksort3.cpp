#include "quicksort3.h"

void qsort3way(string& s, array_list& list, int l, int r, int depth)
{
    if (l >= r)
    {
        return;
    }
    int lt = l; // We initiate lt to be the part that is less than the pivot
    int gt = r;  //The part that is greater than the pivot
    int pivot = list[l + (rand() % (r - l))];//The pivot, chosen to be the random element of the array
    int i = l; //We scan the array from left to right
    while (i <= gt) // Starting from the first element.
    {
        if (list[i] < pivot)
        {
            int t = list[lt];
            list[lt] = list[i];
            list[i] = t;
            lt += 1;
            i += 1;
        }
        else if (list[i] > pivot)
        {
            int t = list[gt];
            list[gt] = list[i];
            list[i] = t;
            gt -= 1;
        }
        else
        {
            i += 1;
        }
    }
    s += log(list, l, r, pivot, depth);
    qsort3way(s, list, l, lt - 1, depth + 1);
    qsort3way(s, list, gt + 1, r, depth + 1);
}


string log(array_list &list, int min, int max, int center, int depth)
{
    string s = "";
    for (int i = 0; i < list.size(); i++)
    {
        s += to_string(list[i]) + ' ';
    }
    s += '\n';
    for (int i = 0; i < list.size(); i++)
    {
        if (i == min) s += "[--";
        else if (list[i] == center) s += "^--";
        else if (i > min && i < max) s += "---";
        else if (i == max) s += "]  ";
        else s += "   ";
    }
    s += " l:" + to_string(min) + " r:" + to_string(max) + " center: " + to_string(center) + " depth: " + to_string(depth) +'\n';
    return s;
}
