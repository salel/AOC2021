#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int main() {
    char line[32];

    vector<int> a;
    int b = 0;

    while (cin) {
        cin.getline(line, 32);
        if (a.size() == 0) {
            a.resize(strlen(line));
        }
        for (unsigned i=0;i<a.size();i++) {
            if (line[i] == '1') a[i]++;
        }

        b++;
    }

    int gamma = 0;
    for (unsigned i=0;i<a.size();i++) {
        if (a[i] > b/2) gamma += (1 << (a.size()-i-1));
    }

    int epsilon = (1 << a.size())-1-gamma;

    cout << gamma * epsilon << endl;
}