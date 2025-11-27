#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int number;
    cin >> number;
    vector<int> prime_numbers;
    for (int i = 2; i <= number; i++) {
        prime_numbers.push_back(i);
    }
    // Решето Эратосфена
    //---------------------------------------------------------
    int ind = 0;
    while (ind < prime_numbers.size()) {
        int curr_num = prime_numbers[ind];
        for (int j = ind + 1; j < prime_numbers.size(); j++) {
            if ((prime_numbers[j] % curr_num == 0)) {
                prime_numbers.erase(prime_numbers.begin() + j);
            }
        }
        ind++;
    }
    //---------------------------------------------------------
    // Заполнение словаря простыми числами с их степенями
    //---------------------------------------------------------
    map<int, int> factors;
    for (auto prime : prime_numbers) {
        if (number % prime == 0) {
            while (number % prime == 0) {
                number = number / prime;
                factors[prime]++;
            }
        }
    }
    //---------------------------------------------------------
    for (auto [prime, counter] : factors) {
        cout << prime << "**" << counter << endl;
    }
}
