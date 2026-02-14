#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void addElement(unordered_map<int, int>& data1, unordered_map<int, int>& data2, vector<int>& answer, int number) {
    if (data1[number] != 0 && data2[number] != 0) {
        answer.push_back(number);
        data1[number]--;
        data2[number]--;
    }
}


vector<int> hashFunc(int array1[], int array2[], int n) {
    unordered_map<int, int> data1;
    unordered_map<int, int> data2;
    vector<int> answer;
    for (int i = 0; i < n; i++) {
        data1[array1[i]]++;
        data2[array2[i]]++;
        addElement(data1, data2, answer, array1[i]);
        addElement(data1, data2, answer, array2[i]);
    }
    return answer;
}


int main() {
    int n;
    cin >> n;
    int array1[n], array2[n];
    for (int i = 0; i < n; i++) {
        cin >> array1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> array2[i];
    }
    for (auto i : hashFunc(array1, array2, n)) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}