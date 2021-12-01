#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> a;
    while (cin) {
        int b = 0;
        cin >> b;
        a.push_back(b);
    }

    int old_slide = a[0]+a[1]+a[2];
    int counter = 0;

    for (unsigned int c=3;c<a.size();c++) {
        int new_slide = old_slide + a[c] - a[c-3];
        if (new_slide > old_slide) counter++;
    }
    cout << counter << endl;
}