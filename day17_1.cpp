#include <iostream>
#include <vector>

using namespace std;

int main() {
    int x0,x1,y0,y1;

    cin.ignore(15);
    cin >> x0;
    cin.ignore(2);
    cin >> x1;
    cin.ignore(4);
    cin >> y0;
    cin.ignore(2);
    cin >> y1;

    cout << ((-y0)*(-y0-1))/2 << endl;
}