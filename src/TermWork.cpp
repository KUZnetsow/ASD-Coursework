#include <fstream>
#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    graph graph;
    setlocale(LC_ALL, "RUS");
    try {
        fstream in("in.txt");
        graph.inputVertex(in);
        in.open("in.txt");
        graph.inputEdge(in);
    }
    catch (exception warning) {
        cout << warning.what() << endl;
    }
    cout << endl;
    try {
        cout << "Максимальный поток в сети " << graph.MaxFlow();
    }
    catch (exception warning) {
        cout << warning.what() << endl;
    }
    return 0;
}