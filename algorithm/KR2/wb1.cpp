#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int main() {
    int number;
    cin >> number;
    vector<int> prime_numbers;
    for (int i = 2; i <= number; i++) {
        prime_numbers.push_back(i);
    }
    int tmp = 0;
    while (tmp < prime_numbers.size()) {
        int curr_num = prime_numbers[tmp];
        for (int j = tmp + 1; j < prime_numbers.size(); j++) {
            if ((prime_numbers[j] % curr_num == 0)) {
                prime_numbers.erase(prime_numbers.begin() + j);
            }
        }
        tmp++;
    }
}
