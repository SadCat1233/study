#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    ifstream readStream("input1.txt");
    string str, numberString;
    getline(readStream, str);
    readStream.close();
    for (int i : str) {
        if (48 >= i >= 57) {
            numberString = numberString + (char)i;
        }
        else {
            numberString = "";
        }
    }
}