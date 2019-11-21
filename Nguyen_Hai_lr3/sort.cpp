#include "sort.h"


void SortSelection::swap(int &a, int &b) {
   int temp;
   temp = a;
   a = b;
   b = temp;
}
void SortSelection::selectionSort_1(int *arr, int size, string *analize, string *result) {
    int i,j, imin;
    analize->append("\n\n");

    for(i = 0; i < size - 1; i++){
        analize->append("Step ");
        analize->append(to_string(i+1).append(" :\n\t"));
        imin = i;
        for(j = i+1; j < size; j++){
            if(arr[j] < arr[imin]){
                imin = j;
            }
        }
        swap(arr[imin],arr[i]);
        for(int i = 0; i < size; i++){
            analize->append(to_string(arr[i]).append(" "));
        }
        analize->append("\n\n");
    }

    for(int i = 0; i < size; i++){
        result->append(to_string(arr[i]).append(" "));
    }
}

void SortSelection::selectionSort_2(int *arr, int size, string *analize, string *result) {
    int i, j, imin, imax;
    analize->append("\n\n");
    for(i = 0; i<int((size+1)/2); i++) {
        analize->append("Step ");
        analize->append(to_string(i+1).append(" :\n\t"));
        imin = i;
        imax = size -1-i;

        for(j = i+1; j<size; j++){
            if(arr[j] < arr[imin])
                imin = j;
        }
        swap(arr[i], arr[imin]);
        for(int i = 0; i < size; i++){
            analize->append(to_string(arr[i]).append(" "));
        }
        analize->append("\n\n");

        for(j = i+1; j<size-i; j++){
            if(arr[j]>arr[imax])
                imax = j;
        }

        swap(arr[size-1-i],arr[imax]);
        analize->append("\t");
        for(int i = 0; i < size; i++){
            analize->append(to_string(arr[i]).append(" "));
        }
        analize->append("\n\n");
    }

    for(int i = 0; i < size; i++){
        result->append(to_string(arr[i]).append(" "));
    }
}
