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
	return false;
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


