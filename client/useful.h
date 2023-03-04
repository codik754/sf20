//Файл useful.h
#pragma once

#include <string>

void setColor(const std::string &color);//установить цвет текста в терминале
void clearScreen();//очистить экран
void waitEnter();//ожидание нажатия клавиши
int charToInt(const char *m);//из char в int
size_t charToSizeT(const char *m);//из char в size_t
unsigned charToUnsigned(const char *m);//из char в unsigned
bool charToBool(const char *m);//из char в bool
