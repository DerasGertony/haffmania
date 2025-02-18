#include "decode.h"
#include <iostream>
#include <bitset>
#include <fstream>

using namespace std;

int binToInt(const string& bin) {
    int result = 0;
    for (char c : bin) {
        result = result * 2 + (c - '0');
    }
    cout << bin << " -> " << result << endl;
    return result;
}

string decodeMessage(const string& str) {
    int index = 0;
    
    if (str.size() < 16) {
        cerr << "Ошибка, короткая строка." << endl;
        return "";
    }
    
    int trailingZeros = binToInt(str.substr(index, 8));
    index += 8;
    
    int alphabetSize = binToInt(str.substr(index, 8));
    index += 8;
    
    cout << "Количество завершающих нулей: " << trailingZeros << endl;
    cout << "Количество символов в алфавите: " << alphabetSize << endl;
    
    unordered_map<string, char> huffmanTable;
    cout << "Коды символов: " << endl;
    
    for (int i = 0; i < alphabetSize; ++i) {
        if (index + 16 > str.size()) {
            cerr << "Ошибка, некорректные данные для символов алфавита." << endl;
            return "";
        }
        
        char symbol = static_cast<char>(binToInt(str.substr(index, 8)));
        index += 8;
        int codeLength = binToInt(str.substr(index, 8));
        index += 8;
        
        if (index + codeLength > str.size()) {
            cerr << "Ошибка, код символа выходит за границы входной строки." << endl;
            return "";
        }
        
        string code = str.substr(index, codeLength);
        index += codeLength;
        huffmanTable[code] = symbol;
        cout << symbol << " -> " << code << endl;
    }
    
    int messageLength = str.size() - index - trailingZeros;
    if (messageLength < 0) {
        cerr << "Ошибка, некорректное количество завершающих нулей." << endl;
        return "";
    }
    string encodedMessage = str.substr(index, messageLength);
    index += messageLength;
    
    string decodedMessage;
    string buffer;
    for (char bit : encodedMessage) {
        buffer += bit;
        if (huffmanTable.count(buffer)) {
            decodedMessage += huffmanTable[buffer];
            buffer.clear();
        }
    }
    
    return decodedMessage;
}

string readBinaryFromFile(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "Ошибка: не удалось открыть файл " << filename << "!" << endl;
        return "";
    }

    string binaryString = "";
    unsigned char byte;
    while (inFile.read(reinterpret_cast<char*>(&byte), 1)) {
        binaryString += bitset<8>(byte).to_string();
    }

    inFile.close();
    return binaryString;
}

void writeToFile(const string& text, const string& filename) {
    ofstream outFile(filename, ios::trunc); 
    if (!outFile) {
        cerr << "Ошибка при открытии файла для записи!" << endl;
        return;
    }

    outFile << text << endl;

    outFile.close();
    cout << "Декодирование успешно завершено." << endl;
}

