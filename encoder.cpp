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


void addCode(Node*&root){ // спускаясь по нодам дает им код где кодес это чек чтоб когда дал последний код не ушел в цикл
    if(root->numnode==1){
        return;
    }

    memcpy(root->right->code,root->code, sizeof(root->code));
    root->right->codelen = root->codelen;
    root->right->code[root->right->codelen] = 1;
    root->right->codelen++;
    addCode(root->right);

    memcpy(root->left->code, root->code, sizeof(root->code));
    root->left->codelen = root->codelen;
    root->left->code[root->left->codelen] = 0;
    root->left->codelen++;
    addCode(root->left);

}

void clean(char*& a){ // убирает мусор из строк мапы
    int i = 0;
    while(a[i]=='0' || a[i]=='1'){i+=1;}
    a[i]=0;
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
    map<char, char*> a;
    cout<<"\ncoding1";
    for(auto & i : tree){ // собирает мапу где ключ символ дата-> код
        if(i->simb.first == 0) {
            char* buf = (char*)malloc(i->codelen * sizeof(char));
            for (int j = 0; j < i->codelen; j++){
                if(i->code[j]){
                    buf[j] = '1';}
                else{
                    buf[j] = '0';
                }
            }
            a[i->simb.second] = (char*)malloc(i->codelen * sizeof(char));
            clean(buf);
            strcpy(a[i->simb.second], buf);


        }

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

    string reswalph;
    char lenalph = 0;
    for(int i = 0; i < tree.size(); i++){
        if(tree[i]->simb.first == 0) {
            lenalph+=1;
        }
    }
    reswalph = decToBinary(lenalph - 1); // чтоб 512 тоже влезло


    for(int i = 0; i < tree.size(); i++){ // добавляем в начало длину алфавита и сам алфавит в виде (символ, длина его кода в битах, код)
        if(tree[i]->simb.first == 0) {
            reswalph+=decToBinary(tree[i]->simb.second);
            reswalph+=decToBinary(tree[i]->codelen);
            reswalph+= a[tree[i]->simb.second];
        }
    }
    reswalph+=res;



    vector<bool> end = stringToBits(reswalph);
    cout<< end.size() << ' ' << reswalph.size();
    int tail = (8-end.size()%8)%8;  // без этого нельзя будет почарно(ну то есть никак) записать/считать
    fputc(tail,out);
    for(int i = 0; i<tail; i++){
        end.push_back(false);
    }
    for(int i = 0; i < end.size(); i+=8){// биты собираем в байты и записываем
        fputc(end[i] * 128 + end[i+1] * 64 +end[i+2] * 32 +end[i+3] * 16 +end[i+4] * 8 +end[i+5] * 4 +end[i+6] * 2 +end[i+7] * 1, out);
    }
    fclose(out);
    return "";

}







