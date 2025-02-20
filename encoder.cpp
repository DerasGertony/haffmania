#include <string>
#include <vector>
#include "encoder.h"
#include <bits/stdc++.h>
using namespace std;
#define BIT8 8


Node* uniteNodes(Node* lchild, Node* rchild) // по сути из массива создает дерево
{
    Node * res = new Node;
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
            k->codelen = 0;
            k->right = nullptr;
            k->left = nullptr;
            k->freq = freq[i].first;
            k->simb.first = 0;
            k->simb.second = freq[i].second;
            k->numnode = 1;
            tree.push_back(k);
        }
    }
    cout<<"\ncodingtree"<<endl;
    stable_sort(tree.begin(), tree.end(), compn);
    for (int i = tree.size() - 1; i >= 0; i--) {
        cout << (char)tree[i]->simb.second << tree[i]->freq << endl;

    }
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


// спускаясь по нодам дает им код где кодес это чек чтоб когда дал последний код не ушел в цикл
void addCode(Node* root, string str,map<char, string> &a)
    {
        if (root == nullptr)
            return;

        // found a leaf node
        if (!root->left && !root->right) {
            a[root->simb.second] = str;
        }
        addCode(root->left, str + "0", a);
        addCode(root->right, str + "1", a);
    }




string decToBinary(int n) // возвращает строку двоичного представления
{
    int binaryNum[8] = {0};
    string buf;

    int i = 0;
    while (n > 0) {

        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }

    for (int j = 7; j >= 0; j--)
        buf+= to_string(binaryNum[j]);

    return buf;
}

vector<bool> stringToBits(const string& str) { // переводит символы в биты логично
    vector<bool> bits;
    for (char c : str) {
        if (c == '0') {
            bits.push_back(false);
        } else if (c == '1') {
            bits.push_back(true);
        }
    }
    return bits;
}


string filetobytes(vector<Node*>&tree, string& from){ // по сути внутренний мэйн но не совсем
    FILE * fr = fopen(from.c_str(), "rb");
    string res;
    map<char, string> a;
    addCode(tree[tree.size()-1], "", a);
    cout<<"\ncoding1";
    for(auto r:a){
        cout<<r.first<<r.second << a.size()<<endl;
    }
    cout<<"\ncoding2";
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)// заменяет символы на их коды
    {
        char k = fgetc(fr);
        res+=a[k];
    }

    fclose(fr);

    FILE* out = fopen("output.txt", "w");
    FILE* ot = fopen("D.txt", "w");


    char lenalph = a.size();;
    fputs(to_string(lenalph).c_str(),out); // чтоб 256 тоже влезло
    fputc('\n', out);

    for(int i = 0; i < tree.size(); i++){ // добавляем в начало длину алфавита и сам алфавит в виде (символ, длина его кода в битах, код)
        if(tree[i]->simb.first == 0){
            fputc(tree[i]->simb.second, out);
            fputs(a[tree[i]->simb.second].c_str(), out);
            fputc('\n', out);
        }
    }

    cout<<endl;


    vector<bool> end = stringToBits(res);

    cout<< end.size() ;
    int tail = (8-end.size()%8)%8;  // без этого нельзя будет почарно(ну то есть никак) записать/считать
    fputc(tail,out);
    fputc('\n',out);
    cout<<tail;
    fputc(tail, ot);
    for(bool i:end){
        fputc(i+'0',ot);
    }
    fclose(ot);
    for(int i = 0; i<tail; i++){
        end.push_back(false);
    }

    for(int i = 0; i < end.size(); i+=8){// биты собираем в байты и записываем
        fputc(end[i] * 128 + end[i+1] * 64 +end[i+2] * 32 +end[i+3] * 16 +end[i+4] * 8 +end[i+5] * 4 +end[i+6] * 2 +end[i+7] * 1, out);
    }
    fclose(out);
    fclose(ot);
    return "";

}



