#include <iostream>
#include <vector>
#include <cmath>
#include <map>
typedef unsigned long long int ull;

using namespace std;
// Функция создания вектора с простыми числами до n решетом Эрафтосфена
// Число i простое, если is_prime[i] == true
vector<bool> resheto(ull n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// Функция разложения числа n алгоритмом Ферма на 2 множителя
pair<ull, ull> ferma(ull n) {
    ull factor1 = ceil(sqrt(n));
    ull squared_factor2 = factor1 * factor1 - n;
    while (sqrt(squared_factor2) != (ull)sqrt(squared_factor2)) {
        factor1++;
        squared_factor2 = factor1 * factor1 - n;
    }
    ull factor2 = sqrt(squared_factor2);
    return {factor1 - factor2, factor1 + factor2};
}

// Рекурсивная функция раскладывающая число n на множители алгоритмом Ферма и записывающая все в словарь
void factorize(ull n, const vector<bool> &prime_numbers, map<ull, int> &factors) {
    if (n <= 1) {
        return;
    }
    if (prime_numbers[n]) {
        factors[n]++;
        return;
    }
    auto [a, b] = ferma(n);

    factorize(a, prime_numbers, factors);
    factorize(b, prime_numbers, factors);
}

int main() {
    ull number;
    cin >> number;
    if (((number - 2) % 4 == 0) || (number < 3)) {
        cout << "Wrong number" << endl;
        return 0;
    }
    vector<bool> prime_numbers = resheto(number);
    map<ull, int> factors;
    
    factorize(number, prime_numbers, factors);

    for (auto [prime, count] : factors) {
        cout << prime << "**" << count << endl;
    }
}
