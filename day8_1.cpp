#include <iostream>

using namespace std;

const int LINE_SIZE = 512;

int main() {
    int counter = 0;

    while (cin) {
        char line[LINE_SIZE];
        cin.getline(line, LINE_SIZE);
        if (!cin) break;
        int cursor = 0;
        while (line[cursor] != '|') cursor++;
        cursor++;
        int digit_size = 0;
        while (true) {
            char c = line[cursor];
            if (c == ' ' || c == '\0' || c == '\r') {
                if (digit_size == 2 || digit_size == 4 || digit_size == 3 || digit_size == 7) counter++;
                digit_size = 0;
                if (c == '\0') break;
            } else {
                digit_size++;
            }
            cursor++;
        }
    }

    cout << counter << endl;


}