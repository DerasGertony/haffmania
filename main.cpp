#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include "encoder.h"
using namespace std;

int main() {
    string filename = "bad.txt"; // вообще можно инпут какой нить написать
    vector<pair<int,char>> freq;
    for(int i = 0; i < 1024; i++){
        freq.push_back(make_pair(0,0));
    }

    // Подсчет символов
    read(filename, freq);
    vector<Node*> tree = frtoNo(freq);
    treefication(tree);
    addCode(tree.back());
    for (int i = tree.size() - 1; i >= 0; i--) {
        cout << tree[i]->freq << ' ';

    }


    for (int i = tree.size() - 1; i >= 0; i--) {
        if (tree[i]->codelen == 0) {
            cout << (char) tree[i]->simb.second << " aaaaaaaaa" << i;
            cout << endl;
        }

    }
    cout << "ready";

    string r = filetobytes(tree, filename);




    cout<<"done";


    return 0;
}