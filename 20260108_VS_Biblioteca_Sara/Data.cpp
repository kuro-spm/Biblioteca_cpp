#include "Data.h"
#include <time.h>

ostream& operator<<(ostream& os, Data& data)
{
	// TODO: Insertar una instrucción "return" aquí
}

Data::Data()
{

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





Data Data::sumar_dies(int days)
{
	return Data();
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



Data::Data(const Data& Data)
{
}

Data& Data::operator=(const Data& Data)
{
	// TODO
	return *this;

}

bool Data::operator==(const Data& Data)
{
	return false;
}

bool Data::operator!=(const Data& Data)
{
	return false;
}

bool Data::operator<=(const Data& Data)
{
	return false;
}

bool Data::operator<(const Data& Data)
{
	return false;
}

bool Data::operator>=(const Data& Data)
{
	return false;
}

bool Data::operator>(const Data& Data)
{
	return false;
}

Data::~Data()
{

}


