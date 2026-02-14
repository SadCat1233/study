#include <iostream>
#include <string>

using namespace std;

int main() {
    string message, newMessage;
    getline(cin, message);
    size_t pos = 0;
    while ((pos = message.find(" ")) != string::npos) {
        string temp = message.substr(0, pos);

        newMessage = temp + " " + newMessage;
        message.erase(0, pos + 1);
    }
    newMessage = message + " " + newMessage;
    newMessage.erase(newMessage.end() - 1);
    cout << newMessage << endl;
    return 0;
}