#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

const int LINE_SIZE = 256;

int main() {
    char line[LINE_SIZE];
    cin.getline(line, LINE_SIZE);
    string molecule(line, strlen(line));
    if (molecule[molecule.size()-1] == '\r') molecule.pop_back();

    map<int, char> rules;
    cin.getline(line, LINE_SIZE);

    while (true) {
        cin.getline(line, LINE_SIZE);
        if (!cin) break;
        int id = ((((int)line[0])<<8) | line[1]);
        rules[id] = line[6];
    }

    int steps = 10;

    for (int i=0;i<steps;i++) {
        for (unsigned j=0;j<molecule.size()-1;j++) {
            int code = ((((int)molecule[j]) << 8) | molecule[j+1]);
            auto it = rules.find(code);
            if (it != rules.end()) {
                char to_insert = it->second;
                molecule.insert(j+1, 1, to_insert);
                j++;
            }
        }
    }

    map<char, int> occurences;
    for (auto c : molecule) {
        auto it = occurences.find(c);
        if (it == occurences.end()) occurences[c] = 1;
        else it->second++;
    }

    int max_occ = occurences.begin()->second;
    int min_occ = occurences.begin()->second;

    for (auto c : occurences) {
        max_occ = max(max_occ, c.second);
        min_occ = min(min_occ, c.second);
    }

    cout << max_occ - min_occ << endl;

}