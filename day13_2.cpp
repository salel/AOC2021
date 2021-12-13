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

    int max_x = 100000;
    int max_y = 100000;
    
    while (true) {
        cin.getline(line, LINE_SIZE);
        if (!cin) break;

        bool fold_dir = (line[11] == 'y');
        int fold_v = atoi(line+13);

        set<pair<int, int>> dots_fold;

        for (auto d : dots) {
            int x = d.first;
            int y = d.second;
            if (fold_dir) {
                if (y > fold_v) y = 2*fold_v - y;
                max_y = min(max_y, fold_v);
            } else {
                if (x > fold_v) x = 2*fold_v - x;
                max_x = min(max_x, fold_v);
            }
            dots_fold.insert(make_pair(x, y));
        }
        dots = dots_fold;
    }

    // to bitmap
    vector<vector<bool>> bmap;
    bmap.resize(max_y);

    for (auto &a : bmap) a.resize(max_x, false);

    for (auto d : dots) {
        bmap[d.second][d.first] = true;
    }

    for (auto a : bmap) {
        for (auto b : a) {
            if (b) cout << "#";
            else cout << ".";
        }
        cout << endl;
    }
    
}