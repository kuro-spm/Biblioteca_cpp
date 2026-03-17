#include "Fitxa.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define DEBUG

//==================CONSTRUCTORS==================

Fitxa::Fitxa() //: referencia("REF"), titol(NULL), esDeixa(NULL), dataCreacio(NULL) 
{
	setTitol("?");
}

//Hem de posar el nom de la classe:: al principi per indicar que forma part de la classe.
Fitxa::Fitxa(const char* referencia, const char* titol) //: esDeixa(NULL), dataCreacio(NULL) 
{
	//Amb punters intel·ligènts ja no cal inicialitzar les dades dinàmiques a null
	setReferencia(referencia);
	setTitol(titol);

	////Gestio de la referencia
	//if (referencia == NULL || strlen(referencia) != REF_LEN) {
	//	throw "La referencia és obligatoria i de llargada REF_LEN";
	//}
	//strcpy(this->referencia, referencia); //strcpy per les cadenes...

	////gestio del titol:
	//if (titol == NULL || strlen(titol) == 0) {
	//	throw "El títol és obligatori";
	//}
	////Creem espai pel titol:
	//this->titol = new char[strlen(titol) + 1];
	//if (this->titol == NULL) {
	//	throw "no hi ha memoria pel titol de la fitxa";
	//}
	//strcpy(this->titol, titol); //strcpy per les cadenes...
}

Fitxa::Fitxa(const char* referencia, const char* titol, bool* esDeixa) //: titol(NULL), esDeixa(NULL), dataCreacio(NULL) 
{

	//Gestio de la referencia
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referencia és obligatoria i de llargada REF_LEN";
	}
	strcpy(this->referencia, referencia);

	////gestio del titol:
	//if (titol == NULL || strlen(titol) == 0) {
	//	throw "El títol és obligatori";
	//}
	////Creem espai pel titol:
	//this->titol = new char[strlen(titol) + 1];
	//if (this->titol == NULL) {
	//	throw "no hi ha memoria pel titol de la fitxa";
	//}
	//strcpy(this->titol, titol);

	//Ara el titol és un unique_ptr, per tant, podem utilitzar el setter que ja gestiona la reserva de memòria i la còpia de dades.
	setReferencia(referencia);

	//Gestio de esDeixa:
	setEsDeixa(esDeixa);


}
Fitxa::Fitxa(const char* referencia, const char* titol, bool* esDeixa, Data* dataCreacio) //: titol(NULL), esDeixa(NULL), dataCreacio(NULL)
{
	//Gestio de la referencia
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referencia és obligatoria i de llargada REF_LEN";
	}
	strcpy(this->referencia, referencia);

	//Resto de gestio de dades:
	setTitol(titol);
	setEsDeixa(esDeixa);
	setDataCreacio(dataCreacio);
}


//==================CONSTRUCTOR DE COPIA==================
Fitxa::Fitxa(const Fitxa& fitxa) //: titol(NULL), esDeixa(NULL), dataCreacio(NULL) 
{
	setReferencia(fitxa.referencia);
	setTitol(fitxa.titol.get());
	setEsDeixa(fitxa.esDeixa.get());
	setDataCreacio(fitxa.dataCreacio.get());
	this->dataAlta = fitxa.dataAlta;
}



//==================DESTRUCTOR==================
// No cal destructor perquè no tenim dades dinàmiques gestionades manualment. Els punters intel·ligents s'encarreguen de gestionar la memòria i alliberar-la quan ja no és necessària. Si haguéssim de fer alguna acció específica a l'hora de destruir l'objecte, podríem definir un destructor, però en aquest cas, el destructor per defecte és suficient.
//Fitxa::~Fitxa() {
//	#ifdef DEBUG
//		std::cout << "\t...Alliberant memoria de la fitxa " << this->referencia << "..." << std::endl;
//	#endif // DEBUG
//
//	delete[] titol;
//	delete esDeixa;
//	delete dataCreacio;
//	//Per si el programador invoca el destructor per netejar l'objecte:
//	titol = NULL;
//	esDeixa = NULL;
//	dataCreacio = NULL;
//}



//==================SETTERS==================
void Fitxa::setReferencia(const char* referencia) {
	if (referencia == NULL || strlen(referencia) != REF_LEN) {
		throw "La referència és obligatòria i de llargada REF_LEN [10]";
	}
	strcpy(this->referencia, referencia);
}

void Fitxa::setTitol(const char* titol) {
	if (titol == NULL || strlen(titol) == 0) {
		throw "El títol és obligatori";
	}
	//evitar autoassginació
	if (this->titol.get() == titol) return; //Si el punter apunta a la mateixa adreça, no fem res.

	/*
	if (this->titol != NULL && strlen(this->titol) == strlen(titol)) {
		strcpy(this->titol, titol);
		return;
	}*/
	if (strlen(this->titol.get()) == strlen(titol)) {
		strcpy(this->titol.get(), titol);
		return;
	}
	//Si tenen diferent llargada, reservem nova memoria
	this->titol = make_unique<char[]>(strlen(titol) + 1);
	//Comprovar que s'ha pogut reservar memoria
	if (this->titol == NULL) {
		throw "No hi ha memòria pel títol de la fitxa";
	}
	strcpy(this->titol.get(), titol);	
	/*
	//Si tenen diferent llargada, reservem nova memoria
		char* aux = new char[strlen(titol) + 1];
		if (aux == NULL) {
			throw "No hi ha memòria pel títol de la fitxa";
		}
		delete[]this->titol;
		this->titol = aux;
		strcpy(this->titol, titol);
	*/
}

