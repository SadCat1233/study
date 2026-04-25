#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Base {
public:
    virtual string name() const {
        return "Base";
    }
    virtual ~Base() = default;
};

class Derived1 : public Base {
public:
    string name() const override {
        return "Derived1";
    }
};

class Derived2 : public Base {
public:
    string name() const override {
        return "Derived2";
    }
};

void process(shared_ptr<Base> ptr) {
    cout << ptr->name() << "\n";

    auto d1 = dynamic_pointer_cast<Derived1>(ptr);
    if (d1) {
        cout << "Is Derived1\n";
    }

    auto d2 = static_pointer_cast<Derived2>(ptr);
    cout << "Static cast to Derived2\n";
}

template<typename T>
shared_ptr<T> smartCast(shared_ptr<Base> ptr) {
    return dynamic_pointer_cast<T>(ptr);
}