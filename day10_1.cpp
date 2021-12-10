#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

const int LINE_SIZE = 512;

int main() {
    char line[LINE_SIZE];
    int score = 0;
    while (true) {
        cin.getline(line, LINE_SIZE);
        if (!cin) {
            break;
        }
        stack<char> chunks;
        auto line_size = strlen(line);
        if (line[line_size-1] == '\r') line_size--;

        char corrupt_char = 0;
        bool corrupt = false;
        for (size_t i=0;i<line_size;i++) {
            char c = line[i];
            corrupt_char = c;
            if (c == '[' || c == '(' || c == '{' || c == '<') chunks.push(c);
            else {
                if (chunks.size() == 0) {
                    corrupt = true;
                    break;
                }
                char c2 = chunks.top();
                chunks.pop();
                if ((c2 == '[' && c != ']') ||
                    (c2 == '(' && c != ')') ||
                    (c2 == '{' && c != '}') ||
                    (c2 == '<' && c != '>')) {
                    corrupt = true;
                    break;
                }
            }
        }
        if (corrupt) {
            if (corrupt_char == ')') score += 3;
            if (corrupt_char == ']') score += 57;
            if (corrupt_char == '}') score += 1197;
            if (corrupt_char == '>') score += 25137;
        }
    }

    cout << score << endl;
}