void Fitxa::setEsDeixa(const bool* esDeixa) {
	//if (esDeixa == NULL) {
	//	delete this->esDeixa;
	//	this->esDeixa = NULL;
	//}
	//else {
	//	if (this->esDeixa == NULL) {
	//		this->esDeixa = new bool;
	//		//Comprovar que s'ha pogut crear memoria
	//		if (this->esDeixa == NULL) {
	//			throw "No s'ha pogut reservar memoria";
	//		}
	//		//this->esDeixa = (bool*)esDeixa; MALAMENT. COPIEM VALORS, NO ADRECES
	//		*(this->esDeixa) = *esDeixa;
	//	}
	//	else {
	//		*(this->esDeixa) = *esDeixa;
	//	}
	//}
	if (this->esDeixa.get() == esDeixa) return; //Si el punter apunta a la mateixa adreça, no fem res.
	if (esDeixa == NULL) {
		this->esDeixa.reset(); //Alliberem la memòria i posem el punter a null
	}
	else {
		if (this->esDeixa == NULL) {
			this->esDeixa = make_unique<bool>(*esDeixa); //Creem un nou bool a partir del valor de esDeixa
			if (this->esDeixa == NULL) throw "No s'ha pogut reservar memoria";
		}
		else {
			*(this->esDeixa) = *esDeixa; //Si ja tenim memoria reservada, només actualitzem el valor.
		}
	}
}

void Fitxa::setDataCreacio(const Data* dataCreacio)
{
	//if (dataCreacio == NULL) {
	//	delete this->dataCreacio;
	//	this->dataCreacio = NULL;
	//}
	//else {
	//	if (this->dataCreacio == NULL) {
	//		//Com que ja hi ha espai reservat, copiem la data directament.
	//		*(this->dataCreacio) = (*dataCreacio);
	//	}
	//	else {
	//		this->dataCreacio = new Data(*dataCreacio);
	//		if (this->dataCreacio == NULL) throw "No s'ha pogut reservar memoria";
	//	}
	//}
	if (this->dataCreacio.get() == dataCreacio) return; //Si el punter apunta a la mateixa adreça, no fem res.
	if (dataCreacio == NULL) {
		this->dataCreacio.reset(); //Alliberem la memòria i posem el punter a null
	}
	else {
		if (this->dataCreacio == NULL) {
			this->dataCreacio = make_unique<Data>(*dataCreacio); //Creem una nova Data a partir del valor de dataCreacio
			if (this->dataCreacio == NULL) throw "No s'ha pogut reservar memoria";
		}
		else {
			*(this->dataCreacio) = *dataCreacio; //Si ja tenim memoria reservada, només actualitzem el valor.
		}
	}
}


//==================GETTERS==================
const char* Fitxa::getReferencia() const { return this->referencia; }
const char* Fitxa::getTitol() const { return this->titol.get(); }		//Hem de cridar el .get() per obtenir l'adreça de memoria.
const bool* Fitxa::getEsDeixa() const { return this->esDeixa.get(); }		//Hem de cridar el .get() per obtenir l'adreça de memoria.
const Data* Fitxa::getDataCreacio() const { return this->dataCreacio.get(); }		//Hem de cridar el .get() per obtenir l'adreça de memoria.
const Data& Fitxa::getDataAlta() const { return this->dataAlta; }


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
	std::cout << "  Data d'alta: " << this->dataAlta << std::endl;;;
	std::cout << "  Data creació: ";
	if (this->dataCreacio == NULL) {
		std::cout << "?" << std::endl;;
	}
	else {
		std::cout << *(this->dataCreacio) << std::endl;;
	}
}

//==================OPERADORS==================
Fitxa& Fitxa::operator=(const Fitxa& fitxa) {
#ifdef DEBUG
	std::cout << "\t*...Usant constructor de copia...*" << this->referencia << "..." << std::endl;
#endif // DEBUG
	setReferencia(fitxa.referencia);
	setTitol(fitxa.titol.get());
	setEsDeixa(fitxa.esDeixa.get());
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



ostream& operator<<(ostream& os, const Fitxa& fitxa)
{
	//Això és ineficient
	//os << "Ref: " << fitxa.getReferencia() << "- Titol: " << fitxa.getTitol();

	//Farem les classes friends per no haver de cridar els getters.
	//(Hem posat 	friend ostream& operator<<(ostream& os, Fitxa& fitxa); al fitxer.h)

	//.h :     friend ostream &operator<<(ostream &os, const Fitxa &fitxa);

	os << "Ref: " << fitxa.referencia << " - Titol: " << fitxa.titol;

	return os;
}
