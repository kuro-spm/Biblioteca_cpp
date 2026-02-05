#ifndef FITXA_H_INCLUDED
#define FITXA_H_INCLUDED

#define REF_LEN 10

#include <iostream>
#include "Data.h"
using namespace std;

#pragma once
class Fitxa
{
	//funcio que tindra acces a totes les dades privades, etc.
	friend ostream& operator<<(ostream& os, Fitxa& fitxa);

private: //Per defecte ja és private. No caldria.
	char referencia[REF_LEN + 1];
	char* titol;
	bool* esDeixa;
	Data dataAlta;
	Data* dataCreacio;



public:
	Fitxa();
	Fitxa(const char* referencia, const char* titol);
	Fitxa(const char* referencia, const char* titol, bool* esDeixa);
	//Constructor de copia
	Fitxa(const Fitxa& fitxa);
	//Operador d'assignacio
	Fitxa& operator = (const Fitxa& fitxa);
	//Operadors de comparacio
	bool operator == (const Fitxa& fitxa);
	bool operator != (const Fitxa& fitxa);
	bool operator <= (const Fitxa& fitxa);
	bool operator < (const Fitxa& fitxa);
	bool operator >= (const Fitxa& fitxa);
	bool operator > (const Fitxa& fitxa);
	//Destructor:
	~Fitxa();

	void setReferencia(const char* referencia);
	void setTitol(const char* titol);
	void setEsDeixa(const bool* esDeixa);

	const char* getReferencia();
	const char* getTitol();
	const bool* getEsDeixa();

	void visualitzar();




}; //Tancar classe

ostream& operator << (ostream& os, Fitxa& fitxa);
#endif


