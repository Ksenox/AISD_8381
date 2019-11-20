#include "console.h"


using namespace std;
#define MAX_SIZE 6000
#define MAX_GROUP_SIZE 2000

void freeFirstSecond(int** firstPart,int** secondPart) {
    for (int i = 0; i < MAX_GROUP_SIZE; i++) {
        delete[] firstPart[i];
        delete[] secondPart[i];
    }
    delete[] firstPart;
    delete[] secondPart;
}


void Merging(int* inputArray, unsigned int size, int** firstPart, int** secondPart) {
    unsigned int firstLen = firstPart[0][0];
    unsigned int secondLen = secondPart[0][0];
    unsigned int len = 0;
    unsigned int fir = 1, sec = 1;
    bool flag = false;
    if (firstLen > secondLen) {
        len = secondLen;
        flag = true;
    }
    else {
        len = firstLen;
    }
    unsigned int i = 0,j=0,k=0,p=0;
    for (i = 1; i < len; i++) {
        for (j = p; j < (firstPart[i][0] + secondPart[i][0]-2)+p; j++) {
            if (fir != firstPart[i][0] && sec != secondPart[i][0] && firstPart[i][fir] <= secondPart[i][sec]) {
                inputArray[j] = firstPart[i][fir++];
                continue;
            }
            if (fir != firstPart[i][0] && sec != secondPart[i][0] && firstPart[i][fir] >= secondPart[i][sec]) {
                inputArray[j] = secondPart[i][sec++];
                continue;
            }
            if (fir == firstPart[i][0] && sec != secondPart[i][0]) {
                inputArray[j] = secondPart[i][sec++];
                continue;
            }
            if (fir != firstPart[i][0] && sec == secondPart[i][0]) {
                inputArray[j] = firstPart[i][fir++];
                continue;
            }

        }
        p = j;
        sec = 1;
        fir = 1;
    }
    fir = 1;
    if (flag)
        for (i = j; i < firstPart[len][0]; i++)
            inputArray[i++] = firstPart[len][fir++];
}


void splitIntoTwo(int* inputArray, int** firstPart, int** secondPart, unsigned int size) {
    unsigned int i = 0;
    unsigned int fir = 1;
    unsigned int sec = 1;
    unsigned int fir_arr = 1;
    unsigned int sec_arr = 1;
    bool flag = true;
    while (i < size) {
        if (i == 0 || (inputArray[i - 1] <= inputArray[i] && flag)) {
            firstPart[fir_arr][fir++] = inputArray[i++];
        }
        else if (inputArray[i - 1] >= inputArray[i]) {
            if (flag) {
                secondPart[sec_arr][sec++] = inputArray[i++];
                firstPart[fir_arr++][0] = fir;
                fir = 1;
                flag = false;
            }
            else {
                firstPart[fir_arr][fir++] = inputArray[i++];
                secondPart[sec_arr++][0] = sec;
                sec = 1;
                flag = true;
            }
        }
        else if (inputArray[i - 1] <= inputArray[i] && !flag) {
            secondPart[sec_arr][sec++] = inputArray[i++];
        }
    }
    flag == true ? firstPart[fir_arr][0] = fir : secondPart[sec_arr][0] = sec;
    flag == true ? fir_arr++ : sec_arr++;
    firstPart[0][0] = fir_arr;
    secondPart[0][0] = sec_arr;
}


void NaturalMergingSort(int* inputArray,unsigned int size,int& step) {
    unsigned int i = 0;
    //int step =1;
    for (;;) {
        int** firstPart = new int* [MAX_GROUP_SIZE];
        int** secondPart = new int* [MAX_GROUP_SIZE];
        for (i = 0; i < MAX_GROUP_SIZE; i++) {
            firstPart[i] = new int[MAX_SIZE];
            secondPart[i] = new int[MAX_SIZE];
        }
        firstPart[0][0] = 0;
        secondPart[0][0] = 0;
        splitIntoTwo(inputArray, firstPart, secondPart, size);
        if (secondPart[0][0] == 1) {
            freeFirstSecond(firstPart,secondPart);
            break;
        }
        step++;
        //cout<<"Step "<<step++<<"\nfirst: ";
        for (int i = 1; i < firstPart[0][0]; i++) {
            for (int j = 1; j < firstPart[i][0]; j++) {
               // cout<<firstPart[i][j]<<' ';
            }
           // cout <<"| ";
        }
        //cout<<"\nsecond: ";
        for (int i = 1; i < secondPart[0][0]; i++) {
            for (int j = 1; j < secondPart[i][0]; j++) {
              //  cout<<secondPart[i][j]<<' ';
            }
          //  cout <<"| ";
        }
        Merging(inputArray, size, firstPart, secondPart);
       // cout<<"\nAfter merging: ";
        for (int k = 0; k < size; k++) {
             //cout<<inputArray[k]<<' ';
        }
      //  cout<<"\n\n";
        freeFirstSecond(firstPart, secondPart);
    }
}

int consoleMain(){
     unsigned int n;
     srand(time(0));
     //n = rand () % 20 +20;
     n = 100;
     cout << "Numb of elements: "<<n<<"\n";
     int* inputArray = new int[n];
     if (n<=0) return 0;
    int step = 0;
     unsigned int i=0;
     for (i=0;i<n;i++){
         inputArray[i] = rand () % 10000 +1;
         //inputArray[i] = j--;
        // std::cout << inputArray[i] << " ";
     }
     //inputArray[i++] = 4;
     //inputArray[i] = 3;
    // cout<<"\n";
     NaturalMergingSort(inputArray,n,step);
    // cout<<"\nRESULT: ";
     for (i=0;i<n;i++){
         cout<<inputArray[i]<<' ';
     }
     cout<<'\n'<<step;
     cout<<"\n";
     return 0;
}



