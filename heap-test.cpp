#include "heap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "please provide input filename" << endl;
        return 1;
    }

    ifstream myfile(argv[1]);
    if (myfile.fail()) {
        cout << "unable to read file.";
        return 1;
    }

    std::vector<int> vals;
    int num;

    while (myfile >> num) {
        vals.push_back(num);
    }

    cout << "original list: ";
    for (size_t i = 0; i < vals.size(); i++) {
        cout << vals[i] << " ";
    }
    cout << endl;

    Heap<int, std::greater<int> > heap;

    for (size_t i = 0; i < vals.size(); i++) {
        heap.push(vals[i]);
    }

    cout << "popped list:   ";
    while (!heap.empty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
    cout << endl;

    return 0;
}