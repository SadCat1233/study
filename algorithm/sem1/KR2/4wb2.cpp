#include <iostream>
#include <vector>
typedef unsigned long long int ull;

using namespace std;

//Заданная функция
ull s(ull number) {
    ull m = pow(2, number) - 1;
    ull S = 4;
    for(int i = 0; i < number - 2; i++){
        S = (S * S - (ull)2) % m;
    }
    return S == 0;
}


int main() {
    int mersen_number;
    cin >> mersen_number;
    vector<int> prime_numbers;
    for (int i = 2; i <= mersen_number; i++) {
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
    // Проверка тестом Люка-Лемера
    //---------------------------------------------------------
    ull mersen = pow(2, mersen_number) - 1;
    cout << mersen << endl;
    if (prime_numbers[prime_numbers.size() - 1] == mersen_number) {
        if (s(mersen_number)) {
            cout << "Простое" << endl;
        } 
        else {
            cout << "Не простое" << endl;
        }
    }
    else {
        cout << "Не простое" << endl;
    }
    return 0;
    //---------------------------------------------------------
}
