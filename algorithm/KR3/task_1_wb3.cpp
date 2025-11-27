#include <iostream>
#include <vector>

using namespace std;


vector<int> add(vector<int>& num1, vector<int>& num2) {
    vector<int> result;
    auto temp = 0;
    for (auto i = (int)num1.size() - 1; i >= 0; i--) {
        result.push_back((num1[i] + num2[i] + temp) % 10);
        temp = (num1[i] + num2[i] + temp) / 10;
    }
    if (temp != 0) {
        result.push_back(temp);
    }
    reverse(result.begin(), result.end());
    return result;
}


vector<int> sub(vector<int>& num1, vector<int>& num2) {
    vector<int> result;
    for (auto i = (int)num1.size() - 1; i >= 0; i--) {
        if (num1[i] < num2[i]) {
            num1.swap(num2);
        }
    }
    auto temp = 0;
    for (auto i = (int)num1.size() - 1; i >= 0; i--) {
        if ((num1[i] + temp) < num2[i]) {
            result.push_back(num1[i] + 10 - num2[i] + temp);
            temp = -1;
        }
        else {
            result.push_back(num1[i] - num2[i] + temp);
            temp = 0;
        }
    }
    reverse(result.begin(), result.end());
    return result;
}


int main() {
    int n, m;
    cout << "Enter lenghts of numbers" << endl;
    cin >> n >> m;
    vector<int> number1, number2;
    srand(time(0));
    for (auto i = 0; i < n; i++) {
        number1.push_back(rand() % 10);
        cout << number1[i];
    }
    cout << " - number1" << endl;

    for (auto i = 0; i < m; i++) {
        number2.push_back(rand() % 10);
        cout << number2[i];
    }
    cout << " - number2" << endl;

    if (n > m) {
        for (auto i = 0; i < (n - m); i++) {
            number2.insert(number2.begin(), 0);
        }
    }
    else {
        for (auto i = 0; i < (m - n); i++) {
            number1.insert(number1.begin(), 0);
        }
    }

    for (auto i : sub(number1, number2)) {
        cout << i;
    }
    cout << " - result sub" << endl;

    for (auto i : add(number1, number2)) {
        cout << i;
    }
    cout << " - result add" << endl;
    return 0;
}