#include <iostream>
#include <map>
#include <vector>

using namespace std;

const int LINE_SIZE = 512;

int main() {
    int counter = 0;

    while (cin) {

        // Read first numbers, extract bit representation
        char line[LINE_SIZE];
        cin.getline(line, LINE_SIZE);
        if (!cin) break;

        vector<int> bit_rep; 

        int cursor = 0;
        int c_bit_rep = 0;
        while (true) {
            char c = line[cursor];
            if (c == ' ' || c == '|') {
                if (c == '|') break;
                bit_rep.push_back(c_bit_rep);
                c_bit_rep = 0;
            } else {
                c_bit_rep = c_bit_rep | (1 << (c-'a'));
            }
            cursor ++;
        }
        int bit_rep_4;
        int bit_rep_1;
        int bit_rep_7;
        vector<int> segment_5;
        vector<int> segment_6;

        auto count_bits = [](int n) {
            int a = 0;
            for (int i=1;i<=0b1111111;i=(i<<1)) {
                if (n&i) a++;
            }
            return a;
        };

        // extract to respective groups
        for (auto a : bit_rep) {
            int c = count_bits(a);
            if (c == 2) bit_rep_1 = a;
            else if (c == 3) bit_rep_7 = a;
            else if (c == 4) bit_rep_4 = a;
            else if (c == 5) segment_5.push_back(a);
            else if (c == 6) segment_6.push_back(a);
        }

        map<int, int> bit_rep_to_number = {{0b1111111, 8}, {bit_rep_4, 4}, {bit_rep_1, 1}, {bit_rep_7, 7}};
        for (auto a : segment_5) {
            if ((a & bit_rep_1) == bit_rep_1) bit_rep_to_number[a] = 3;
            else if (count_bits(a & bit_rep_4) == 2) bit_rep_to_number[a] = 2;
            else bit_rep_to_number[a] = 5; 
        }
        for (auto a : segment_6) {
            if ((a & bit_rep_1) == bit_rep_1) {
                if ((a & bit_rep_4) == bit_rep_4) bit_rep_to_number[a] = 9;
                else bit_rep_to_number[a] = 0;
            } else bit_rep_to_number[a] = 6; 
        }

        cursor+=2;
        c_bit_rep = 0;
        int mul = 1000;
        int number = 0;
        while (true) {
            char c = line[cursor];
            if (c == ' ' || c == '\0' || c == '\r') {
                number += bit_rep_to_number[c_bit_rep]*mul;
                c_bit_rep = 0;
                mul /= 10;
                if (c == '\0') break;
            } else {
                c_bit_rep = c_bit_rep | (1 << (c-'a'));
            }
            cursor++;
        }
        counter += number;
    }

    cout << counter << endl;


}