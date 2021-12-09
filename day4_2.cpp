#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


struct bingocard {
    vector<int> grid;
    vector<bool> strike;

    bingocard(vector<int> g){
        this->grid = g;
        strike = vector<bool>(25,false);
    }

    int update(int num) {
        for (int i=0;i<25;i++) {
            if (grid[i] == num) {
                strike[i] = true;

                bool won_hori = true;
                bool won_vert = true;
                for (int j=0;j<5;j++) {
                    if (!strike[j*5+(i%5)]) won_hori = false;
                    if (!strike[(i/5)*5 + j]) won_vert = false;
                }

                if (!won_hori && !won_vert) return -1;

                int score = 0;
                for (int j=0;j<25;j++) {
                    if (!strike[j]) score += grid[j];
                }
                return score*num;
            }
        }
        return -1;
    }

};

const int GAME_SIZE = 1024;

int main() {
    char game[GAME_SIZE];
    cin.getline(game, GAME_SIZE);
    stringstream ss(string(game, strlen(game)));

    vector<int> game_num;

    while (ss) {
        int a;
        ss >> a;
        game_num.push_back(a);
        ss.ignore(1);
    }

    vector<bingocard> cards;

    while (cin) {
        vector<int> grid;
        for (int i=0;i<25;i++) {
            int num;
            cin >> num;
            if (!cin) break;
            grid.push_back(num);
        }
        if (grid.size() == 25) cards.emplace_back(grid);
    }

    for (auto num : game_num) {
        vector<bingocard> remaining;

        int won_score = 0;
        for (auto& c : cards) {
            int a = c.update(num);
            if (a == -1) remaining.push_back(c);
            else won_score = a;
        }
        if (remaining.size() == 0) {
            cout << won_score << endl;
            return 0;
        }
        cards = remaining;
    }

}