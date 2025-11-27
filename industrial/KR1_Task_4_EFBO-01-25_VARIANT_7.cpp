#include <iostream>

using namespace std;

int main() {
    double a; double b; double c;
    cout << "Введите коэффицент a: ";
    cin >> a;

    cout << "Введите коэффицент b: ";
    cin >> b;

    cout << "Введите коэффицент c: ";
    cin >> c;

    cout << "Введите символ: ";
    char s;
    cin >> s;

    if (s == 'G') {
        cout << "Gamaev Pavel" << endl;
    }
    else if (s == 't') {
        int x;
        cout << "Введите число: ";
        cin >> x;
        if (x % 5 == 0) {
            cout << "Делится на 5" << endl;
        }
        else {
            cout << "Не делится на 5" << endl;
        }
    }
    else if (s == 'n') {
        if (a == 0 && b == 0 && c == 0) {
            cout << "Корень — любое действительное число." << endl;
        }
        else if (a == 0 && b == 0) {
            cout << "Уравнение не имеет решений." << endl;
        }
        else if (a == 0) {
            cout << "Линейное уравнение, корень x = " << -c / b << endl;
        }
        else {
            double d = b * b - 4 * a * c;
            if (d > 0) {
                double x1 = (-b + pow(d, 0.5)) / (2 * a);
                double x2 = (-b - pow(d, 0.5)) / (2 * a);
                cout << "Два корня: x1 = " << x1 << ", x2 = " << x2 << endl;
            } else if (d == 0) {
                double x = -b / (2 * a);
                cout << "Один корень: x = " << x << endl;
            } else {
                cout << "Действительных корней нет." << endl;
            }
        }
    }
    return 0;
}