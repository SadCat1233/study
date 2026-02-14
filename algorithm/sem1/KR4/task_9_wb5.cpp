#include <iostream>
#include <string>

using namespace std;

void towerOfHanoi(int n, char start, char buffer, char destination) {
    if (n == 1) {
        cout << "Move disk 1 from " << start << " to " << destination << std::endl;
        return;
    }
    towerOfHanoi(n - 1, start, destination, buffer);
    cout << "Move disk " << n << " from " << start << " to " << destination << std::endl;
    towerOfHanoi(n - 1, buffer, start, destination);
}

int main() {
    int numDisks;
    cout << "Enter the number of disks: ";
    cin >> numDisks;
    towerOfHanoi(numDisks, 'A', 'B', 'C');
    return 0;
}
