//Файл message.cpp
#include "message.h"

//Конструктор по умолчанию
Message::Message() : sendedFrom_("UNKNOWN"), sendedTo_("UNKNOWN"), text_("UNKNOWN"), dateandtime_() {}

//Конструктор с параметрами
Message::Message(const std::string& from, const std::string& to, const std::string& text) : sendedFrom_(from), sendedTo_(to), text_(text), dateandtime_() {}

//Конструктор с параметрами
Message::Message(const std::string& from, const std::string& to, const std::string& text, const Datetime &dateandtime) : sendedFrom_(from), sendedTo_(to), text_(text), dateandtime_(dateandtime) {}

//Конструктор копирования
Message::Message(const Message& other) : sendedFrom_(other.sendedFrom_), sendedTo_(other.sendedTo_), text_(other.text_), dateandtime_(other.dateandtime_) {}

//Узнать от кого отправлено сообщение
const std::string& Message::getSendedFrom() const {
	return sendedFrom_;
}

//Узнать кому отправлено сообщение
const std::string& Message::getSendedTo() const {
   return sendedTo_;
}

//Получить текст сообщения
const std::string& Message::getText() const {
	return text_;
}

//Получить дату и время
const std::string Message::getDatetime() const {
	return dateandtime_.getStrAll();
}

//Соответсвует ли поле кому отправлено сообщение переданной строке
bool Message::checkToSendedTo(const std::string& login) const {
	return sendedTo_ == login;
}

//Получить секунду отправки сообщения
int Message::getSec() const{
   return dateandtime_.getSec();
}

//Получить минуты отправки сообщения
int Message::getMin() const{
   return dateandtime_.getMin();
}

//Получить часы отправки сообщения
int Message::getHour() const{
   return dateandtime_.getHour();
}

//Получить день отправки сообщения
int Message::getDay() const{
   return dateandtime_.getDay();
}

//Получить месяц отправки сообщения
int Message::getMonth() const{
   return dateandtime_.getMonth();
}

//Получить год отправки сообщения
int Message::getYear() const{
   return dateandtime_.getYear();
}
