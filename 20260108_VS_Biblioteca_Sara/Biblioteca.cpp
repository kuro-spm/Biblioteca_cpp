#include "Biblioteca.h"
#include "Data.h"

ostream& operator<<(ostream& os, Biblioteca& biblioteca)
{
	// TODO: Insertar una instrucción "return" aquí
}


Biblioteca::Biblioteca(const char* nom, const int& capacitat, const Data& dataInauguracio) :
	nom(NULL), dataInauguracio(dataInauguracio), capacitat(capacitat), qtatFitxes(0), t(NULL)
{
	//Gestio del nom:
	if (nom == NULL || strlen(nom) == 0) {
		throw "El nom de la biblioteca és obligatori";
	}
	//Creem espai pel nom:
	setNom(nom);

	//Gestio de la capacitat:
	setCapacitat(capacitat);
	this->capacitat = capacitat;
	//Inicialitzem el vector de fitxes a null
	this->t = NULL;
}

//==================CONSTRUCTOR CÒPIA==================
Biblioteca::Biblioteca(const Biblioteca& biblioteca)
{
}

//==================OPERADORS==================
Biblioteca& Biblioteca::operator=(const Biblioteca& b)
{
	// TODO: Insertar una instrucción "return" aquí
}

//==================DESTRUCTOR==================
Biblioteca::~Biblioteca()
{
}




//==================SETTERS==================
void Biblioteca::setNom(const char* nom)
{
	if (nom == NULL || strlen(nom) == 0) {
		throw "El nom de la biblioteca és obligatori";
	}
	if (this->nom != NULL && strlen(nom)==strlen(this->nom)) {
		strcpy(this->nom, nom);

	}
	else {
		// Creem espai pel nou nom:
		char* nomAux = new char[strlen(nom) + 1];
		if (nomAux == NULL) {
			throw "No hi ha memòria pel nom de la biblioteca";
		}
		//Hem d'alliberar el nom anterior
		delete[] this->nom;
		this->nom = nomAux;
		strcpy(this->nom, nom);
	}
}

void Biblioteca::setCapacitat(const int& capacitat)
{
	if (capacitat <= 0) {
		throw "La capacitat de la biblioteca ha de ser positiva";
	}
	if (capacitat < this->qtatFitxes) {
		throw "La capacitat de la biblioteca no pot ser inferior a la quantitat de fitxes que conté";
	}
	if (capacitat == capacitat) {
		return;
	}
	//else if (capacitat != this->capacitat) {
	//Si la capacitat és diferent a l'actual, hem de redimensionar el vector de fitxes.
	Fitxa** tAux = new Fitxa * [capacitat];
	if (tAux == NULL) {
		throw "No hi ha memòria per redimensionar el vector de fitxes de la biblioteca";
	}
	//Copiem les adreces de les fitxes al nou vector
	for (int i = 0; i < this->qtatFitxes; i++) {
		tAux[i] = this->t[i];
	}
	//Alliberem el vector anterior
	delete[] this->t;
	//Assignem el nou vector a la biblioteca
	this->t = tAux;
	this->capacitat = capacitat;


}

void Biblioteca::setDataInauguracio(const Data& dataInauguracio)
{
	this->dataInauguracio = dataInauguracio;
}


//==================GETTERS==================

const char* Biblioteca::getNom()
{
	return nullptr;
}

const Data& Biblioteca::getDataInauguracio()
{
	// TODO: Insertar una instrucción "return" aquí
}

const int Biblioteca::getCapacitat()
{
	// TODO: Insertar una instrucción "return" aquí
}

const int Biblioteca::getQtatFitxes()
{
	return 0;
}

const Fitxa& Biblioteca::getFitxes()
{
	// TODO: Insertar una instrucción "return" aquí
}




//==================ALTRES MÈTODES==================

bool Biblioteca::afegirFitxa(const Fitxa* fitxa)
{
}

Fitxa& Biblioteca::cercarFitxa(const char* referencia)
{
	// TODO: Insertar una instrucción "return" aquí
}

void Biblioteca::eliminarFitxa(const char* referencia)
{
}

void Biblioteca::actualitzarFitxa(const Fitxa* fitxa)
{
}

Fitxa* Biblioteca::extreureFitxa(const char* referencia)
{
	return nullptr;
}

void Biblioteca::visualitzar()
{
}
