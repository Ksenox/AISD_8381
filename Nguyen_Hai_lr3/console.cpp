#include "console.h"
console::console(){
    Method = new(method);
}

void console::Console(bool flagCase_1, bool flagCase_2,int* flagError, string *result, string *analize,QString data){
    if(flagCase_1 == false && flagCase_2 == false){
        *flagError = 2;
        return;
    }
    else {
        QStringList text_in = data.split(' ');
        int* arr = new int[100];
        int i = 0;
        for(auto x:text_in){
            bool flagConvert;
            x.toInt(&flagConvert);
            if(flagConvert == false){
                *flagError = 1;
                return;
            }
            else {
                arr[i] = x.toInt();
                i++;
            }
        }

        analize->append("Arrays length : ");
        analize->append(to_string(i));
        if(flagCase_1){
            analize->append("\n\nRecusion deep : ");
            analize->append(to_string(i-1));
            Method->selectionSort_1(arr,i,analize,result);
        }
        else if(flagCase_2){
            analize->append("\n\nRecusion deep : ");
            analize->append(to_string(int((i+1)/2)));
            Method->selectionSort_2(arr,i,analize,result);
        }

    }
}
