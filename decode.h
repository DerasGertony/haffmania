#ifndef DECODE_H
#define DECODE_H
using namespace std;
#include <string>
#include <unordered_map>

// Функция для перевода бинарной строки в число
int binToInt(const string& bin);

// Функция для расшифровки сообщения
std::string decodeMessage(const string& str);

// Чтение бинарной строки из файла
std::string readBinaryFromFile(const string& filename);

// Запись текста в файл
void writeToFile(const string& text, const string& filename);

#endif
