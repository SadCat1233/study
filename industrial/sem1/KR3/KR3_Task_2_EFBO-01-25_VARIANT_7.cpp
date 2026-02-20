#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream in("input1.txt");
    string number;
    int counter = 0, sum = 0;
    while (getline(in, number)) {
        counter++;
        sum += stoi(number);
    }
   double answer = sum / counter;
    in.close();
    ofstream out("output.txt");
    out << to_string(answer) << endl;
    out.close();
    return 0;
}