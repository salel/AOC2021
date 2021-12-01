#include <iostream>

using namespace std;

int main() {
    int counter = 0;
    int val = 10000000;
    while (cin) {
        int nval = 0;
        cin >> nval;
        if (nval > val) counter++;
        val = nval;
    }
    cout << counter << endl;
}