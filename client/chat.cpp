//Файл chat.cpp
#include "chat.h"
#include "useful.h"
#include <iostream>
#include <cstdlib>
#include <algorithm> 


//Показать первое меню
char Chat::showHelloMenu() {
    char choice = '0';//переменная для выбора
    while (true) {
        clearScreen();
        setColor("FIRST");
        std::cout << "Добрый день! Добро пожаловать в чат. Что будем делать?" << std::endl;
        std::cout << "1. Подключиться" << std::endl;
        std::cout << "2. Регистрация" << std::endl;
        std::cout << "q - Выход" << std::endl;
        std::cout << std::endl << "Введите символ: ";
        setColor("INSERT");
        std::cin >> choice;
        //Если введены символы соответствующие требуемым
        if (choice == '1' || choice == '2' || choice == '3' || choice == 'q') {
            break;
        }
        else {
            //Если введены символы не соответствующие выбранным
            clearScreen();
            setColor("ERROR");
            std::cout << "Команды " << choice << " не знаю!!!" << std::endl;
            setColor("DEFAULT");
            waitEnter(); 
            clearScreen();
        }
    }
    setColor("DEFAULT");
    return choice;
}


//Показать меню для входа
void Chat::showLogIn() {
    clearScreen();
    std::string tlogin;
    std::string tpassword;
    setColor("FIRST");
    std::cout << "Введите данные для входа " << std::endl;
    std::cout << "Логин: ";
    setColor("INSERT");
    std::cin >> tlogin;
    setColor("FIRST");
    std::cout << "Пароль: ";
    setColor("INSERT");
    std::cin >> tpassword;
    
    //Подключаемся к серверу
    try{
      configClient();//настраиваем клиент
      connectToServer();//подлючаемся к серверу
    }
    catch(const char *e){
      clearScreen();
      setColor("ERROR");
      std::cout << e << std::endl;
      setColor("DEFAULT");
      waitEnter();
      clearScreen();
      return;
    }
    catch(...){
      clearScreen();
      setColor("ERROR");
      std::cout << "Unknown exception!" << std::endl;
      setColor("DEFAULT");
      waitEnter();
      clearScreen();
      return;
    }
    
 
    SHA256 sha256;//создаем объект для хеширования пароля
    bool res = auth(tlogin, sha256(tpassword));
    
    clearScreen();
    //Если пользователь не найден
    if (!res) {
        setColor("ERROR");
        std::cout << "Логин или пароль введены неверно!" << std::endl;
        setColor("DEFAULT");
        waitEnter();
        clearScreen();
        client_->send("END");
        disconnect();
        return;
    }
    setColor("DEFAULT");
    login_ = tlogin;
    messages_.clear();
    
    showChatMenu();//показываем меню чата
    logOutUser();//отправляем запрос на выход из системы
    
    client_->send("END");
    disconnect();
}

//Авторизация
bool Chat::auth(std::string login, std::string password){
   client_->send("CHK");
   client_->send(login.c_str());
   client_->send(password.c_str());

   char m[lengthMessage];
   client_->receive(m, lengthMessage);
   
   return charToBool(m);
}

//Настройка клиента для соединения
void Chat::configClient(){
  client_->config(ip_.c_str(), port_);
}

//Соединение с сервером
void Chat::connectToServer(){
  client_->connectToServer(); 
}

//Отключиться от сервера
void Chat::disconnect(){
   client_->disconnect();
}

//Получить сообщения от сервера
void Chat::receiveMessages(const std::string &login){
   client_->send("MSG");
   client_->send(login.c_str());
   client_->send(messages_.size());

   char m[lengthMessage];
   client_->receive(m, lengthMessage);
   
   size_t amount = charToSizeT(m);
  
   //Получаем сообщения
   for(size_t i = 0; i < amount; ++i){
      //Получаем информацию об отправители
      client_->receive(m, lengthMessage);
      std::string from = m;
      
      //Получаем информацию о получателе
      client_->receive(m, lengthMessage);
      std::string to = m;

      //Получаем сообщения сообщения
      client_->receive(m, lengthMessage);
      std::string text = m;

      //Получаем секунды отправки сообщения
      client_->receive(m, lengthMessage);
      int sec = charToInt(m);

      //Получем минуты отправки сообщения
      client_->receive(m, lengthMessage);
      int min = charToInt(m);

      //Получаем часы отправки сообщения
      client_->receive(m, lengthMessage);
      int hour = charToInt(m);

      //Получаем день отправки сообщения
      client_->receive(m, lengthMessage);
      int day = charToInt(m);

      //Получаем месяц отправки сообщения
      client_->receive(m, lengthMessage);
      int month = charToInt(m);

      //Получаем год отправки сообщения
      client_->receive(m, lengthMessage);
      int year = charToInt(m);

      Datetime date(sec, min, hour, day, month, year);
      
      messages_.emplace_back(from, to, text, date);
   }
}

