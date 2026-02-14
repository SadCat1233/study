#include <iostream>
#include <vector>

using namespace std;


void normalize(vector<int>& num1, vector<int>& num2, int n, int m) {
    if (n > m) {
        for (auto i = 0; i < (n - m); i++) {
            num2.push_back(0);
        }
    }
    else {
        for (auto i = 0; i < (m - n); i++) {
            num1.push_back(0);
        }
    }
}


int transfer_sum(vector<int>& transfers) {
    int sum = 0;
    for (auto i = 1; i < (transfers.size() - 1); i++) {
        sum += transfers[i];
    }
    return sum;
}


vector<int> fast_add(vector<int>& num1, vector<int>& num2) {
    vector<int> temp_sum, transfers;
    transfers = {0};
    bool first = true;
    while ((transfer_sum(transfers) != 0) || first) {
        transfers = {0};
        temp_sum = {};
        first = false;
        for (auto i = 0; i < num1.size(); i++) {
            if ((num1[i] + num2[i]) % 10 == 0) {
                temp_sum.push_back(0);
            }
            else {
                temp_sum.push_back((num1[i] + num2[i]) % 10);
            }
            if ((num1[i] + num2[i]) >= 10) {
                transfers.push_back(1);
            }
            else {
                transfers.push_back(0);
            }
        }
        num1 = temp_sum;
        num2 = transfers;
        normalize(num1, num2, (int)num1.size(), (int)num2.size());
    }
    reverse(temp_sum.begin(), temp_sum.end());
    int ind = 0;
    while (temp_sum[ind] == 0) {
        temp_sum.erase(temp_sum.begin());
    }
    return temp_sum;
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

    reverse(number1.begin(), number1.end());
    reverse(number2.begin(), number2.end());

    normalize(number1, number2, n, m);

    for (auto i : fast_add(number1, number2)) {
        cout << i;
    }
    cout << " - result" << endl;
    return 0;
}