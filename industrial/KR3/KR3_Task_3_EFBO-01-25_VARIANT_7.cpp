#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream in("input2.txt");
    string text;
    getline(in, text);
    cout << text.size() << endl;
    return 0;
}