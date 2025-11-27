#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    ifstream readStream("input1.txt");
    string georgeKarlin;
    getline(readStream, georgeKarlin);
    readStream.close();
    ifstream readStream("input1.txt");
    string danilaProdolniy;
    getline(readStream, danilaProdolniy);
    readStream.close();
    size_t ind = georgeKarlin.find(danilaProdolniy);
    if (ind != string::npos) {
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
}