//Показать общий чат
void Chat::showAllChat(){
   setColor("FIRST");
   std::cout << "Общий чат" << std::endl;
   Datetime date;//объект для определения даты и времени
   date.setNow();//устанавливаем текущую дату и время
   //Выводим на экран
   std::cout << date.getStrDate() << std::endl;
   std::cout << date.getStrTime() << std::endl;
  
   std::cout << "________________________________________________________________________________________________" << std::endl;
   //Определяем есть ли сообщения в общем чате
  if (calculateAllMessages() == 0) {
       setColor("TEXT");
       std::cout << std::endl << "Сообщений нет" << std::endl;
   }
   else {
       //Определяем количество новых сообщений в общем чате
       for (const auto& message : messages_) {
           //Если поле кому содержит all
           if (message.checkToSendedTo("all")) {
               setColor("USER");
               //Выводим того кто отправл сообщение
               std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
               setColor("DEFAULT");
               setColor("TEXT");
               //Выводим текст
               std::cout << message.getText() << std::endl;
               setColor("DATE");
               //Выводим дату и время отправки сообщения
               std::cout << message.getDatetime() << std::endl;
               std::cout << std::endl;
               setColor("DEFAULT");
           }
       }
   }
   setColor("FIRST");
   std::cout << "________________________________________________________________________________________________" << std::endl;
   std::cout << "1 - Обновить чат   2 - Личные сообщения" << "  3 - Написать сообщение " << "q - Выход" << std::endl;
   setColor("DEFAULT");
}

//Показать чат с личными сообщениями
void Chat::showSelfChat(){
   setColor("FIRST");
   std::cout << "Личные сообщения" << std::endl;
   Datetime date;//объект для определения даты и времени
   date.setNow();//устанавливаем текущую дату и время
   //Выводим на экран
   std::cout << date.getStrDate() << std::endl;
   std::cout << date.getStrTime() << std::endl;
   std::cout << "________________________________________________________________________________________________" << std::endl;
   //Если количество личных сообщений равно 0
   if (calculateSelfMessages() == 0) {
       setColor("TEXT");
       std::cout << std::endl << "Сообщений нет" << std::endl;
   }
   else {
       for (const auto& message : messages_) {
           //Если поле в сообщение кому соответствует логину текущего пользователя
           if (message.checkToSendedTo(login_)) {
               setColor("USER");
               //Выводим логин отправителя
               std::cout << "[" << message.getSendedFrom() << "]" << std::endl;
               setColor("DEFAULT");
               setColor("TEXT");
               //Выводим сообщение
               std::cout << message.getText() << std::endl;
               setColor("DATE");
               //Выводим дату и время отправки сообщения
               std::cout << message.getDatetime() << std::endl;
               std::cout << std::endl;
               setColor("DEFAULT");
           }
       }
   }
   setColor("FIRST");
   std::cout << "________________________________________________________________________________________________" << std::endl;
   std::cout << "1 - Общий чат" << "  2 - Обновить чат" << "  3 - Написать сообщение  4 - " <<
       "q - Выход" << std::endl;
   setColor("DEFAULT");
}

//Показать меню чата
void Chat::showChatMenu() {
     
    short type = 1;//тип чата(общий или личнные сообщения)
    char choice = '0';//выбор в чате

    while (true) {
        //Если type = 1 выводим общий чат
        if (type == 1){
            receiveMessages(login_);
            showAllChat();
            setColor("FIRST");
            std::cout << "Введите символ: ";
            setColor("INSERT");
            std::cin >> choice;//считываем ввод от пользователя
            setColor("DEFAULT");
        }
        
        //Если type = 2 выводим чат с личными сообщениями
        if (type == 2) {
            receiveMessages(login_);
            showSelfChat();
            setColor("FIRST");
            std::cout << "Введите символ: ";
            setColor("INSERT");
            std::cin >> choice;//считываем ввод от пользователя
            setColor("DEFAULT");
        }

        if (choice == 'q') {
            break;
        }
        else if (choice == '1') {
            if (type == 2) {
                type = 1;
            }
            clearScreen();

            continue;
        }
        else if (choice == '2') {
            if (type == 1) {
                type = 2;
            }
            clearScreen();
            continue;
        }
        else if (choice == '3') {
            clearScreen();
            showWriteMessageMenu();//показать меню для написания сообщения
        }
        clearScreen(); 
    }
    clearScreen(); 
}

