#include "Fitxa.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define DEBUG

//==================CONSTRUCTORS==================

Fitxa::Fitxa() : referencia("REF"), titol(NULL), esDeixa(NULL), dataCreacio(NULL) {
	////Inicialitzar les dades dinàmiques a null
	//this->titol = NULL;
	//this->esDeixa = NULL;

	/*strcpy(this->referencia, "??????????");
	this->titol = NULL;
	this->esDeixa = NULL;*/
	//setReferencia("??????????");
	setTitol("?");
}

//Hhem de posar el nom de la classe al principi per indicar que forma part de la classe.
Fitxa::Fitxa(const char* referencia, const char* titol) {
	//Inicialitzar les dades dinàmiques a null
	this->titol = NULL;
	this->esDeixa = NULL;

	//Gestio de la referencia
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referencia és obligatoria i de llargada REF_LEN";
	}
	strcpy(this->referencia, referencia);

	//gestio del titol:
	if (titol == NULL || strlen(titol) == 0) {
		throw "El títol és obligatori";
	}
	//Creem espai pel titol:
	this->titol = new char[strlen(titol) + 1];
	if (this->titol == NULL) {
		throw "no hi ha memoria pel titol de la fitxa";
	}
	strcpy(this->titol, titol);
}

Fitxa::Fitxa(const char* referencia, const char* titol, bool* esDeixa) {
	//Inicialitzar les dades dinàmiques a null
	this->titol = NULL;
	this->esDeixa = NULL;

	//Gestio de la referencia
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referencia és obligatoria i de llargada REF_LEN";
	}
	strcpy(this->referencia, referencia);

	//gestio del titol:
	if (titol == NULL || strlen(titol) == 0) {
		throw "El títol és obligatori";
	}
	//Creem espai pel titol:
	this->titol = new char[strlen(titol) + 1];
	if (this->titol == NULL) {
		throw "no hi ha memoria pel titol de la fitxa";
	}
	strcpy(this->titol, titol);

	//Gestio de esDeixa:
	setEsDeixa(esDeixa);


}
Fitxa::Fitxa(const char* referencia, const char* titol, bool* esDeixa, Data* dataCreacio)
{
	//TODO
}


//==================CONSTRUCTOR DE COPIA==================
Fitxa::Fitxa(const Fitxa& fitxa) : titol(NULL), esDeixa(NULL) {
	setReferencia(fitxa.referencia);
	setTitol(fitxa.titol);
	setEsDeixa(fitxa.esDeixa);
}

//==================OPERADORS==================
Fitxa& Fitxa::operator=(const Fitxa& fitxa) {
#ifdef DEBUG
	std::cout << "\t*...Usant constructor de copia...*" << this->referencia << "..." << std::endl;
#endif // DEBUG
	setReferencia(fitxa.referencia);
	setTitol(fitxa.titol);
	setEsDeixa(fitxa.esDeixa);
	return *this;
}

bool Fitxa::operator==(const Fitxa& fitxa)
{
	return (strcmp(this->referencia, fitxa.referencia) == 0);
}

bool Fitxa::operator!=(const Fitxa& fitxa)
{
	return strcmp(this->referencia, fitxa.referencia) != 0;
}

bool Fitxa::operator<=(const Fitxa& fitxa)
{

	return (strcmp(this->referencia, fitxa.referencia) <= 0);

}

bool Fitxa::operator<(const Fitxa& fitxa)
{
	return (strcmp(this->referencia, fitxa.referencia) < 0);
}

bool Fitxa::operator>=(const Fitxa& fitxa)
{

	return (strcmp(this->referencia, fitxa.referencia) >= 0);

}

bool Fitxa::operator>(const Fitxa& fitxa)
{
	return (strcmp(this->referencia, fitxa.referencia) > 0);
}



//==================DESTRUCTOR==================
Fitxa::~Fitxa() {
#ifdef DEBUG
	std::cout << "\t...Alliberant memoria de la fitxa " << this->referencia << "..." << std::endl;
#endif // DEBUG


	delete[] titol;
	delete esDeixa;
	delete dataCreacio;
	//Per si el programador invoca el destructor per netejar l'objecte:
	titol = NULL;
	esDeixa = NULL;
	dataCreacio = NULL;
}



//==================SETTERS==================
void Fitxa::setReferencia(const char* referencia) {
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referència és obligatòria i de llargada REF_LEN [10]";
	}

	// Omplim la referència
	strcpy(this->referencia, referencia);
}

void Fitxa::setTitol(const char* titol) {
	if (titol == NULL || strlen(titol) == 0) {
		throw "El títol és obligatori";
	}
	//Hem d'alliberar el titol anterior
	delete[] this->titol;
	//SI volguessim més eficiencia podem comprovar si la length del titol anterior es igual a l'actual.

	// Omplim el títol dinàmic
	this->titol = new char[strlen(titol) + 1];
	if (this->titol == NULL) {
		throw "No hi ha memòria pel títol de la fitxa";
	}

	strcpy(this->titol, titol);
}

void Fitxa::setEsDeixa(const bool* esDeixa) {
	if (esDeixa == NULL) {
		delete this->esDeixa;
		this->esDeixa = NULL;
	}
	else {
		if (this->esDeixa == NULL) {
			this->esDeixa = new bool;
			//Comprovar que s'ha pogut crear memoria
			if (this->esDeixa == NULL) {
				throw "No s'ha pogut reservar memoria";
			}
			//this->esDeixa = (bool*)esDeixa; MALAMENT. COPIEM VALORS, NO ADRECES
			*(this->esDeixa) = *esDeixa;

		}
		else {
			*(this->esDeixa) = *esDeixa;
		}

	}
}

//==================GETTERS==================
const char* Fitxa::getReferencia() {
	return this->referencia;
}
const char* Fitxa::getTitol() {
	return this->titol;
}
const bool* Fitxa::getEsDeixa() {
	return this->esDeixa;

}

//==================METODES==================
void Fitxa::visualitzar() {
	std::cout << "  Referencia: " << this->getReferencia() << std::endl;
	std::cout << "  Titol: " << this->getTitol() << std::endl;
	std::cout << "  Es deixa?: ";
	if (this->esDeixa == NULL) {
		std::cout << "?" << std::endl;;
	}
	else if (*(this->esDeixa)) {
		std::cout << "Si" << std::endl;
	}
	else {
		std::cout << "No" << std::endl;
	}
	std::cout << "  Data d'alta: "<< this->dataAlta << std::endl;;;
	std::cout << "  Data creació: ";
	if (this->dataCreacio == NULL) {
		std::cout << "?" << std::endl;;
	}
	else {
		std::cout << this->dataCreacio << std::endl;;
	}


}

ostream& operator<<(ostream& os, Fitxa& fitxa)
{
	//Això és ineficient
	//os << "Ref: " << fitxa.getReferencia() << "- Titol: " << fitxa.getTitol();
	
	//Farem les classes friends per no haver de cridar els getters.
	//(Hem posat 	friend ostream& operator<<(ostream& os, Fitxa& fitxa); al fitxer.h)
	os << "Ref: " << fitxa.referencia << "- Titol: " << fitxa.titol;


	
	return os;
}
