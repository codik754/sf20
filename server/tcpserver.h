//Файл tcpserver.h
#pragma once

#include "iserver.h"
#include "datetime.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr short lengthMessage = 1024;//длина сообщения

//Класс для TCP-сервера
class TcpServer : public IServer{
   int sockets_; //сокет для обмена данными
   struct sockaddr_in serveraddr_;//адрес сервера
   struct sockaddr_in  client_;//адрес клиента
   uint16_t port_;  //порт для обмена сообщениями 
   char m_[lengthMessage]; //массив для отправки и получения сообщений
   int connection_;//переменная для соединения
   unsigned short amountErrors_; //количество подряд идущих ошибок
   Datetime timing_; //время последней ошибки. Нужно для сравнения
public:
   //Конструктор по умолчанию
   TcpServer();
   //Конструктор с параметрами
   explicit TcpServer(uint16_t port);
   //Деструктор класса
   virtual ~TcpServer() override = default;

   void config() override;  //настройка сервера
   void listenAndWait() override; //слушать и ждать соединение
   void stop() override; //остановка соединения
   void receive(char *buf, short length) override; //ждать сообщения от клиента
   bool send(const char *message) override; //отправка сообщения клиенту
   bool send(const int n) override; //отправка сообщения клиенту
   bool send(const size_t n) override; //отправка сообщения клиенту
   bool send(const unsigned n) override; //отправка сообщения клиенту
   bool send(const bool bit) override; //отправка сообщения клиенту

   //Напечатать текущую дату и время
   void printDateTime();
   //Это ошибка
   void thisIsError();
};
