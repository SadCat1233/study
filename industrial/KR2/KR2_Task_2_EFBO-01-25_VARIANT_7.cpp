//Group: EFBO-01-25
//Student: Gamaev Pavel

#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    int **matrix;
    matrix = new int *[n];
    for (int j = 0; j < m; j++) {
        matrix[j] = new int[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = rand() % 100 - rand() % 100;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j > i) {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}