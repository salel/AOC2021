#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> ages;
    while (cin) {
        int age;
        cin >> age;
        if (cin) ages.push_back(age);
        cin.ignore(1);
    }

    int gens = 80;

    for (int i=0;i<gens;i++) {
        vector<int> new_ages;
        for (auto a : ages) {
            if (a == 0) {
                new_ages.push_back(6);
                new_ages.push_back(8);
            } else {
                new_ages.push_back(a-1);
            }
        }
        ages = new_ages;
    }

    cout << ages.size() << endl;

}