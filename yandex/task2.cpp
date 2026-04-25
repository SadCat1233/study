#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, string> link;

string root(const string& v) {
    if (!isdigit(v[0]) && link.count(v))
        return root(link[v]);
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    for (int i = 0; i < n; i++) {
        if (!isdigit(a[i][0]) && !isdigit(b[i][0])) {
            string ra = root(a[i]), rb = root(b[i]);
            if (ra != rb)
                link[ra] = rb;
        }
    }

    unordered_map<string, int> val;
    for (int i = 0; i < n; i++) {
        string x = a[i], y = b[i];
        if (!isdigit(x[0]) && !isdigit(y[0])) continue;
        if (!isdigit(x[0])) swap(x, y);

        string rv = root(y);
        int v = stoi(x);

        if (isdigit(rv[0]) && stoi(rv) != v) {
            cout << "NO\n";
            return 0;
        }
        if (!isdigit(rv[0]) && val.count(rv) && val[rv] != v) {
            cout << "NO\n";
            return 0;
        }
        val[rv] = v;
    }

    cout << "YES\n";
}