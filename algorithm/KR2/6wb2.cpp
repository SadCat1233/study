#include <iostream>
#include <vector>

using namespace std;

int main() {
    int number;
    cin >> number;
    int length = (number - 1) / 2;
    int numbers[length];
    for (int i = 1; i <= length; i++) {
        numbers[i - 1] = i;
    }
    for (int i = 1; i <= length; i++) {
        for (int j = i; j <= length; j++) {
            if ((i + j + 2 * i * j) <= length) {
                numbers[i + j + 2 * i * j - 1] = 0;
            }
        }
    }
    vector<int> prime_numbers;
    for (auto number : numbers) {
        if (number != 0) {
            prime_numbers.push_back(number * 2 + 1);
        }
    }
    for (auto prime : prime_numbers) {
        cout << prime << " ";
    }
    cout << endl;
    return 0;
}
