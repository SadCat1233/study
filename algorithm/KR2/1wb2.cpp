#include <iostream>

using namespace std;

int nod(int num1, int num2) {
    int res;
    while ((num1 % num2) != 0) {
        int temp;
        temp = num2;
        if (num2 > (num1 % num2)) {
            num2 = num1 % temp;
            num1 = temp;
        }
        else {
            num1 = num1 % num2;
        }
    }
    if (num1 > num2) {
        res = num2;
    }
    else {
        res = num1;
    }
    return res;
}


int main() {
    int number1, number2, number3;
    cin >> number1 >> number2 >> number3;
    int nod_1_2;
    nod_1_2 = nod(number1, number2);
    cout << nod(nod_1_2, number3) << endl;
}


