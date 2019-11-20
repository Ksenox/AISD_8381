include "NaturalMergingSort.h"

/*void splitIntoTwo(vector <int>& inputArray, vector <int>& firstPart, vector <int>& secondPart) {
    int flag = 1;
    int i = 0;
    while (i < inputArray.size()) {
        if (i == 0 || (inputArray[i - 1] <= inputArray[i] && flag)) {
            firstPart.push_back(inputArray[i++]);
        }
        else if (inputArray[i - 1] >= inputArray[i]) {
            flag == 1 ? secondPart.push_back(inputArray[i++]) : firstPart.push_back(inputArray[i++]);
            flag == 1 ? flag = 0 : flag = 1;
        }
        else if (inputArray[i - 1] <= inputArray[i] && !flag) {
            secondPart.push_back(inputArray[i++]);
        }
    }
}

void Merging(vector <int>& inputArray, vector <int>& firstPart, vector <int>& secondPart) {
    int flagSec = 0, flagFir = 0;
    int i = 0, fir = 0, sec = 0;
    int markSec = -1, markFir = -1;

    while (i < inputArray.size()||fir == firstPart.size() || sec == secondPart.size()) {
        if (fir > 0 && fir != firstPart.size() && firstPart[fir - 1] > firstPart[fir]&& markFir!=fir) {
            markFir = fir;
            flagFir++;
        }
        if (sec > 0 && sec != secondPart.size() && secondPart[sec - 1] > secondPart[sec]&& markSec!=sec) {
            markSec = sec;
            flagSec++;
        }
        if (flagFir > flagSec) {
            if (sec == 0) inputArray[i++] = secondPart[sec++];
            while (secondPart[sec - 1] < secondPart[sec]) {

                inputArray[i++] = secondPart[sec++];
                if (sec == secondPart.size()) break;
            }
            flagSec++;
        }
        if (flagFir < flagSec) {
            if (fir == 0) inputArray[i++] = firstPart[fir++];
            while (firstPart[fir - 1] < firstPart[fir]) {
                inputArray[i++] = firstPart[fir++];
                if (fir == firstPart.size()) break;
            }
            flagFir++;
        }
        if (fir == firstPart.size() || sec == secondPart.size()) break;

        if (flagFir == flagSec) {
            if (firstPart[fir] < secondPart[sec])
                inputArray[i++] = firstPart[fir++];
            else
                inputArray[i++] = secondPart[sec++];
        }
    }

    if (fir != firstPart.size() && sec == secondPart.size())
        while (i < inputArray.size()) {
            inputArray[i++] = firstPart[fir++];
        }
    else if (fir == firstPart.size() && sec != secondPart.size())
        while (i < inputArray.size()) {
            inputArray[i++] = secondPart[sec++];
        }
    firstPart.clear();
    secondPart.clear();
}

void NaturalMergingSort(vector <int>& inputArray) {
    int s1 = 1, s2 = 1;
    int flag = 1;
    vector <int> firstPart;
    vector <int> secondPart;
    for (;;) {
        splitIntoTwo(inputArray, firstPart, secondPart);
        if (secondPart.size() == 0) break;
        std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

        for (int j = 0; j < firstPart.size(); j++) {
            if (j > 0 && firstPart[j - 1] > firstPart[j]) cout << "| ";
            cout << firstPart[j] << " ";
        }
        std::cout << std::endl;
        for (int k = 0; k < secondPart.size(); k++) {
            if (k > 0 && secondPart[k - 1] > secondPart[k]) cout << "| ";
            std::cout << secondPart[k] << " ";
        }

        Merging(inputArray, firstPart, secondPart);
    }

    std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
    for (int l = 0; l < inputArray.size(); l++)
        std::cout << inputArray[l] << " ";
    std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

}
*/
