#include <string>
#include <vector>
#include "encoder.h"
#include <bits/stdc++.h>
using namespace std;
#define BIT8 8


Node* uniteNodes(Node* lchild, Node* rchild) // по сути из массива создает дерево
{
    Node * res = new Node;
    res->code = (short*)malloc(1024* sizeof(short));
    res->codelen = 0;
    res->freq = lchild->freq + rchild->freq;
    res->simb.first = 1;
    res->simb.second = 0;
    res->left = lchild;
    res->right = rchild;
    res->numnode= lchild->numnode + rchild->numnode + 1;
    return res;

}


bool compn(Node* a, Node* b) {
    return a->freq < b->freq;
}


void read(string& from, vector<pair<int,char>>& freq){ // создает массив пар буква-ее частота
    FILE * fr = fopen(from.c_str(), "rb");
    if (!fr)
        return;
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        int k = fgetc(fr);
        freq[k].first++;
        freq[k].second = k;
    }
    fclose(fr);
}


vector<Node*> frtoNo(vector<pair<int,char>>& freq){ // из пар делает ноды для создания дерева
    static vector<Node*> tree;
    for(int i = 0; i < freq.size(); i++){
        if(freq[i].first) {
            Node* k = new Node;
            k->code = (short*)malloc(1024* sizeof(short));
            k->codelen = 0;
            k->right = new Node;
            k->left = new Node;
            k->freq = freq[i].first;
            k->simb.first = 0;
            k->simb.second = freq[i].second;
            k->numnode = 1;
            tree.push_back(k);
        }
    }
    cout<<"\ncodingtree";
    stable_sort(tree.begin(), tree.end(), compn);
    return tree;
}

void treefication(vector<Node*>&tree){ // по сути из массива одиночных нод собирает все массив в дерево где последняя нода корень
    int i = 0;
    while(true){
        if(i+1 == tree.size()){
            break;
        }

        Node* k = uniteNodes(tree[i], tree[i+1]);
        tree.push_back(k);

        stable_sort(tree.begin(), tree.end(), compn);
        i+=2;
    }
}






