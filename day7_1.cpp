#include <iostream>
#include <vector>
#include <numeric>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    vector<int> pos;

    while (cin) {
        int p;
        cin >> p;
        if (!cin) break;
        pos.push_back(p); 
        cin.ignore(1);
    }

    auto minmaxPos = minmax_element(pos.cbegin(), pos.cend());

    int fuel_min = 1000000000;
    for (int i=*minmaxPos.first;i<=*minmaxPos.second;i++) {
        int fuel = 0;
        for (auto p : pos) {
            fuel += abs(p-i);
        }
        fuel_min = min(fuel, fuel_min);
    }

    cout << fuel_min << endl;

}