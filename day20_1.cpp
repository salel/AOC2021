#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

vector<bool> apply_algo(vector<bool> algo, vector<bool> img, bool border = false) {

    int width = (int)sqrt(img.size());
    int offset = 1;
    int nwidth = width+offset*2;

    vector<bool> large_img(nwidth*nwidth, border);

    for (int i=0;i<width;i++) {
        for (int j=0;j<width;j++) {
            large_img[(i+offset)*nwidth+j+offset] = img[i*width+j];
        }
    }

    vector<bool> new_img(nwidth*nwidth);

    for (int i=0;i<nwidth;i++) {
        for (int j=0;j<nwidth;j++) {
            int code = 0;
            for (int k=0;k<9;k++) {
                int i0 = i+k/3-1;
                int j0 = j+k%3-1;

                bool val = border;
                if (i0 >= 0 && i0 < nwidth && j0 >= 0 && j0 < nwidth) val = large_img[i0*nwidth+j0];

                code = code | ((int)(val) << (8-k));
            }

            new_img[i*nwidth+j] = algo[code];
        }
    }

    return new_img;

}

int main() {

    vector<bool> algo;

    while (true) {
        auto c = cin.get();
        if (c == '\r') continue;
        else if (c == '\n') break;
        else {
            algo.push_back(c=='#');
        }
    }

    vector<bool> img;

    while (true) {
        auto c = cin.get();
        if (!cin) break;
        if (c == '.') img.push_back(false);
        else if (c == '#') img.push_back(true);
    }

    bool border = false;
    for (int i=0;i<2;i++) {
        img = apply_algo(algo, img, border);
        border = algo[border?511:0];
    }

    int size = (int)sqrt(img.size());

    cout << count(img.begin(), img.end(), true) << endl;

    for (int i=0;i<size;i++) {
        for (int j=0;j<size;j++) {
            cout << (img[i*size+j]?'#':'.');
        }
        cout << endl;
    }
}