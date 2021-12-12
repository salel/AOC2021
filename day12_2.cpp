#include <iostream>
#include <set>
#include <cstring>
#include <string>
#include <map>

using namespace std;

const int LINE_SIZE = 256;

void find_path(map<string, set<string>> edges, string node, set<string> visited, bool visited_twice, int& paths) {
    if (node == "end") {
        paths++;
        return;
    }
    set<string> new_visited = visited;
    if (node[0] >= 'a') new_visited.insert(node);
    for (auto a : edges.at(node)) {
        if (visited.find(a) == visited.end()) {
            find_path(edges, a, new_visited, visited_twice, paths);
        } else if (!visited_twice) {
            find_path(edges, a, new_visited, true, paths);
        }
    }
}

int main() {
    map<string, set<string> > edges;

    while (true) {
        char line[LINE_SIZE];
        cin.getline(line, LINE_SIZE);
        if (!cin) break;
        int cursor = 0;
        while (line[cursor] != '-') cursor++;
        line[cursor] = '\0';
        string node1(line);
        string node2(line+cursor+1);
        if (node2[node2.size()-1] == '\r') node2.pop_back();

        if (node2 != "start") {
            auto it1 = edges.find(node1);
            if (it1 == edges.end()) edges[node1] = {node2};
            else it1->second.insert(node2);
        }

        if (node1 != "start") {
            auto it2 = edges.find(node2);
            if (it2 == edges.end()) edges[node2] = {node1};
            else it2->second.insert(node1);
        }
    }

    int paths = 0;

    find_path(edges, "start", {}, false, paths);

    cout << paths << endl;

}