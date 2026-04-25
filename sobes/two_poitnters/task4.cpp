#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isPalindrome(string text) {
    int leftPtr = 0, rightPtr = text.size() - 1;
    while (leftPtr < rightPtr) {
        if (!isalnum(text[leftPtr])) {
            leftPtr++;
            continue;
        }
        if (!isalnum(text[rightPtr])) {
            rightPtr--;
            continue;
        }
        if (tolower(text[leftPtr]) != tolower(text[rightPtr])) {
            cout << text[leftPtr] << " " << text[rightPtr] << endl;
            return false;
        }
        leftPtr++;
        rightPtr--;
    }
    return true;
}


int main() {
    string s = "A man, a plan, a canal: Panama"; 
    isPalindrome(s);
    return 0;
}