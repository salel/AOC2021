#include <iostream>
#include <vector>

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

    int sum = 0;

    for (unsigned i=0;i<plan.size();i++) {
        int pos_x = i%width;
        int pos_y = i/width;

        int val = plan[i];

        bool low_point = true;
        if (pos_x > 0 && plan[i-1] <= val) low_point = false;
        if (pos_x < width-1 && plan[i+1] <= val) low_point = false;
        if (pos_y > 0 && plan[i-width] <= val) low_point = false;
        if (pos_y < height-1 && plan[i+width] <= val) low_point = false;

        if (low_point) sum += 1+val;
    }
    cout << sum << endl;
}