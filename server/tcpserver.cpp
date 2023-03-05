//Файл tcpserver.cpp
#include "tcpserver.h"
#include "datetime.h"
#include <iostream>
#include <string>

//Конструктор по умолчанию
TcpServer::TcpServer() : sockets_(-1), serveraddr_(), client_(), port_(55000), connection_(-1), amountErrors_(0), timing_(){
   bzero(m_, lengthMessage);
}

//Конструктор с параметрами
TcpServer::TcpServer(uint16_t port) : sockets_(-1), serveraddr_(), client_(), port_(port), connection_(-1), amountErrors_(0), timing_(){
   bzero(m_, lengthMessage);
}

//Настройка сервера сервера
void TcpServer::config(){
   printDateTime();
   std::cout << "Server configuration started" << std::endl;
   //Создаем сокет
   sockets_ = socket(AF_INET, SOCK_STREAM, 0);
   
   if(sockets_ == -1){
      Datetime now; 
      std::string str = "[" + now.getStrAll() + "] ";
      str += "Exception: Socket creation failed!";
      throw str;
   }

   serveraddr_.sin_addr.s_addr = htonl(INADDR_ANY);
   //Задаем номер порта для связи
   serveraddr_.sin_port = htons(port_); 
   //Используем IPv4
   serveraddr_.sin_family = AF_INET;

   //Привязываем сокет
   int bind_status = bind(sockets_, (struct sockaddr*) &serveraddr_, sizeof(serveraddr_));
   
   //Если привязать не удалось
   if(bind_status == -1){
      Datetime now; 
      std::string str = "[" + now.getStrAll() + "] ";
      str += "Exception: Socket binding failed!";
      throw str;
   }
  
   printDateTime();
   std::cout << "Server uses the port " << port_ << std::endl;
  
   printDateTime();
   std::cout << "Server configuration finished" << std::endl;
}

void TcpServer::listenAndWait(){
   //Поставим сервер на прием данных
   int connection_status = listen(sockets_, 5);
   
   if(connection_status == -1){
      Datetime now; 
      std::string str = "[" + now.getStrAll() + "] ";
      str += "Exception: Server is unable to listen for new connections";
      throw str;
   }
   else{
      printDateTime();
      std::cout << "Server is listening for new connections" << std::endl;
   }

   socklen_t length = sizeof(client_);
   connection_ = accept(sockets_, (struct sockaddr*) &client_, &length);

   if(connection_ == -1){
      Datetime now; 
      std::string str = "[" + now.getStrAll() + "] ";
      str += "Exception: Server is unable to accept the data from client";
      throw str;
   }

   printDateTime();
   std::cout << "A client has connected" << std::endl;
}

//Oстановка соединения
void TcpServer::stop(){
   close(sockets_);
   printDateTime();
   std::cout << "Server is stopped" << std::endl;
}

//Ждать сообщения от клиента
void TcpServer::receive(char *buf, short length){
   bzero(m_, sizeof(m_));
   bzero(buf, length);

   ssize_t bytes = read(connection_, m_, sizeof(m_));
   if(bytes > 0){
      strcpy(buf, m_);
   }
   else{
      printDateTime();
      std::cout << "error receiving data from the client" << std::endl;
      thisIsError();
   }
}

//Отправка сообщения клиенту
bool TcpServer::send(const char *message){
   bzero(m_, sizeof(m_));
   strcpy(m_, message);
   ssize_t bytes = write(connection_, m_, sizeof(m_));
            
   //Если передать не получилось возвращаем false
   return bytes > 0;
}

//Отправка сообщения клиенту
bool TcpServer::send(const int n){
   bzero(m_, sizeof(m_));
   std::string temp = std::to_string(n);
      
   strcpy(m_, temp.c_str());

   ssize_t bytes = write(connection_, m_, sizeof(m_));
   //Если передать не получилось
   return bytes > 0;
}

//Отправка сообщения клиенту
bool TcpServer::send(const size_t n){
   bzero(m_, sizeof(m_));
   std::string temp = std::to_string(n);
      
   strcpy(m_, temp.c_str());

   ssize_t bytes = write(connection_, m_, sizeof(m_));
   //Если передать не получилось
   return bytes > 0;
}

//Отправка сообщения клиенту
bool  TcpServer::send(const unsigned n){
   bzero(m_, sizeof(m_));

   std::string temp = std::to_string(n);
      
   strcpy(m_, temp.c_str());

   ssize_t bytes = write(connection_, m_, sizeof(m_));
   //Если передать не получилось
   return bytes > 0;
}

//Отправка сообщения клиенту
bool TcpServer::send(const bool bit){
   bzero(m_, sizeof(m_));

   if(bit){
      strcpy(m_, "1");
   }
   else{
      strcpy(m_, "0");
   }

   ssize_t bytes = write(connection_, m_, sizeof(m_));
   //Если передать не получилось
   return bytes > 0;
}

//Напечатать текущую дату и время
void TcpServer::printDateTime(){
   Datetime now;
   std::cout << "[" << now.getStrAll() << "] ";
}

//Это ошибка
void TcpServer::thisIsError(){
   Datetime now;//текущие время

   //Проверяем меньше ли двух секунд разница во времени
   if(timing_.diffTwoSec(now)){
      ++amountErrors_;//увеличиваем количество подряд идущих ошибок
      timing_.setNow();//устанавливаем текущее время
   }
   else{
      amountErrors_ = 0;//обнуляем количество подряд идущих ошибок
      timing_.setNow();//утанавливаем текущее время
   }

   //Проверяем количество ошибок
   if(amountErrors_ == 10){
      std::string str = "[" + now.getStrAll() + "] ";
      str += "Exception: Several consecutive errors. The server operation is interrupted";
      throw str;
   }
}
