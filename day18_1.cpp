#include <iostream>
#include <vector>
#include <memory>

using namespace std;

struct snailnum {
    int atom;
    shared_ptr<snailnum> p1,p2;
    shared_ptr<snailnum> parent;
    bool right;
};

void print(shared_ptr<snailnum> s) {
    if (s->p1) {
        cout << "["; print(s->p1);cout << ","; print(s->p2); cout << "]";
    } else {
        cout << s->atom;
    }
}

shared_ptr<snailnum> parse(char*& line) {
    auto s = shared_ptr<snailnum>(new snailnum());
    if (*line == '[') {
        ++line;
        s->p1 = parse(line);
        s->p1->right = false;
        s->p1->parent = s;
        ++line;
        s->p2 = parse(line);
        s->p2->right = true;
        s->p2->parent = s;
        ++line;
    } else {
        s->atom = (*line-'0');
        ++line;
    }
    return s;
}

shared_ptr<snailnum> find_explode(shared_ptr<snailnum> s, int level=0) {
    if (!s || (level == 4 && s->p1)) return s;
    
    auto res = find_explode(s->p1, level+1);
    if (res) return res;
    else return find_explode(s->p2, level+1);
}

shared_ptr<snailnum> find_next(shared_ptr<snailnum> s, bool left_or_right) {
    auto current = s;
    bool right = current->right;

    while (((!right)^left_or_right) && current) {
        current = current->parent;
        if (current) right = current->right;
    }

    if (!current) return current;
    current = current->parent;
    if (!current) return current;

    if (left_or_right) {
        current = current->p2;
        while (current->p1) current = current->p1;
    } else {
        current = current->p1;
        while (current->p2) current = current->p2;
    }

    return current;
}

void explode(shared_ptr<snailnum> s) {
    auto left = find_next(s, false);
    auto right = find_next(s, true);

    auto left_val = s->p1->atom;
    auto right_val = s->p2->atom;

    if (left) left->atom += left_val;
    if (right) right->atom += right_val;

    s->p1.reset();
    s->p2.reset();
    s->atom = 0;
}

shared_ptr<snailnum> find_split(shared_ptr<snailnum> s) {
    if (!s || (!(s->p1) && s->atom > 9)) return s;
    auto a = find_split(s->p1);
    if (a) return a;
    else return find_split(s->p2);
}

void split(shared_ptr<snailnum> s) {
    s->p1.reset(new snailnum());
    s->p1->atom = s->atom/2;
    s->p1->right = false;
    s->p1->parent = s;
    s->p2.reset(new snailnum());
    s->p2->atom = (s->atom+1)/2;
    s->p2->right = true;
    s->p2->parent = s;
}

const int LINE_SIZE = 256;

void reduce(shared_ptr<snailnum> s) {
    while (true) {
        auto a = find_explode(s);
        if (a) explode(a);
        else {
            auto b = find_split(s);
            if (b) split(b);
            else return;
        }
        //print(s); cout << endl;
    }
}

long magnitude(shared_ptr<snailnum> s) {
    if (!(s->p1)) return (long)s->atom;
    return 3*magnitude(s->p1)+2*magnitude(s->p2);
}

int main() {

    shared_ptr<snailnum> number;

    while (true) {
        char line[LINE_SIZE];
        cin.getline(line, LINE_SIZE);
        if (!cin) break;
        char* cursor = line;
        auto s = parse(cursor);
        if (!number) number = s;
        else {
            cout << "  "; print(number); cout << endl;
            cout << "+ "; print(s); cout << endl;
            shared_ptr<snailnum> temp = number;
            number.reset(new snailnum());
            number->p1 = temp;
            number->p1->right = false;
            number->p1->parent = number;
            number->p2 = s;
            number->p2->right = true;
            number->p2->parent = number;
            reduce(number);
            cout << "= ";print(number); cout << endl << endl;
        }
    }

    cout << magnitude(number) << endl;
}
