#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;


void normalizeNumber(vector<int>& number, int n) {
    int size = number.size();
    for (int i = 0; i < n - size; i++) {
        number.insert(number.begin(), 0);
    }
}


int checkSum(vector<int> data) {
    int res = 0;
    for (auto i : data) {
        res += i;
    }
    return res;
}


void printArray(vector<int> &number, string message) {
    for (auto elem : number) {
        cout << elem;
    }
    if (message != "") {
        cout << " - " << message << endl;
    }
    cout << endl;
}


void tenPowerMultiply(vector<int> &number, int n) {
    for (int i = 0; i < n; i++) {
        number.push_back(0);
    }
}


vector<int> add(vector<int>& num1, vector<int>& num2) {
    normalizeNumber(num1, num2.size());
    normalizeNumber(num2, num1.size());
    vector<int> result;
    auto temp = 0;
    for (auto i = (int)num1.size() - 1; i >= 0; i--) {
        result.push_back((num1[i] + num2[i] + temp) % 10);
        if ((num1[i] + num2[i] + temp) != 0) {
            temp = (num1[i] + num2[i] + temp) / 10;
        }
    }
    if (temp != 0) {
        result.push_back(temp);
    }
    reverse(result.begin(), result.end());
    if (checkSum(result) != 0) {
        while (result[0] == 0) {
            result.erase(result.begin());
        }
    }
    return result;
}


vector<int> sub(vector<int>& num1, vector<int>& num2) {
    normalizeNumber(num1, num2.size());
    normalizeNumber(num2, num1.size());
    vector<int> result;
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
    if (checkSum(result) != 0) {
        while (result[0] == 0) {
            result.erase(result.begin());
        }
    }
    return result;
}


vector<int> multiply(vector<int>& num1, vector<int>& num2) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
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
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    return result;
}


vector<int> mult(vector<int>& number1, vector<int>& number2, int n) {
    if (n > 2) {
        vector<int> halfNumber1First(number1.begin(), number1.begin() + n / 2),
            halfNumber1Second(number1.begin() + n / 2, number1.end()), 
            halfNumber2First(number2.begin(), number2.begin() + n / 2), 
            halfNumber2Second(number2.begin() + n / 2, number2.end());

        vector<int> tempSum1 = add(halfNumber1First, halfNumber1Second);
        vector<int> tempSum2 = add(halfNumber2First, halfNumber2Second);
        int maxTempSumSize = max((int)tempSum1.size(), (int)tempSum2.size()) >= 2 ? max((int)tempSum1.size(), (int)tempSum2.size()) : 2;
        normalizeNumber(tempSum1, pow(2, ceil(log2(maxTempSumSize))));
        normalizeNumber(tempSum2, pow(2, ceil(log2(maxTempSumSize))));

        vector<int> temp1 = mult(halfNumber1First, halfNumber2First, n / 2);
        vector<int> temp2 = mult(halfNumber1Second, halfNumber2Second, n / 2);
        vector<int> temp3 = mult(tempSum1, tempSum2, (int)tempSum1.size());

        temp3 = sub(temp3, temp2);
        temp3 = sub(temp3, temp1);
        tenPowerMultiply(temp3, n / 2);
        tenPowerMultiply(temp1, n);
        temp2 = add(temp2, temp3);
        temp1 = add(temp2, temp1);

        return temp1;
    }
    else {
        normalizeNumber(number1, 2);
        normalizeNumber(number2, 2);

        int temp1 = number1[0] * number2[0];
        int temp2 = number1[1] * number2[1];
        int temp3 = (number1[0] + number1[1]) * (number2[0] + number2[1]);
    
        int result = temp1 * pow(10, n) + (temp3 - temp2 - temp1) * pow(10, n / 2) + temp2;
        vector<int> multiplied;
        while (result > 0) {multiplied.push_back(result % 10); result /= 10;}
        reverse(multiplied.begin(), multiplied.end());
        normalizeNumber(multiplied, 4);
        return multiplied;
    }
}


int main() {
    int n, m;
    cout << "Enter lenghts of numbers" << endl;
    cin >> n >> m;
    vector<int> number1, number2;
    srand(time(0));
    for (auto i = 0; i < n; i++) {
        number1.push_back(rand() % 10);
    }
    for (auto j = 0; j < m; j++) {
        number2.push_back(rand() % 10);
    }
    printArray(number1, "");
    printArray(number2, "");
    cout << "----------------------------------------------------------" << endl;
    for (auto j : multiply(number1, number2)) {
        cout << j;
    }
    cout << " - умножение в столбик" << endl;
    normalizeNumber(number1, pow(2, ceil(log2(max(m, n)))));
    normalizeNumber(number2, pow(2, ceil(log2(max(m, n)))));
    vector<int> res = mult(number1, number2, (int)number1.size());
    for (auto j : res) {
        cout << j;
    }
    cout << " - Карабуца" << endl;
    return 0;
}