//Файл serverchat.h
#include "iserver.h"
#include "tcpserver.h"
#include "user.h"
#include "message.h"
#include "sha256.h"
#include "datetime.h"
#include <memory>
#include <vector>

class ServerChat{
   std::unique_ptr<IServer> server_;//указатель для работы с сервером
   std::vector<User> users_;//вектор пользователей
   std::vector<Message> messages_;//вектор сообщений
   
public:
   //Конструктор по умолчанию
   ServerChat() : server_(new TcpServer(55000)), users_(), messages_() {
      SHA256 sha256;
      users_.emplace_back("admin", sha256("a123"));//добавляем админа
   }

   //Деструктор класса
   ~ServerChat() = default;

   //Напечатать текущую дату и время
   void printDateTime();

   //Настройка сервера
   void config();

   //Ожидать соединения
   void wait();

   //Закрыть соединение
   void close();

   //Принять сообщение
   void receive(char *m, int length);

   //Авторизация пользователя
   bool authUser(const std::string &login, const std::string &password);

   //Отправить сообщения на клиент
   void sendMessages(const std::string &login, const size_t amount);

   //Установить статус пользователя не авторизирвован
   void logOutUser(const std::string &login);

   //Добавить пользователя
   int addUser(const std::string &login, const std::string &password);

   //Добавить сообщение
   int addMessage(const std::string &from, const std::string &to, const std::string &text);

};
