//Файл datetime.cpp

#include "datetime.h"
#include <ctime>
#include <sstream>
#include <memory>

//Конструктор по умолчанию
Datetime::Datetime() {
    time_t sec = time(NULL);
    std::shared_ptr<tm*> now = std::make_shared<tm*>(localtime(&sec));

    sec_ = (*now)->tm_sec;
    min_ = (*now)->tm_min;
    hour_ =(*now)->tm_hour;
    day_ = (*now)->tm_mday;
    month_ = (*now)->tm_mon + 1;
    year_ = (*now)->tm_year + 1900;
}

//Конструктор копирования
Datetime::Datetime(const Datetime& other) {
    sec_ = other.sec_;
    min_ = other.min_;
    hour_ = other.hour_;
    day_ = other.day_;
    month_ = other.month_;
    year_ = other.year_;
}

//Оператор присваивания
Datetime& Datetime::operator = (const Datetime &other) {
    //Проверка на самоприсваивание
    if (&other == this) {
        return *this;
    }
    sec_ = other.sec_;
    min_ = other.min_;
    hour_ = other.hour_;
    day_ = other.day_;
    month_ = other.month_;
    year_ = other.year_;
    return *this;
}

//Установить текущие время
void Datetime::setNow() {
    time_t sec = time(NULL);
    std::shared_ptr<tm*> now = std::make_shared<tm*>(localtime(&sec));

    sec_ = (*now)->tm_sec;
    min_ = (*now)->tm_min;
    hour_ =(*now)->tm_hour;
    day_ = (*now)->tm_mday;
    month_ = (*now)->tm_mon + 1;
    year_ = (*now)->tm_year + 1900;
}

//Получить дату и время в виде строки
const std::string Datetime::getStrAll() const {
    std::ostringstream os;
    os << day_ << "." << month_ << "." << year_ << "  " << hour_ << ":" << min_ << ":" << sec_;
    return os.str();
}

//Получить дату в виде строки
const std::string Datetime::getStrDate() const {
    std::ostringstream os;
    os << day_ << "." << month_ << "." << year_;
    return os.str();
}

//Получить время в виде строки
const std::string Datetime::getStrTime() const {
    std::ostringstream os;
    os << hour_ << ":" << min_ << ":" << sec_;
    return os.str();
}

//Получить секунды
int Datetime::getSec() const {
   return sec_;
}

//Получить минуты
int Datetime::getMin() const{
   return min_;
}

//Получить часы
int Datetime::getHour() const{
   return hour_;
}

//Получить день
int Datetime::getDay() const{
   return day_;
}

//Получить месяц
int Datetime::getMonth() const{
   return month_;
}

//Получить год
int Datetime::getYear() const{
   return year_;
}

//Разница меньше двух секунд
bool Datetime::diffTwoSec(const Datetime &other) const{
   if(year_ != other.year_){
      return false;
   }

   if(month_ != other.month_){
      return false;
   }

   if(day_ != other.day_){
      return false;
   }

   if(hour_ != other.hour_){
      return false;
   }
   
   if(min_ != other.min_){
      return false;
   }

   if(sec_ > other.sec_){
      if((sec_ - other.sec_) > 2){
         return false;
      }
   }
   else{
      if((other.sec_ - sec_) > 2){
         return false;
      }
   }

   return true;
}
