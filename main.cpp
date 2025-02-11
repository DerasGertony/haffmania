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



    cout<<"ready";


    return 0;
}