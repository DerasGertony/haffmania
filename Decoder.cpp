#include "Decoder.h"

void Decoder::parse_to_map(){
    char c;

    char* buffer = (char*) calloc(100, sizeof(char));
    if(!file) return;
    // считываем кол-во пар ключей/значений
    string count;
    while (true) {
        c = fgetc(file);

        count += c;
        if (c != '\n') {
        } else {
            break;
        }
    }
//            cout << count;
    int intCount = stoi(count);
    //  cout << intCount;

//             складываем все пары в мапу
    cout << "COUNT: " << intCount << "\n";

    for (int i = 0; i < intCount; i++){
        buffer[0] = '\0';
        char currentSymbol = fgetc(file);


        while ((c = fgetc(file)) != '\n'){
            strncat(buffer, &c, 1);
        }

        hashMap[buffer] = currentSymbol;



    }
    //считываем лишний \n
    c = fgetc(file);

    free(buffer);
}

void Decoder::extract(){
    parse_to_map();
    long long remainsSymbols = file_len - ftell(file) - 1;
    cout << "rem: " << remainsSymbols << "\n";
    char c;
    char * buffer = (char*) calloc(10, sizeof(char));
    string buff = "";
    long long index = 0;

    while (++index <= remainsSymbols){

        // cout << index << "\n";
        c = fgetc(file);
        std::bitset<8> x(c);
        int start = 7;
        int end = 0;
        if (index == remainsSymbols){
            start = size_of_last_bite - 1;
        }
        // cout << "BITSET: " << x << "\n";
        for (int i = start; i >= end; i--){
            if (x[i] == 0){
                buff += '0';
            } else {
                buff += '1';
            }
            // cout << "BUFFER " << buff << "\n";
            if (hashMap[buff]){
                //    cout << hashMap[buff];
                decodedResult += hashMap[buff];
                buff.clear();
            }
        }
    }
    free(buffer);

}

void Decoder::replaceCompressedToFull(string filename2){
    const char * res = decodedResult.c_str();
    FILE * file2 = fopen(filename2.c_str(), "wb");
    fputs(res, file2);
    fclose(file2);
}