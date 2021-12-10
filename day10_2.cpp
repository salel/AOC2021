#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>

using namespace std;

const int LINE_SIZE = 512;

int main() {
    char line[LINE_SIZE];
    vector<long> scores;
    while (true) {
        cin.getline(line, LINE_SIZE);
        if (!cin) {
            break;
        }
        stack<char> chunks;
        auto line_size = strlen(line);
        if (line[line_size-1] == '\r') line_size--;

        bool corrupt = false;
        for (size_t i=0;i<line_size;i++) {
            char c = line[i];
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
        if (!corrupt) {
            long local_score = 0;
            while (chunks.size() > 0) {
                char c = chunks.top();
                chunks.pop();
                local_score *= 5;
                if (c == '(') local_score += 1;
                else if (c == '[') local_score += 2;
                else if (c == '{') local_score += 3;
                else if (c == '<') local_score += 4;
            }
            scores.push_back(local_score);
        }
    }

    sort(scores.begin(), scores.end());

    cout << scores[scores.size()/2] << endl;
}