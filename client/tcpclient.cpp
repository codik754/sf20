//файл tcpclient.cpp
#include "tcpclient.h"
#include <iostream>
#include <string>

//Конструктор по умолчанию
TcpClient::TcpClient() : sockets(-1), serveraddr(), client(){
   bzero(m, lengthMessage);
}

//Настройка клиента
void TcpClient::config(const char *address, uint16_t port){
  //Создадим сокет
  sockets = socket(AF_INET, SOCK_STREAM, 0);
   
  if(sockets == -1){
      throw "Creation of socket failed";
  }

  //Установим адрес сервера
  serveraddr.sin_addr.s_addr = inet_addr(address);
  //Зададим номер порта
  serveraddr.sin_port = htons(port);
  //Используем IPv4
  serveraddr.sin_family = AF_INET;
}

//Соединение с сервером
void TcpClient::connectToServer(){
   //Установи соединение с сервером
   int connection = connect(sockets, (struct sockaddr*) &serveraddr, sizeof(serveraddr));

   if(connection == -1){
     throw "Connect with server failed";
   }
}

//Отправить сообшение
bool TcpClient::send(const char *message){
   bzero(m, sizeof(m));
   strcpy(m, message);
   ssize_t bytes = write(sockets, m, sizeof(m));
   
   //Если передать не получилось возвращаем false
   return bytes > 0;
}

//Отправить сообшение
bool TcpClient::send(const int n){
   bzero(m, sizeof(m));
   std::string temp = std::to_string(n);
   
   strcpy(m, temp.c_str());

   ssize_t bytes = write(sockets, m, sizeof(m));
   //Если передать не получилось
   return bytes > 0;
}

//Отправить сообшение
bool TcpClient::send(const unsigned n){
   bzero(m, sizeof(m));

   std::string temp = std::to_string(n);
   
   strcpy(m, temp.c_str());

   ssize_t bytes = write(sockets, m, sizeof(m));
   //Если передать не получилось
   return bytes > 0;
}

//Отправить сообшение
bool TcpClient::send(const bool bit){
   bzero(m, sizeof(m));

   if(bit){
      strcpy(m, "1");
   }
   else{
      strcpy(m, "0");
   }

   ssize_t bytes = write(sockets, m, sizeof(m));
   //Если передать не получилось
   return bytes > 0;
}

//Получить сообщение
void TcpClient::receive(char *buf, short length){
   bzero(m, sizeof(m));
   bzero(buf, length);

   read(sockets, m, sizeof(m));

   strcpy(buf, m);
}

//Завершение соединения
void TcpClient::disconnect(){
   close(sockets);
}

//Отправить сообшение
bool TcpClient::send(const size_t n){
   bzero(m, sizeof(m));
   std::string temp = std::to_string(n);
   
   strcpy(m, temp.c_str());

   ssize_t bytes = write(sockets, m, sizeof(m));
   //Если передать не получилось
   return bytes > 0;
}
