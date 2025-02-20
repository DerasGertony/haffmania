
#include "fastdec.h"
#include <math.h>
vector<bool> strToBits(const string& str) { // переводит символы в биты логично
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

void clean(char*& a){ // убирает мусор из строк мапы
    int i = 0;
    while(a[i]=='0' || a[i]=='1'){i+=1;}
    a[i]=0;
}


void fdecode(string from, string to) {
    FILE *fr = fopen(from.c_str(), "rb");
    FILE *wher = fopen(to.c_str(), "w");
    if (!fr)
        return;


    map<string, char> a;
    char c;
    char* buffer = (char*)calloc(300, sizeof(char));
    string count;
    while (true) {
        c = fgetc(fr);
        count += c;
        if (c != '\n') {
        }
        else {
            break;
        }
    }
    int intCount = stoi(count);

    for (int i = 0; i < intCount; i++) {
        buffer[0] = '\0';
        char currentSymbol = 0;
        currentSymbol = fgetc(fr);
        if(!currentSymbol){
            cout<<"aaaaaaaaa";
        }
        while ((c = fgetc(fr)) != '\n') {
            strncat(buffer, &c, 1);
        }
        clean(buffer);
        a[buffer] = currentSymbol;
    }


    free(buffer);
    for(auto r:a){
        cout<<r.second<<endl;
        cout<<r.first<<endl;
    }

    fclose(fr);
    fclose(wher);
}