//Файл iclient.h
#pragma once

#include <arpa/inet.h>

//Интерфейс для клиента
class IClient{
public:
   virtual ~IClient() = default; //деструктор класса
   virtual void config(const char *address, uint16_t port) = 0;//настройка клиента
   virtual void connectToServer() = 0;//соединение с сервером
   virtual bool send(const char *message) = 0;//отправить сообшение
   virtual bool send(const int n) = 0;//отправить сообшение
   virtual bool send(const unsigned n) = 0;//отправить сообшение
   virtual bool send(const bool bit) = 0;//отправить сообшение
   virtual bool send(const size_t n) = 0;//отправить сообшение
   virtual void receive(char *buf, short length) = 0;//получить сообщение
   virtual void disconnect() = 0; //завершение соединения
};
