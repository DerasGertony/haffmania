#define _CRT_SECURE_NO_WARNINGS
#ifndef COMPRESSION_DECODER_H
#define COMPRESSION_DECODER_H
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <string.h>
#include <bitset>
#include <string>

using namespace std;
class Decoder {
public:
    Decoder(const char* output_file_name){
        file = fopen(output_file_name, "rb");
        fseek(file, -1L, SEEK_END);
        size_of_last_bite = (getc(file) - '0');
        file_name = output_file_name;
         file_len = ftell(file);
        fseek(file, 0, SEEK_SET);
    }
    ~Decoder(){
        fclose(file);
    }
     void parse_to_map();
    void extract();
     void replaceCompressedToFull(string filename2);
private:
    unordered_map<string, char > hashMap;
    FILE * file;
    string file_name;
    long file_len;
    int size_of_last_bite;
    string decodedResult;
};




#endif