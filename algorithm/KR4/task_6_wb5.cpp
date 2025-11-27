#include <iostream>
#include <cmath>

using namespace std;
bool FLAG = true;

double f(double x) {
    double y = pow(exp(1), x - 1) - pow(x, 3) - x;
    return FLAG ? y : -y;
}


double solve(double left, double right, double mid) {
    if (right - left < 0.0001) {
        return mid;
    }
    mid = (right + left) / 2;
    if (f(left) * f(mid) < 0) {
        return solve(left, mid, mid);
    }
    return solve(mid, right, mid);
}


int main() {
    double left = 0, right = 2, mid = 0;
    if (f(left) > f(right)) {
        FLAG = false;
    }
    cout << solve(left, right, mid) << endl;
    return 0;
}