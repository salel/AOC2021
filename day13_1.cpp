#include <iostream>
#include <set>
#include <cstring>
#include <string>
#include <vector>
#include <set>

using namespace std;

const int LINE_SIZE = 256;

int main() {
    set<pair<int, int>> dots;
    char line[LINE_SIZE];

    while (true) {
        cin.getline(line, LINE_SIZE);

        if (line[0] == '\r' || line[0] == '\0') break;
        int cursor = 0;
        while (line[cursor] != ',') cursor++;
        line[cursor] = '\0';

        int a = atoi(line);
        int b = atoi(line+cursor+1);
        dots.insert(make_pair(a, b));
    }

    
    cin.getline(line, LINE_SIZE);

    bool fold_dir = (line[11] == 'y');
    int fold_v = atoi(line+13);

    set<pair<int, int>> dots_fold_y;

    for (auto d : dots) {
        int x = d.first;
        int y = d.second;
        if (fold_dir) {
            if (y > fold_v) y = 2*fold_v - y;
        } else {
            if (x > fold_v) x = 2*fold_v - x;
        }
        dots_fold_y.insert(make_pair(x, y));
    }

    cout << dots_fold_y.size() << endl;
    
}