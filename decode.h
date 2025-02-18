#ifndef DECODE_H
#define DECODE_H

#include <string>
#include <unordered_map>

// Функция для перевода бинарной строки в число
int binToInt(const std::string& bin);

// Функция для расшифровки сообщения
std::string decodeMessage(const std::string& str);

// Чтение бинарной строки из файла
std::string readBinaryFromFile(const std::string& filename);

// Запись текста в файл
void writeToFile(const std::string& text, const std::string& filename);

#endif
