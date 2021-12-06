#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    vector<long> ages(9,0); // index -> number of fish with age as index
    while (cin) {
        int age;
        cin >> age;
        if (cin) ages[age]++;
        cin.ignore(1);
    }

    int gens = 256;

    for (int i=0;i<gens;i++) {
        vector<long> new_ages(9,0);
        long breeding = ages[0];
        for (unsigned j=1;j<ages.size();j++) {
            new_ages[j-1] = ages[j];
        }
        new_ages[6] += breeding;
        new_ages[8] = breeding;

        ages = new_ages;
    }

    cout << accumulate(ages.cbegin(), ages.cend(), (long)0) << endl;

}