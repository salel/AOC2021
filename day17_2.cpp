#include <iostream>
#include <vector>

using namespace std;

int main() {
    int x0,x1,y0,y1;

    cin.ignore(15);
    cin >> x0;
    cin.ignore(2);
    cin >> x1;
    cin.ignore(4);
    cin >> y0;
    cin.ignore(2);
    cin >> y1;

    int min_vel_x = 0;
    int acc = 0;
    while (acc < x0) {
        min_vel_x++;
        acc += min_vel_x;
    }

    auto sim = [&](int vx, int vy) {
        int x = 0;
        int y = 0;
        while (true) {
            if (x >= x0 && x <= x1 && y >= y0 && y <= y1) {
                return true;
            } else if (x > x1 || y < y0) {
                return false;
            }
            x += vx;
            y += vy;
            vy--;
            if (vx > 0) vx--;
        }
    };

    int distinct_count = 0;

    for (int y=y0;y<=-y0-1;y++) {
        for (int x=min_vel_x;x<=x1;x++) {
            if (sim(x,y)) distinct_count++;
        }
    }

    cout << distinct_count << endl;
}
