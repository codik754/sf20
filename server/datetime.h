//Файл datetime.h
#pragma once
#include <string>

//Класс для даты и времени
class Datetime
{
	int sec_;  //секунды
	int min_;  //минуты
	int hour_; //час
	int day_;  //день
	int month_;//месяц
	int year_; //год
public:
	
	//Конструктор по умолчанию
	Datetime();
   //Консруктор с параметрами
   Datetime(int sec, int min, int hour, int day, int month, int year) : sec_(sec), min_(min), hour_(hour), day_(day), month_(month), year_(year) {}

	//Конструктор копирования
	Datetime(const Datetime &other);
	//Деструктор
	~Datetime() = default;

	//Оператор присваивания
	Datetime& operator = (const Datetime& other);

	//Установить текущие время и дату
	void setNow();

	//Получить дату и время в виде строки
	const std::string getStrAll() const;
	//Получить дату в виде строки
	const std::string getStrDate() const;
	//Получить время в виде строки
	const std::string getStrTime() const;

   //Получить секунды
   int getSec() const;
   //Получить минуты
   int getMin() const;
   //Получить часы
   int getHour() const;
   //Получить день
   int getDay() const;
   //Получить месяц
   int getMonth() const;
   //Получить год
   int getYear() const;
   
   //Разница меньше двух секунд
   bool diffTwoSec(const Datetime &other) const;
};

