#include <iostream>

using namespace std;

int main() {
    int pos_x = 0;
    int pos_y = 0;
    int aim = 0;

    char line[32];

    while (cin) {
        cin.getline(line, 32);
        char *a = line;
        while (*a != ' ') a++;
        while (*a == ' ') a++;
        int number = atoi(a);

        char c = line[0];
        if (c=='f') {
            pos_x += number;
            pos_y += aim*number;
        }
        else if (c == 'u') aim -= number;
        else if (c == 'd') aim += number;
    }

    cout << pos_x*pos_y << endl;
}