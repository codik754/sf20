//Файл user.cpp
#include "user.h"

//Получить логин
const std::string& User::getLogin() const {
	return login_;
}

//Проверка логина
bool User::checkLogin(const std::string& login) const {
	return login_ == login;
}

//Проверка пароля
bool User::checkPassword(const std::string& password) const {
	return password_ == password;
}

//Установить бит авторизации
void User::setAuth(){
   isAuth_ = true;
}

//Сбросить бит авторизации
void User::resetAuth(){
   isAuth_ = false;
}

//Получить статус авторизации
bool User::checkAuth() const{
   return isAuth_;
}
