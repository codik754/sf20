//Файл tcpclient.h
#pragma once

#include "iclient.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>

constexpr short lengthMessage = 1024;

//Класс для TCP-клиента
class TcpClient : public IClient{
   int sockets; //сокет
   struct sockaddr_in serveraddr;//адрес сервера
   struct sockaddr_in client;//адрес клиента
   char m[lengthMessage];//массив для сообщения
public:
   //Конструктор по умолчанию
   TcpClient();

   virtual ~TcpClient() override = default; //деструктор класса
   void config(const char *address, uint16_t port) override;//настройка клиента
   void connectToServer() override;//соединение с сервером
   bool send(const char *message) override;//отправить сообшение
   bool send(const int n) override;//отправить сообшение
   bool send(const unsigned n) override;//отправить сообшение
   bool send(const bool bit) override;//отправить сообшение
   bool send(const size_t n) override;//отправить сообшение
   void receive(char *buf, short length) override;//получить сообщение
   void disconnect() override; //завершение соединения

};
