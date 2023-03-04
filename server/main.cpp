//Файл main.cpp

#include <iostream>
#include <string>
#include "serverchat.h"
#include "useful.h"

void clientCode(){
   ServerChat server;//создаем объект для сервера
    
   server.config();//настраиваем его
   
   char m[lengthMessage];//делаем массив для получения сообщений
   bzero(m, lengthMessage);
   
   while(1){
      server.wait();//сервер ждет подключения
      while(strncmp("END", m, 3) != 0){
         server.receive(m, lengthMessage);//получаем данные
         //Если пришла команда для авторизации
         if(strncmp("CHK", m, 3) == 0){
            //Условие для авторизации
            server.printDateTime();
            std::cout << "Authorization request received" << std::endl;

            //Принимаем логин
            server.receive(m, lengthMessage);
            std::string login(m);

            //Принимаем пароль
            server.receive(m, lengthMessage);
            std::string password(m);
            
            server.authUser(login, password);

            bzero(m, lengthMessage);
         }
         else if(strncmp("MSG", m, 3) == 0){
            //Если пришла команда для получения сообщений
            //Условие для отправки сообщений
            server.printDateTime();
            std::cout << "Received a request to receive messages" << std::endl;

            //Принимаем логин
            server.receive(m, lengthMessage);
            std::string login(m);
            
            //Прием количества сообщений на клиенте
            server.receive(m, lengthMessage);
            size_t amount = charToSizeT(m);

            server.sendMessages(login, amount);
            
            bzero(m, lengthMessage);
         }
         else if(strncmp("USR", m, 3) == 0){
            //Если пришла команда для авторизации
            //Условие для добавления пользователя
            server.printDateTime();
            std::cout << "Received a request to add a user" << std::endl;
            
            //Принимаем логин
            server.receive(m, lengthMessage);
            std::string login(m);

            //Принимаем пароль
            server.receive(m, lengthMessage);
            std::string password(m);

            int res = server.addUser(login, password);

            if(res == 1){
               setColor("INSERT");
               server.printDateTime();
               std::cout << "User " << login << " added" << std::endl;
               setColor("DEFAULT");
            }
            else if(res == 2){
               setColor("ERROR");
               server.printDateTime();
               std::cout << "User " << login << " not added" << std::endl;
               setColor("DEFAULT");
            }

            bzero(m, lengthMessage);
         }
         else if(strncmp("ADM", m, 3) == 0){
            //Если пришла команда для добавления сообщения
            //Условие для добавления сообщения
            server.printDateTime();
            std::cout << "Received a request to send a message" << std::endl;

            //Принимаем логин отправителя
            server.receive(m, lengthMessage);
            std::string from(m);

            //Принимаем логин получателя
            server.receive(m, lengthMessage);
            std::string to(m);

            //Принимаем текст сообщения
            server.receive(m, lengthMessage);
            std::string text(m);

            int res = server.addMessage(from, to, text);

            if(res == 1){
               setColor("INSERT");
               server.printDateTime();
               std::cout << "User " << from << " sent a message" << std::endl;
               setColor("DEFAULT");
            }
            else if(res == 2){
               setColor("ERROR");
               server.printDateTime();
               std::cout << "User " << from << " did not send a message" << std::endl;
               setColor("DEFAULT");
            }

            bzero(m, lengthMessage);
         }
         else if(strncmp("BCK", m, 3) == 0){
            //Если пришла команда для выхода пользователя
            server.receive(m, lengthMessage);
            std::string login(m);
            server.logOutUser(login);
            bzero(m, lengthMessage);
         }
      }
      bzero(m, lengthMessage);
   }
   server.close();//закрывае соединение
}

int main(){
   clientCode();

   return 0;
}
