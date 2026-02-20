#include "Biblioteca.h"
#include "Data.h"

ostream& operator<<(ostream& os, Biblioteca& biblioteca)
{
	// TODO: Insertar una instrucción "return" aquí
}


Biblioteca::Biblioteca(const char* nom, const int& capacitat, const Data& dataInauguracio) :
	nom(NULL), dataInauguracio(dataInauguracio), capacitat(0), qtatFitxes(0), t(NULL)
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
///El constructor de còpia és imprescindible quan tenim dades dinàmiques, ja que el constructor per defecte faria una còpia superficial (shallow copy) i compartiríem les mateixes adreces de memòria, cosa que podria provocar problemes com la doble alliberació de memòria (double free) o modificacions no desitjades en les dades compartides. Amb el constructor de còpia personalitzat, podem assegurar-nos que cada objecte té la seva pròpia còpia de les dades dinàmiques, evitant aquests problemes i garantint un comportament correcte del programa.
Biblioteca::Biblioteca(const Biblioteca& biblioteca) :
	nom(NULL), dataInauguracio(dataInauguracio), capacitat(0), qtatFitxes(0), t(NULL)
{
	setNom(biblioteca.nom);
	setCapacitat(biblioteca.capacitat);
	//TODO assegurar que si peta, no deixi la biblioteca en un estat inconsistent. Per exemple, si no es pot reservar memòria pel nom, no hauria de continuar intentant copiar les fitxes.
	for (int i = 0; i < biblioteca.qtatFitxes; i++) {
		t[i] = new Fitxa(*(biblioteca.t[i]));
		//afegirFitxa(biblioteca.t[i]);
	}
	qtatFitxes = biblioteca.qtatFitxes;
}

//==================OPERADORS==================
Biblioteca& Biblioteca::operator=(const Biblioteca& b)
{
	throw "No es permet l'assignació de biblioteques.";
}

//==================DESTRUCTOR==================
Biblioteca::~Biblioteca()
{
	delete[] nom;    
	//Asssumim que les fitxes les gestiona la biblioteca, per tant, hem d'alliberar la memòria de cada fitxa abans d'alliberar el vector de punters a fitxes.
	for (int i = 0; i < qtatFitxes; i++) {
		delete t[i];
	}
	delete[] t;       
	nom = NULL;
	t = NULL;
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

const char* Biblioteca::getNom() const { return nom; }
const Data& Biblioteca::getDataInauguracio() const { return dataInauguracio; }
int Biblioteca::getCapacitat() const { return capacitat; }
int Biblioteca::getQtatFitxes() const { return qtatFitxes; }
const Fitxa** Biblioteca::getFitxes() const { return (const Fitxa**)t; }




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

void Biblioteca::visualitzar(ostream &os)
{
	os << "Nom: " << this->getNom() << std::endl;
	os << "Data d'inauguració: " << this->dataInauguracio << std::endl;
	os << "Capacitat: " << this->getCapacitat() << std::endl;
	os << "Quantitat de fitxes: " << this->getQtatFitxes() << std::endl;
	if (qtatFitxes > 0) {
		os << "Fitxes:" << std::endl;
		for (int i = 0; i < this->qtatFitxes; i++) {
			os << "\t" << *(this->t[i]) << std::endl;
		}
	}
	else {
		os << "No hi ha fitxes a la biblioteca." << std::endl;
	}

	
}
