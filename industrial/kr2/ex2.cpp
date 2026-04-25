#include <iostream>
#include <memory>

using namespace std;

class Tracker{
    public:
        int id;
        Tracker() : id(0) {
            cout << "Default: " << id << endl;
        }
        Tracker(int i) : id(i) {
            cout << "Param: " << id << endl;
        }
        Tracker(Tracker& i) : id(i.id) {
            cout << "Copy: from " << i.id << " to " << id << endl;
        }
        Tracker(Tracker&& i) noexcept : id(i.id) {
            cout << "Move: from" << i.id << " to " << id << endl;
        }
        Tracker(double d) : Tracker(static_cast<int>(d)) {}

        explicit Tracker(const string& str) : id(0) {
            cout << "String: " << str << endl;
        }
        ~Tracker() {
            cout << "Destroy: " << id << endl;
        }
};