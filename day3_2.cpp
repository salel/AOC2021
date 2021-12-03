#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

int get(vector<string> lines, bool cmp) {
    vector<string> b1(lines);
    for (unsigned i=0;i<lines[0].length();i++) { 
        vector<string> b2,b3;
        for (auto s : b1) {
            if (s[i] == '1') b2.push_back(s);
            else b3.push_back(s);

        }
        if ((cmp && b2.size() >= b3.size())
            || (!cmp && b2.size() < b3.size())) {
            b1 = b2;
        } else {
            b1 = b3;
        }
        if (b1.size() == 1) break;
    }
    string d = b1[0];
    int value = 0;
    for (unsigned i=0;i<d.length();i++) {
        if (d[i] == '1') value += (1 << (d.length()-i-1));
    }
    return value;
}

int main() {
    char line[32];
    vector<string> lines;

    while (cin) {
        cin.getline(line, 32);
        if (line[0] != '0' && line[0] != '1') break;
        lines.emplace_back(line, strlen(line));
    }

    int oxy = get(lines, true);
    int co2 = get(lines, false);


    cout << oxy * co2 << endl;
}