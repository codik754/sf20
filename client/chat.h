//Файл chat.h
#include <vector>
#include "message.h"
#include "sha256.h"
#include "tcpclient.h"
#include "iclient.h"
#include <memory>


//Класс для чата
class Chat{
   std::string login_; //логин пользователя
   std::string ip_; //IP-адрес сервера
   uint16_t port_; //порт для подключения к серверу
	std::vector<Message> messages_;//вектор сообщений
   std::unique_ptr<IClient> client_; //объект для работы с сетью

public:
	//Конструктор по умолчанию
	Chat() : login_(), ip_("127.0.0.1"), port_(55000), messages_(), client_(new TcpClient) {
   }

	virtual ~Chat() = default;//деструктор класса

	char showHelloMenu();//показать первое меню
	void showLogIn();//показать меню для входа
   bool  auth(std::string login, std::string password);//авторизация
   void configClient();//настройка клиента для соединения
   void connectToServer();//соедиение с сервером
   void disconnect();//окончания соединения с сервером
   void receiveMessages(const std::string &login);//получить сообщения от сервера
   void showAllChat();//показать общий чат
   void showSelfChat();//показать чат с личными сообщениями
	void showChatMenu();//показать меню чата
   int calculateAllMessages() const;//подсчитать количество общих сообщений
   int calculateSelfMessages() const;//подсчитать количество личных сообщений
   void logOutUser();//отправить запрос на выход
	void showRegistrationMenu();//показать меню регистрации
	void showWriteMessageMenu();//показать меню для написания сообщений
   void showConfigMenu();//меню настройки
};

