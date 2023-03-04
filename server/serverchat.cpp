//Файл serverchat.cpp
#include "serverchat.h"
#include "datetime.h"
#include "useful.h"
#include <iostream>

//Напечатать текущую дату и время
void ServerChat::printDateTime(){
   Datetime now;
   std::cout << "[" << now.getStrAll() << "] ";
}

//Настройка сервера
void ServerChat::config(){
   server_->config();
}

//Ожидать соединения
void ServerChat::wait(){
   server_->listenAndWait();
}

//Закрыть соединение
void ServerChat::close(){
   server_->stop();
}

//Принять сообщение
void ServerChat::receive(char *m, int length){
   server_->receive(m, length);
}

//Авторизация пользователя
bool ServerChat::authUser(const std::string &login, const std::string &password){
   //Проверяем логин и пароль
   for(auto &user : users_){
       if(user.checkLogin(login)){
          if(user.checkPassword(password)){
            //Если все удачно
            user.setAuth();
            server_->send(true);
            setColor("INSERT");
            printDateTime();
            std::cout << "User " << login << " has successfully logged in" << std::endl;
            setColor("DEFAULT");
            return true;
          }
       }
   }
   
   //Если совпадений не найдено
   server_->send(false);
   setColor("ERROR");
   printDateTime();
   std::cout << "User " << login << " has not logged in" << std::endl;
   setColor("DEFAULT");
   
   return false;
}


//Запрос на получение сообщений
void ServerChat::sendMessages(const std::string &login, const size_t amount){
   std::vector<Message> v;//вектор для найденных сообщений
   
   //Формируем вектор сообщений
   for(const auto m : messages_){
      if(m.checkToSendedTo(login) || m.checkToSendedTo("all")){
         v.push_back(m);
      }
   }
   
   //Если количество сообщений на клиенте меньше, чем на сервере   
   if(amount < v.size()){
      size_t diff = v.size() - amount;
      server_->send(diff);
      
      for(size_t i = amount; i < v.size(); ++i){
         //Отправляем данные сообщения
         server_->send((v[i].getSendedFrom()).c_str());
         server_->send((v[i].getSendedTo()).c_str());
         server_->send((v[i].getText()).c_str());
         //Отправляем дату частями
         server_->send(v[i].getSec());
         server_->send(v[i].getMin());
         server_->send(v[i].getHour());
         server_->send(v[i].getDay());
         server_->send(v[i].getMonth());
         server_->send(v[i].getYear());

      }
      return;
   }
   else{
      server_->send(0);
   }
}

//Запрос на выход
void ServerChat::logOutUser(const std::string &login){
   for(auto user : users_){
      if(user.checkLogin(login)){
         user.resetAuth();
         printDateTime();
         std::cout << "User " << login << " logged out" << std::endl;
         return;
      }
   }
   setColor("ERROR");
   std::cout << "User " << login << " logged out failed to log out. He is not found" << std::endl;
   setColor("DEFAULT");
}

//Добавить пользователя
int ServerChat::addUser(const std::string &login, const std::string &password){
   //Проверяем есть ли пользователь с таким логином в векторе пользователей
   for(const auto &user : users_){
      if(user.checkLogin(login)){
         server_->send(2);
         return 2;
      }
   }
   
   //Добавляем пользователя
   users_.emplace_back(login, password);
   server_->send(1);
  
   //Добавляем сообщение для нового пользователя от админа
   messages_.emplace_back("admin", login, "Welcome to the chat! We are glad to see you here. Make yourself at home!");
   return 1;
}

//Добавить сообщение
int ServerChat::addMessage(const std::string &from, const std::string &to, const std::string &text){
   //Проверяем есть ли получатель в векторе пользователей
   bool bit = true;
   if(to != "all"){
      bit = false;
      for(const auto &user : users_){
         if(user.checkLogin(to)){
            std::cout << "Логин есть " << to << std::endl;
            bit = true;
            break;
         }
      }
   }

   if(!bit){
      server_->send(2);
      return 2;
   }

   //Добавляем сообщение
   messages_.emplace_back(from, to, text);
   //Отправляем сигнал успешного добавления
   server_->send(1);

   return 1;
}

//Это ошибка
void ServerChat::thisIsError(){
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
   if(amountErrors_ >= 10){
      //Если выполняется условие, то прервываем програму
      printDateTime();
      std::cout << "Several consecutive errors. The server operation is interrupted" << std::endl;
      exit(1);
   }
}

