#include <iostream>
#include <vector>

using namespace std;


vector<int> multiply(vector<int>& num1, vector<int>& num2) {
    vector<int> result;
    for (int i = 0; i < (num1.size() + num2.size()) + 1; i++) {
        result.push_back(0);
    }
    int temp_mult = 0;
    for (int i = 0; i < num2.size(); i++) {
        temp_mult = 0;
        for (int j = 0; j < num1.size(); j++) {
            int new_value = result[i + j] + (num2[i] * num1[j]) % 10 + temp_mult;
            result[i + j] = new_value % 10;
            temp_mult = ((num2[i] * num1[j]) / 10) + (new_value / 10);
        }
        if (temp_mult != 0) {
            result[i + num1.size()] += temp_mult;
        }
    }
    reverse(result.begin(), result.end());
    int ind = 0;
    while (result[ind] == 0) {
        result.erase(result.begin());
    }
    return result;
}


int main() {
    int n, m;
    cout << "Enter lenghts of numbers" << endl;
    cin >> n >> m;
    vector<int> number1, number2;
    srand(time(0));
    if (n < m) {
        n = n + m;
        m = n - m;
        n = n - m;
    }
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

    reverse(number1.begin(), number1.end());
    reverse(number2.begin(), number2.end());

    for (auto i : multiply(number1, number2)) {
        cout << i;
    }
    cout << " - result" << endl;
    return 0;
}