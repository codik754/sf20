//Файл main.cpp
#include <iostream>
#include "chat.h"
#include "useful.h"

void clientCode(){
   Chat chat;
   char c = '0';
   while(1){
      if(c == '0'){
         //Отображаем первое меню
         c = chat.showHelloMenu();
      }
      else if(c == '1'){
         //Открываем окно для ввода логина и пароля
         chat.showLogIn();
         c = '0';
      }
      else if(c == '2'){
         //Отображаем меню для регистрации
         chat.showRegistrationMenu();
         c = '0';
      }
      else if(c == 'q'){
         clearScreen();
         setColor("GOOD");
         std::cout << "До встречи" << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
         break;
      }
      clearScreen();
   }
}

int main(){
   clientCode();

   return 0;
}
