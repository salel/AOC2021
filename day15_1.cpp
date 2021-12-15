#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

vector<int> neighbors(int width, int height, int c) {
    int pos_x = c%width;
    int pos_y = c/width;

    vector<int> n;
    if (pos_x > 0) n.push_back(c-1); 
    if (pos_x < width-1) n.push_back(c+1);
    if (pos_y > 0) n.push_back(c-width); 
    if (pos_y < height-1) n.push_back(c+width);
    return n; 
}

int main() {
    int width = 0;
    int height = 0;
    vector<int> risk;
    int cursor = 0;
    while(true) {
        int c = cin.get();
        if (!cin) break;
        if (c == '\r') continue;
        if (c == '\n') {
            if (width == 0) width = cursor;
            continue;
        }
        risk.push_back(c-'0');
        cursor++;
    }

    height = ((int)risk.size())/width;

    vector<int> distances(risk.size(), 9999999);
    distances[0] = 0;
    int next_check = 0;
    vector<int> visited(risk.size(), false);

    while (next_check != -1) {
        visited[next_check] = true;
        for (auto n : neighbors(width, height, next_check)) {
            int new_cost = distances[next_check] + risk[n];
            distances[n] = min(distances[n], new_cost);
        }
        // next cell to check
        int min_dist = 9999999;
        int min_cell = -1;
        for (int i=0;i<distances.size();i++) {
            if (!visited[i] && (distances[i] < min_dist)) {
                min_cell = i;
                min_dist = distances[i];
            }
        }
        next_check = min_cell;
    }

    cout << distances[width*height-1] << endl;
    
    
}