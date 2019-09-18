#include <iostream>
#include <string>
#include <fstream>
#include <fstream>

using namespace std;
char choice;
int depht = 0;
void Permutation(int *str,int i,int len){
    if(choice == 'f'){
        ofstream fil_n;
        fil_n.open("/home/veronica/programming/labfirst/text.txt", ios::app); //opening file to add results
        if ( i == len ){
            for(int j = 0; j < len; j++){
                fil_n << str[j] << ' ';
            }
            fil_n << endl;
            fil_n.close();
        }
        else{
            for(int j = i; j < len; j++){
                swap(str[i], str[j]);
                depht++;
                Permutation(str, i + 1, len);
                swap(str[i], str[j]);

            }
        }
    }
    else{
        if ( i == len ){
            for(int j = 0; j < len; j++){
                cout << str[j] << ' ';
            }
            cout << endl;
        }
        else{
            for(int j = i; j < len; j++){
                swap(str[i], str[j]);
                depht++;
                Permutation(str, i + 1, len); // cout temporary results
                swap(str[i], str[j]);

            }
        }
    }
}

int main() {
    int *mass;
    int n;
    cout << "Введите количество чисел:" << endl; // make check what all numbers are integer
    cin >> n;
    mass = new int[n];
    cout << "Откуда будут взяты значения?";
    cin >> choice;
    if (choice == 'c'){
        cout << "Введите числа:" << endl;
        for(int i =0; i< n; i++){
            cin >> mass[i];
            }
        if(cin.fail()){
            cout << "You have entered wrong input" <<endl;
            return 0;
        }
        Permutation(mass, 0, n);
    }
    else {
        ifstream fil;
        fil.open("/home/veronica/programming/labfirst/text.txt"); // open file to get information
        for(int i =0; i< n; i++) {
            fil >> mass[i];
            if(fil.fail()){
                cout << "You have entered wrong input" <<endl;
                return 0;
            }
        }
        if(fil.fail()){
            cout << "You have entered wrong input" <<endl;
            return 0;
        }
        if(!fil.is_open()) cout<<"ERROR";
        fil.close();
        Permutation(mass, 0, n);
    }
    cout << depht <<endl;
    return 0;
}