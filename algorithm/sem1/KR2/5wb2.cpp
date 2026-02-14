#include <iostream>
#include <string>
#include <cstdint>
typedef unsigned long long int ull;

using namespace std;

int main() {
    ull number;
    cin >> number;
    for (int i = 0; i < 10; ++i) {
        ull squared = number * number;
        string squared_string = to_string(squared);
        // Дополнение строки ведущими нулями, чтобы длина была нечетной
        //---------------------------------------------------------
        if (squared_string.size() % 2 == 0) {
            squared_string = "0" + squared_string;
        }
        //---------------------------------------------------------
        // Дополнение до строки длиной 5
        //---------------------------------------------------------
        if (squared_string.size() < 5) {
            while (squared_string.size() != 5) {
                squared_string = "0" + squared_string;
            }
        }
        //---------------------------------------------------------
        // Получение нового числа
        //---------------------------------------------------------
        size_t start = (squared_string.size() - 5) / 2;
        string mid5 = squared_string.substr(start, 5);

        ull new_number = 0;
        for (char c : mid5) {
            new_number = new_number * 10 + (c - '0');
        }
        cout << "Squared number: " << squared << " Pseudorandom number: " << new_number << endl;
        number = new_number;
        //---------------------------------------------------------
    }
    return 0;
}
