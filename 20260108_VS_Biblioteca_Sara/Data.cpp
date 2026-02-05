#include "Data.h"
#include <time.h>

ostream& operator<<(ostream& os, Data& data)
{
	os << (short)data.day << "/" << (short)data.month << "/" << data.year;
	return os;
}



Data::Data()
{
	//Ha d'iniciar-se amb la data actual
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);
	this->day = now->tm_mday;
	this->month = now->tm_mon + 1;
	this->year = now->tm_year + 1900;
}

Data::Data(int day, int month, int year)
{
	if (verificarDiaMesAny(day, month, year)) {
		this->day = day;
		this->month = month;
		this->year = year;
	}
	else {
		throw "Data no vàlida en el constructor";
	}
}

//==================GETTERS==================

int Data::getDay()
{
	return day;
}

int Data::getMonth()
{
	return month;
}

int Data::getYear()
{
	return year;
}

//==================SETTERS==================

bool Data::setDay(int day)
{
	if (verificarDiaMesAny(day, this->month, this->year)) {
		this->day = day; return true;
	}
	return false;
}

bool Data::setMonth(int month)
{
	if (verificarDiaMesAny(this->day, month, this->year)) {
		this->month = month; return true;
	}
	return false;
}

bool Data::setYear(int year)
{
	if (verificarDiaMesAny(this->day, this->month, year)) {
		this->year = year; return true;
	}
	return false;
}

//==================METODES==================





/// <summary>
/// Augmenti d1 amb els dies indicats a X, que pot ser negatiu
/// </summary>
/// <param name="days"></param>
/// <returns></returns>
Data Data::sumar_dies(int days)
{
	//TODO: Millorar eficiencia
	if (days < 0) return *this; //TODO.

	for (int i = 0; i < days; ++i) {
		if (verificarDiaMesAny(day + 1, month, year)) {
			day++;
		}
		else {
			day = 1;
			if (verificarDiaMesAny(day, month + 1, year)) {
				month++;
			}
			else {
				month = 1;
				year++;
			}
		}
	}
	return *this;
}

bool Data::verificarDiaMesAny(int day, int month, int year)
{
	if (year < 0 || month < 1 || month > 12) {
		return false;
	}
	int diesPerMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (month == 2 && esAnyTraspas(year)) {
		diesPerMes[2] = 29;
	}
	return (day >= 1 && day <= diesPerMes[month]);
}

bool Data::esAnyTraspas(int year)
{
	// Un any és de traspàs si:
	// 1. És divisible per 4 I NO per 100
	// 2. O si és divisible per 400
	return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}


/* Constructor de còpia
* //No cal mentre no tinguem dades dinamiques
Data::Data(const Data& Data)
{
}
*/

//==================OPERADORS==================

/*
* No cal mentre no tinguem dades dinamiques
Data& Data::operator=(const Data& Data)
{
	// TODO
	return *this;

}
*/

bool Data::operator==(const Data& Data)
{
	if (this->day != Data.day)return false;
	if (this->month != Data.month)return false;
	if (this->year != Data.year)return false;
	return true;
}

bool Data::operator!=(const Data& Data)
{
	if (this->day != Data.day)return true;
	if (this->month != Data.month)return true;
	if (this->year != Data.year)return true;
	return false;
}



bool Data::operator<(const Data& Data)
{
	if (this->year < Data.year)return true;
	if (this->month < Data.month)return true;
	if (this->day < Data.day)return true;
	return false;
}

bool Data::operator<=(const Data& Data)
{
	/*if (this->year < Data.year)return true;
	if (this->month < Data.month)return true;
	if (this->day < Data.day)return true;
	if (this->day == Data.day && this->month == Data.month && this->year == this->year)return true;
	return false;*/
	return (*this == Data || *this < Data);

}

bool Data::operator>(const Data& Data)
{
	if (this->year > Data.year)return true;
	if (this->month > Data.month)return true;
	if (this->day > Data.day)return true;
	return false;
}



bool Data::operator>=(const Data& Data)
{
	/*if (this->year > Data.year)return true;
	if (this->month > Data.month)return true;
	if (this->day > Data.day)return true;
	if (this->day == Data.day && this->month == Data.month && this->year == this->year)return true;
	return false;*/
	return (*this == Data || *this > Data);
}

// Pre-increment: ++d
Data& Data::operator++() {
	*this = sumar_dies(1);
	return *this;
}

// Post-increment: d++
Data Data::operator++(int) {
	Data copia(*this); 
	++(*this);        
	return copia;      
}
// Pre-decrement: --d
Data& Data::operator--() {
	*this = sumar_dies(-1);
	return *this;
}

// Post-decrement: d--
Data Data::operator--(int) {
	Data copia(*this); 
	--(*this);        
	return copia;      
}

Data Data::operator+(int x)
{
	return Data(this->sumar_dies(x));
}

Data Data::operator-(int x)
{
	return Data(this->sumar_dies(-x));
}

Data &Data::operator+=(int x)
{
	*this = this->sumar_dies(x); 
	return *this;
}

Data &Data::operator-=(int x)
{
	*this = this->sumar_dies(-x);
	return *this;
}

//Data::~Data()
//{
//	//Només cal si tenim dades dinàmiques
//}

Data operator+(const int& dies, Data& data)
{
	return data + dies;
}
