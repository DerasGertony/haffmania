#include <iostream>
#include <unordered_map>
#include <bitset>
#include <string>
using namespace std;

// Функция для перевода бинарной строки в число
int binToInt(const string& bin) {
    int result = 0;
    for (char c : bin) {
        result = result * 2 + (c - '0');
    }
    cout << bin << " -> " << result << endl;
    return result;
}

// Функция для расшифровки сообщения
string decodeMessage(const string& str) {
    int index = 0;
    
    // Проверка длины входной строки
    if (str.size() < 16) {
        cerr << "Ошибка, короткая строка." << endl;
        return "";
    }
    
    // Считываем количество завершающих нулей (первые 8 бит)
    int trailingZeros = binToInt(str.substr(index, 8));
    index += 8;
    
    // Считываем размер алфавита (вторые 8 бит)
    int alphabetSize = binToInt(str.substr(index, 8));
    index += 8;
    
    cout << "Количество завершающих нулей: " << trailingZeros << endl;
    cout << "Количество символов в алфавите: " << alphabetSize << endl;
    
    unordered_map<string, char> huffmanTable;
    cout << "Коды символов: " << endl;
    
    // Считываем символы алфавита и их коды
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
    
    // Вычисляем длину закодированного сообщения
    int messageLength = str.size() - index - trailingZeros;
    if (messageLength < 0) {
        cerr << "Ошибка, некорректное количество завершающих нулей." << endl;
        return "";
    }
    string encodedMessage = str.substr(index, messageLength);
    index += messageLength;
    
    // Расшифровываем сообщение
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

int main() {
    string input;
    cout << "Введите бинарное сообщение: ";
    cin >> input;
    string result = decodeMessage(input);
    
    if (!result.empty()) {
        cout << "\nРасшифрованное сообщение: " << result << endl;
    }
    return 0;
}
