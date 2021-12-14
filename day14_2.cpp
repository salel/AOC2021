#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

const int LINE_SIZE = 256;

template<typename T>
void add_occurence(map<T, long>& occ, T c, long count = 1) {
    auto it = occ.find(c);
    if (it == occ.end()) occ[c] = count;
    else it->second += count;
}

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

    map<char, long> occurences;
    for (auto c : molecule) add_occurence(occurences, c);

    map<int, long> pair_occurences;

    for (unsigned i=0;i<molecule.size()-1;i++) {
        int code = ((((int)molecule[i])<<8) | molecule[i+1]);
        add_occurence(pair_occurences, code);
    }

    int steps = 40;

    for (int i=0;i<steps;i++) {
        map<int, long> new_pair_occurences;

        for (auto c : pair_occurences) {
            auto code = c.first;
            auto number = c.second;
            auto rule = rules.find(code);
            if (rule == rules.end()) {
                add_occurence(new_pair_occurences, code, number);
            } else {
                char to_insert = rule->second;
                add_occurence(occurences, to_insert, number);
                int code1 = ((code&0xFF00) | to_insert);
                int code2 = ((to_insert << 8) | (code&0xFF));
                add_occurence(new_pair_occurences, code1, number);
                add_occurence(new_pair_occurences, code2, number);
            }
        }
        pair_occurences = new_pair_occurences;

    }

    long max_occ = occurences.begin()->second;
    long min_occ = occurences.begin()->second;

    for (auto c : occurences) {
        max_occ = max(max_occ, c.second);
        min_occ = min(min_occ, c.second);
    }

    cout << max_occ - min_occ << endl;

}