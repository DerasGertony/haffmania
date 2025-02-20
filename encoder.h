
#include <iostream>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>
using namespace std;


#ifndef UNTITLED8_ENCODER_H
#define UNTITLED8_ENCODER_H

// Node structure for a Binary Tree
class Node {
public:
    Node* left;
    Node* right;
    Node* par;
    std::pair<char, int> simb;
    int codelen;
    int freq;
    int numnode;
};


vector<Node*> frtoNo(vector<pair<int,char>>& freq);
vector<bool> stringToBits(const string& str);
void read(string& from, vector<pair<int,char>>& freq);
void treefication(vector<Node*>&tree);
void addCode(vector<Node*>&tree);
string filetobytes(vector<Node*>&tree, string& from);
string decToBinary(int n);

#endif //UNTITLED8_ENCODER_H

