#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {

    vector<int> array;
    while (true) {
        char c;
        cin.get(c);
        if (!cin) break;
        if (c == '\r' || c == '\n') continue;
        else {
            array.push_back(c-'0');
        }
    }

    auto neighbors = [](int a) {
        vector<int> n;
        int pos_x = a%10;
        int pos_y = a/10;
        for (int i=pos_x-1;i<=pos_x+1;i++) {
            for (int j=pos_y-1;j<=pos_y+1;j++) {
                if (i==pos_x && j==pos_y) continue;
                if (i >= 0 && i < 10 && j >= 0 && j < 10) n.push_back(j*10+i);
            }
        }
        return n;
    };

    for (int s=1;;s++) {
        set<int> flashed;
        for (int i=0;i<(int)array.size();i++) {
            array[i]++;
            if ((array[i]%10) == 0) flashed.insert(i);
        }
        while (flashed.size() > 0) {
            set<int> next_flashed;
            vector<int> to_change;
            for (auto f : flashed) {
                for (auto n : neighbors(f)) {
                    if (array[n]%10 != 0) {
                        to_change.push_back(n);
                    }
                }
            }
            for (auto c : to_change) {
                if (array[c]%10 != 0) array[c]++;
                if (array[c]%10 == 0) {
                    next_flashed.insert(c);
                }
            }
            flashed = next_flashed;
        }

        bool all_flashed = true;
        for (auto c : array) {
            if (c%10 != 0) {
                all_flashed = false;
                break;
            }
        }
        if (all_flashed) {
            cout << s << endl;
            break;
        }
    }
}