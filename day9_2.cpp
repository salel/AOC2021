#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LINE_SIZE = 512;

int main() {
    int cursor = 0;
    vector<int> plan;
    int width = 0;
    int height = 0;

    while (true) {
        char c;
        cin.get(c);
        if (!cin) break;
        if (c == '\r') continue;
        else if (c == '\n') {
            if (width == 0) width = cursor;
            height++;
        } else {
            plan.push_back((c-'0'));
        }
        cursor++;
    }

    vector<int> low_points;

    auto neighbors = [=](int i) {
        vector<int> n;
        int pos_x = i%width;
        int pos_y = i/width;
        if (pos_x > 0) n.push_back(i-1);
        if (pos_x < width-1) n.push_back(i+1);
        if (pos_y > 0) n.push_back(i-width);
        if (pos_y < height-1) n.push_back(i+width);
        return n;
    };

    for (unsigned i=0;i<plan.size();i++) {
        int val = plan[i];

        bool low_point = true;
        for (auto n : neighbors(i)) {
            if (plan[n] <= val) low_point = false;
        }

        if (low_point) {
            low_points.push_back(i);
        }
    }

    vector<int> basin_sizes;

    for (auto p : low_points) {
        vector<int> states(plan.size(), 0); // 0 -> nothing; 1 -> to check; 2 -> to stage; 3 -> visited
        states[p] = 1;

        while (true) {
            bool remaining = false;
            for (unsigned i=0;i<states.size();i++) {
                if (states[i] == 1) {
                    remaining = true;
                    if (plan[i] != 9) {
                        for (auto n : neighbors(i)) {
                            if (states[n] == 0) states[n] = 2;
                        }
                    }
                    states[i] = 3;
                }
            }

            if (!remaining) break;
            for (unsigned i=0;i<states.size();i++) {
                if (states[i] == 2) states[i] = 1;
            }
        }
        int basin_size = 0;
        for (unsigned i=0;i<states.size();i++) {
            if (states[i] == 3 && plan[i] != 9) basin_size++;
        }
        basin_sizes.push_back(basin_size);
    }

    sort(basin_sizes.begin(), basin_sizes.end(), [](int a, int b) {return a > b; });

    cout << basin_sizes[0] * basin_sizes[1] * basin_sizes[2] << endl;

}