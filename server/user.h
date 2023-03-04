//Файл user.h
#pragma once
#include <string>
#include <memory>

//Класс для пользователя
class User{
	const std::string login_;//поле для логина
	std::string password_;//поле для пароля
   bool isAuth_;//пользователь авторизирован
public:
	//Конструктор по умолчанию
	User() : login_("UNKNOWN"), password_("UNKNOWN"), isAuth_(false) {}
	//Параметризированный конструктор
	User(const std::string& login, const std::string& password)
		: login_(login), password_(password), isAuth_(false) {}

	~User() = default;//деструктор класса
   
	//Проверка логина
	bool checkLogin(const std::string &login) const;

	//Проверка пароля
	bool checkPassword(const std::string& password) const;

	const std::string& getLogin() const;//получить логин

   //Установить бит авторизации
   void setAuth();

   //Сбросить бит авторизации
   void resetAuth();

   bool checkAuth() const; //получить статус авторизации
};
