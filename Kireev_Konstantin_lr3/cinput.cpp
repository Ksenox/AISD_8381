#include <cinput.h>
#include <shellsort.h>

int cinput()
{
    srand(time(0));
    int n, sequence;
    cout << "Num of elements: ";
    cin >> n;
    int arr[n];
    if(!n)
       { cout << "!Zero elements" << endl; exit(1); }
    for (int i = 0; i < n; i++)
        { arr[i] = rand()%1000; cout << arr[i] << " "; }
    cout << endl << "Gap length sequence: ";
    cout << endl << "0 for Shell gap";
    cout << endl << "1 for Sedgewick gap";
    cout << endl << "2 for Hibbard gap";
    cout << endl << "3 for Pratt gap";
    cout << endl << "Enter: ";
    cin >> sequence;
    shellSort(arr, n, sequence);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}

void shellSort(int a[], int size, int sequence)
{
    int inc, i, j, s, inc_array[100];
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
            { cout << "!Wrong sequence" << endl; exit(1); }
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
        }
    }
}

int incrementShell(int inc[], int size)
{
    if(size == 1) inc[0] = 1;
    int s = -1;
    size /= 2;
    while(size > 0)
        { inc[++s] = size; size /= 2; }
    reverseArray(inc, inc+s);
    return s >= 0 ? s : 0;
}

int incrementSedgewick(int inc[], int size)
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

int incrementHibbard(int inc[], int size)
{
    int s = -1, i = 1;
    while(pow(2, i) - 1 <= size)
        inc[++s] = pow(2, i++) - 1;
    return s--;
}

int incrementPratt(int inc[], int size)
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
    sort(inc, inc+s+1);
    return s;
}

void reverseArray(int a[], int b[])
{
   if (a < b)
   { *a += *b; *b = *a - *b; *a -= *b;
       reverseArray(a + 1, b - 1); }
}
