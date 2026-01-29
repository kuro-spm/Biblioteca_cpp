#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED


#include <iostream>
using namespace std;

class Data
{
private:
	friend ostream& operator<<(ostream& os, Data& data);
	char day, month;
	short year;

public:
	Data();
	Data(int day, int month, int year);

	//Constructor de copia
	Data(const Data& Data);
	//Operador d'assignacio
	Data& operator = (const Data& Data);
	//Operadors de comparacio
	bool operator == (const Data& Data);
	bool operator != (const Data& Data);
	bool operator <= (const Data& Data);
	bool operator < (const Data& Data);
	bool operator >= (const Data& Data);
	bool operator > (const Data& Data);
	//Destructor:
	//~Data(); //Només cal si tenim dades dinàmiques

	Data sumar_dies(int days);
	static bool verificarDiaMesAny(int day, int month, int year);
	static bool esAnyTraspas(int year);


}; //TANCAR CLASSE

ostream& operator << (ostream& os, Data& data);


#endif
