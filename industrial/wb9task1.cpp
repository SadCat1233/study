#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string banChars = "useragmnt";
    ifstream readStream("input.txt");
    string str, newStr;
    getline(readStream, str);
    for (int chr : str) {
        bool flag = true;
        for (int banChar : banChars) {
            if (chr == banChar || (chr - 32) == banChar) {
                flag = false;
            }
        }
        if (flag) {
            newStr = newStr + (char)chr;
        }
    }
    readStream.close();
    ofstream writeStream("output.txt");
    writeStream << newStr;
}