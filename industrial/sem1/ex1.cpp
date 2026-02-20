#include <iostream>

using namespace std;

int main() {
    int n, m, temp;
    int tmp[3] = {-1, 0, 1};
    cin >> n >> m;
    cin >> temp;
    char data[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            data[i][j] = '0';
        }
    }
    for (int i = 0; i < temp; i++) {
        int n_g, m_g;
        cin >> n_g >> m_g;
        data[n_g - 1][m_g - 1] = '*';
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (data[i][j] != '*') {
                for (int n_shift = 0; n_shift < 3; n_shift++) {
                    for (int m_shift = 0; m_shift < 3; m_shift++) {
                        if ((-1 < (i + tmp[n_shift])) && (-1 < (j + tmp[m_shift])) && ((i + tmp[n_shift]) < n) && ((j + tmp[m_shift]) < m)) {
                            if (data[i + tmp[n_shift]][j + tmp[m_shift]] == '*') {
                                data[i][j] += 1;
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << data[i][j];
        }
        cout << endl;
    }
    return 0;
}