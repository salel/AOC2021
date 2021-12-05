#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

struct point {
    int x,y;
};

bool operator<(const point p1, const point p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
}

int main() {
    map<point, int> overlap;

    while (cin) {
        point p1,p2;
        cin >> p1.x;
        if (!cin) break;
        cin.ignore(1);
        cin >> p1.y;
        cin.ignore(4);
        cin >> p2.x;
        cin.ignore(1);
        cin >> p2.y;

        auto update = [&](point p) {
            auto it = overlap.find(p);
            if (it == overlap.end()) overlap.insert(make_pair(p, 1));
            else it->second++;
        };
        if (p1.x == p2.x) {
            for (int y=min(p1.y,p2.y);y<=max(p1.y,p2.y);y++) {
                update({p1.x, y});
                
            }
        } else if (p1.y == p2.y) {
            for (int x=min(p1.x,p2.x);x<=max(p1.x,p2.x);x++) {
                update({x, p1.y});
            }
        }
    }

    cout << count_if(overlap.cbegin(), overlap.cend(), [](auto v) {
        return v.second >= 2;
    }) << endl;
}