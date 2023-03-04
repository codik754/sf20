//Файл message.h
#pragma once
#include <string>
#include "datetime.h"

//Класс для сообщений
class Message {
	const std::string sendedFrom_;//от кого отправлено сообщение
	const std::string sendedTo_;  //кому отправлено сообщение
	const std::string text_;	//текст сообщения
	const Datetime dateandtime_; //дата отправки сообщения
public:
	//Конструктор по умолчанию
	Message();
	//Конструктор с параметрами
	Message(const std::string& from, const std::string& to, const std::string& text);
   //Конструктор с параметрами
	Message(const std::string& from, const std::string& to, const std::string& text, const Datetime &dateandtime); 

	//Конструктор копирования
	Message(const Message& other);
	//Деструктор
	~Message() = default;
	

	//Узнать от кого отправлено сообщение
	const std::string& getSendedFrom() const;
   //Узнать кому отправлено сообщение
   const std::string& getSendedTo() const;
	//Получить текст сообщения
	const std::string& getText() const;
	//Получить дату и время
	const std::string getDatetime() const;
	//Соответсвует ли поле кому отправлено сообщение переданной строке
	bool checkToSendedTo(const std::string &login) const;

   //Получить секунду отправки сообщения
   int getSec() const;
   //Получить минуты отправки сообщения
   int getMin() const;
   //Получить часы отправки сообщения
   int getHour() const;
   //Получить день отправки сообщения
   int getDay() const;
   //Получить месяц отправки сообщения
   int getMonth() const;
   //Получить год отправки сообщения
   int getYear() const;
};
