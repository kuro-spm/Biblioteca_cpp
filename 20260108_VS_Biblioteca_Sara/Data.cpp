#include "Data.h"
#include <time.h>

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

int Data::getDay() const { return day; }
int Data::getMonth() const { return month; }
int Data::getYear() const { return year; }

//==================SETTERS==================

//Es podrien haver fet els setters amb alies(&) per estalviar una mica de memòria en comptes de passar els paràmetres per valor...

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

int Data::diesDelMes(const int& mes, const int& any) {
	const int dies[] = { 31, 28, 31,30,31,30,31,31,30,31,30,31 };
	if (mes == 2 && esAnyTraspas(any)) return 29;
	return dies[mes - 1];
}

/// <summary>
/// Augmenti d1 amb els dies indicats a X, que pot ser negatiu
/// </summary>
/// <param name="days"></param>
/// <returns></returns>
Data Data::sumar_dies(int d)
{
	if (d == 0) return *this;
	while (d > 0) {
		int diesMes = diesDelMes(month, year); // mes i any de la data actual
		int diesQuedenDinsMes = diesMes - day;    // dies que queden del mes
		if (d < diesQuedenDinsMes) {    // x conté els dies que queden per sumar
			day += d; d = 0; return *this;   // ja hem sumat tots els dies
		}
		d -= (diesQuedenDinsMes + 1);    // x el disminuïm amb els dies del mes
		// +1 per què ens ubiquem en el dia 1 del mes següent
		day = 1;    // Ens situem en el dia 1 del mes següent
		month++;     // Mes següent
		if (month == 13) {
			month = 1; year++;
		}
	}
	while (d < 0) {
		int diesMesAnterior;
		if (month == 1) {
			diesMesAnterior = 31;     // Desembre sempre te 31 dies
		}
		else {
			diesMesAnterior = diesDelMes(month - 1, year); // mes-1 i any de la data actual
		}
		if (-d < day) {    // x conté els dies que queden per restar
			day += d; d = 0;  return *this;
		}
		d += day;
		day = diesMesAnterior;
		month--;
		if (month == 0) {
			month = 12; year--;
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
	//Només cal si tenim dades dinàmiques
}

//Destructor
Data::~Data()
{
	//Només cal si tenim dades dinàmiques
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

bool Data::operator<=(const Data& Data) {
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
	*this = sumar_dies(1); //S'incrementa 'objecte actual
	return *this; //i es retorna l'objecte actual.
}

// Post-increment: d++
Data Data::operator++(int) {
	Data copia(*this); //Es fa una copia
	++(*this); //S'incrementa l'obecte actual
	return copia; //Es retorna la còpia.
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

Data& Data::operator+=(int x)
{
	*this = this->sumar_dies(x);
	return *this;
}

Data& Data::operator-=(int x)
{
	*this = this->sumar_dies(-x);
	return *this;
}

Data operator+(const int& dies, Data& data)
{
	return data + dies;
}

//A Data.h: 	friend ostream& operator<<(ostream& os, const Data& data);

ostream& operator<<(ostream& os, const Data& data)
{
	os << (short)data.day << "/" << (short)data.month << "/" << data.year;
	return os;
}


