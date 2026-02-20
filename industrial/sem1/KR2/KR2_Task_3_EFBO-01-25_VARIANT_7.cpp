//Group: EFBO-01-25
//Student: Gamaev Pavel

#include <iostream>
typedef unsigned long long int ull;

using namespace std;


int factorial(int num, int arr[]) {
    ull result = 1;
    for (int i = 0; i < num; i++) {
        result *= (ull)arr[i];
    }
    return result;
}


int main() {
    int number;
    cin >> number;
    int arr[number];
    for (int i = 0; i < number; i++) {
        arr[i] = i + 1;
    }
    cout << factorial(number, arr) << endl;
}