//Подсчитать количество общих сообщений
int Chat::calculateAllMessages() const{
    //Подсчитываем количество совпадений
    int amount = std::count_if(messages_.begin(), messages_.end(), [](const Message& m) {
        return m.checkToSendedTo("all");
     });

    return amount;
}

//Подсчитать количество общих сообщений
int Chat::calculateSelfMessages() const{
    std::string login = login_;
    //Подсчитываем количество совпадений
    int amount = std::count_if(messages_.begin(), messages_.end(), [login](const Message& m) {
        return m.checkToSendedTo(login);
     });
    return amount;
}

//Отправить запрос на выход
void Chat::logOutUser(){
   client_->send("BCK");
   client_->send(login_.c_str());
   login_.clear();
   messages_.clear();
}

//Показать меню регистрации
void Chat::showRegistrationMenu() {
     clearScreen();
     std::string tlogin;
     std::string tpassword;

     
    //Подключаемся к серверу
    try{
      configClient();//настраиваем клиент
      connectToServer();//подлючаемся к серверу
    }
    catch(const char *e){
      clearScreen();
      setColor("ERROR");
      std::cout << e << std::endl;
      setColor("DEFAULT");
      waitEnter();
      clearScreen();
      return;
    }
    catch(...){
      clearScreen();
      setColor("ERROR");
      std::cout << "Unknown exception!" << std::endl;
      setColor("DEFAULT");
      waitEnter();
      clearScreen();
      return;
    }
     
     setColor("FIRST");
     std::cout << "Введите регистрационные данные" << std::endl;
     std::cout << "Логин: ";
     setColor("INSERT");
     std::cin >> tlogin;

     //Проверяем соответствует ли логин требованиям 
     if (tlogin.length() < 3) {
         clearScreen();
         setColor("ERROR");
         std::cout << "Логин очень короткий! Логин должен быть более 2 символов." << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
         return;
     }

     if (tlogin.length() > 8) {
         clearScreen();
         setColor("ERROR");
         std::cout << "Логин очень длинный! Логин должен быть не более 8 символов." << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
         return;
     }


     setColor("FIRST");
     std::cout << "Пароль: ";
     setColor("INSERT");
     std::cin >> tpassword;

     SHA256 sha256;

     //Отправляем логин и пароль
     client_->send("USR");
     client_->send(tlogin.c_str());
     client_->send((sha256(tpassword)).c_str());
      
     //Получаем результат
     char m[lengthMessage];
     client_->receive(m, lengthMessage);

     int res = charToInt(m);

     if(res == 1){
         clearScreen();
         setColor("INSERT");
         std::cout << "Поздравляем! Регистрация прошла успешно." << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
     }
     else if(res == 2){
         clearScreen();
         setColor("ERROR");
         std::cout << "Этот логин занят!" << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
     }

     client_->send("END");
     disconnect();
     clearScreen();
}


//Показать меню для написания сообщений
void Chat::showWriteMessageMenu() {
    std::string to;
    std::string text;
        
    setColor("FIRST");
    std::cout << "Кому писать сообщение(all в общий чат): ";
    setColor("INSERT");
    std::cin >> to;
    setColor("FIRST");
    std::cout << "Текст сообщения: ";
    setColor("INSERT");
    std::cin.ignore();
    std::getline(std::cin, text);
    
    //Если поле пустое
    if (text.empty()) {
       clearScreen();
       setColor("ERROR");
       std::cout << "Поле сообщение пустое!!!" << std::endl;
       setColor("DEFAULT");
       waitEnter();
       return;
    }

     //Отправляем данные на сервер
     client_->send("ADM");
     client_->send(login_.c_str());
     client_->send(to.c_str());
     client_->send(text.c_str());
      
     //Получаем результат
     char m[lengthMessage];
     client_->receive(m, lengthMessage);

     int res = charToInt(m);

     if(res == 1){
         clearScreen();
         setColor("INSERT");
         std::cout << "Сообщение отправлено!" << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
     }
     else if(res == 2){
         clearScreen();
         setColor("ERROR");
         std::cout << "Пользователя с таким логином нет в чате" << std::endl;
         setColor("DEFAULT");
         waitEnter();
         clearScreen();
     }
     setColor("DEFAULT");
}
