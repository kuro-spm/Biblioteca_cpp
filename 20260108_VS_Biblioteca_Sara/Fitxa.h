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
	friend ostream& operator<<(ostream& os, const Fitxa& fitxa);

private: //Per defecte ja és private. No caldria.
	char referencia[REF_LEN + 1];
	
	unique_ptr<char[]> titol; //char* titol;
	unique_ptr<bool> esDeixa; //bool* esDeixa;
	Data dataAlta;
	unique_ptr<Data> dataCreacio; //Data* dataCreacio;

public:
	Fitxa();
	Fitxa(const char* referencia, const char* titol);
	Fitxa(const char* referencia, const char* titol, bool* esDeixa);
	Fitxa(const char* referencia, const char* titol, bool* esDeixa, Data* dataCreacio);
	//Constructor de còpia
	Fitxa(const Fitxa& fitxa);
	//Operador d'assignacio
	Fitxa& operator = (const Fitxa& fitxa);

	//Moviment: No s'han de poder utilitzar els operadors de moviment, ja que no té sentit moure una fitxa. Per tant, els eliminem explícitament.
	Fitxa(Fitxa&& fitxa) = delete; //Constructor de MOVIMENT
	Fitxa& operator=(Fitxa&& fitxa) = delete; //Assignació de MOVIMENT

	//Operadors de comparacio
	bool operator == (const Fitxa& fitxa);
	bool operator != (const Fitxa& fitxa);
	bool operator <= (const Fitxa& fitxa);
	bool operator < (const Fitxa& fitxa);
	bool operator >= (const Fitxa& fitxa);
	bool operator > (const Fitxa& fitxa);
	//Destructor:
	~Fitxa() = default;

	void setReferencia(const char* referencia);
	void setTitol(const char* titol);
	void setEsDeixa(const bool* esDeixa);
	void setDataCreacio(const Data* dataCreacio);

	const char* getReferencia() const;
	const char* getTitol() const;
	const bool* getEsDeixa() const;
	const Data* getDataCreacio() const;
	const Data& getDataAlta() const;

	void visualitzar();

}; //Tancar classe

ostream& operator<<(ostream& os, const Fitxa& fitxa);

#endif


