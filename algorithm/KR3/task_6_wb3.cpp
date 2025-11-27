#include <iostream>
typedef unsigned long long int ull;

using namespace std;


ull bin_search(ull number, ull divider) {
    ull left = 1;
    ull right = number;
    ull mid;
    while (right >= left) {
        mid = (right + left) / (ull)2;
        if ((mid * divider) > number) {
            right = mid - (ull)1;
        }
        else if ((mid * divider) < number) {
            left = mid + (ull)1;
        }
        else {
            return mid;
        }
    }
    return left - (ull)1;
}


int main() {
    ull number, divider;
    cout << "Enter number" << endl;
    cin >> number;
    cout << "Enter divider" << endl;
    cin >> divider;
    cout << number << " = " << bin_search(number, divider) << "*" << divider << "+" << number - (bin_search(number, divider) * divider) << endl;
    return 0;
}