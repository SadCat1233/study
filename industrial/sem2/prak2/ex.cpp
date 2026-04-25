#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;


class Triangle {
    public:
        double a, b, c;

        Triangle(double first, double second, double third) {
            a = first;
            b = second;
            c = third;
            if (!exst_tr()) {
                a = 3;
                b = 4;
                c = 5;
            }
        }

        bool is_similar(Triangle& t2) {
            return ((t2.a / a) == (t2.b / b) && (t2.b / b) == (t2.c / c));
        }

        bool exst_tr() {
            return ((a + b) > c && (a + c) > b && (b + c) > a);
        }

        void show() {
            cout << "A = " << a << ", B = " << b << ", C = " << c << endl;
        }

        double perimetr() const {
            return a + b + c;
        }

        double square() const {
            double halfPerimetr = perimetr() / 2;
            return pow(halfPerimetr * (halfPerimetr - a) * (halfPerimetr - b) * (halfPerimetr - c), 0.5);
        }

        double get_a() {
            return a;
        }

        double get_b() {
            return b;
        }

        double get_c() {
            return c;
        }
};


class Circle {
    public:
        float r;
        float x, y;

        Circle(float r1, int x1, int y1) {
            r = r1;
            x = x1;
            y = y1;       
        };

        void set_circle(float r1, int x1, int y1) {
            r = r1;
            x = x1;
            y = y1;
        }

        float square() {
            return M_PI * r * r;
        }

        bool triangle_around(Triangle& t) {
            double triangleSquare = t.square();
            return ((t.a * t.b * t.c) / 4 * triangleSquare) == r;
        }

        bool triangle_in(Triangle& t) {
            return r == (t.square() / (t.perimetr() / 2));
        }

        bool check_circle(Circle& c1) {
            return pow(pow(abs(x - c1.x), 2) + pow(abs(y - c1.y), 2), 0.5) <= (r + c1.r);
        }
};


int main() {
    Triangle tr = Triangle(3, 4, 5);
    Circle c1 = Circle(0.5, 0, 0);
    Circle c2 = Circle(3, 0, 7);
    cout << tr.square() / tr.perimetr() << endl;
    cout << c1.triangle_in(tr) << endl;
    return 0;
}


// #include "main1_4.cpp"