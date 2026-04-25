#include <iostream>
#include <cmath>

using namespace std;

class Triangle {
public:
    double a, b, c;

    Triangle(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
        if (!exst_tr()) {
            this->a = 3;
            this->b = 4;
            this->c = 5;
        }
    }

    bool exst_tr() {
        return (a + b > c) && (a + c > b) && (b + c > a);
    }

    void show() {
        cout << "A = " << a << ", B = " << b << ", C = " << c << endl;
    }

    double perimetr() {
        return a + b + c;
    }

    double square() {
        double p = perimetr() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    bool is_similar(Triangle &t2) {
        double k1 = a / t2.a;
        double k2 = b / t2.b;
        double k3 = c / t2.c;
        return (k1 == k2) && (k2 == k3);
    }

    double get_a() { return a; }
    double get_b() { return b; }
    double get_c() { return c; }
};

class Circle {
public:
    float r;
    float x;
    float y;

    Circle(float r, float x, float y) {
        this->r = r;
        this->x = x;
        this->y = y;
    }

    void set_circle(float r, float x, float y) {
        this->r = r;
        this->x = x;
        this->y = y;
    }

    float square() {
        return 3.14 * r * r;
    }

    bool triangle_around(Triangle &t) {
        double a = t.get_a();
        double b = t.get_b();
        double c = t.get_c();
        double S = t.square();
        if (S == 0) return false;

        double R = (a * b * c) / (4 * S);
        return R == r;
    }

    bool triangle_in(Triangle &t) {
        double S = t.square();
        double p = t.perimetr() / 2;
        if (p == 0) return false;

        double r_in = S / p;
        return r_in == r;
    }

    bool check_circle(Circle &c) {
        float dx = x - c.x;
        float dy = y - c.y;
        float distance = sqrt(dx * dx + dy * dy);

        return distance <= (r + c.r) && distance >= fabs(r - c.r);
    }
};

#include "main1_4.cpp"
