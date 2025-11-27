#include <iostream>
#include <string>

using namespace std;

int main() {
    string message, newMessage;
    size_t pos = 0;
    int maxLength = 0;
    getline(cin, message);
    message = message + " ";
    while ((pos = message.find(" ")) != string::npos) {
        string temp = message.substr(0, pos);
        if (maxLength < (int)temp.size()) {
            maxLength = (int)temp.size();
            newMessage = temp;
        }
        message.erase(0, pos + 1);
    }
    cout << newMessage << endl;
    return 0;
}