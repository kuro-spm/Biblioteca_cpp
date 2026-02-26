#include "Biblioteca.h"
#include "Data.h"




Biblioteca::Biblioteca(const char* nom, const int& capacitat, const Data& dataInauguracio) :
	nom(NULL), dataInauguracio(dataInauguracio), capacitat(0), qtatFitxes(0), t(NULL)
{
	setNom(nom);
	setCapacitat(capacitat);

}

//==================CONSTRUCTOR CÒPIA==================
///El constructor de còpia és imprescindible quan tenim dades dinàmiques, ja que el constructor per defecte faria una còpia superficial (shallow copy) i compartiríem les mateixes adreces de memòria, cosa que podria provocar problemes com la doble alliberació de memòria (double free) o modificacions no desitjades en les dades compartides. Amb el constructor de còpia personalitzat, podem assegurar-nos que cada objecte té la seva pròpia còpia de les dades dinàmiques, evitant aquests problemes i garantint un comportament correcte del programa.
Biblioteca::Biblioteca(const Biblioteca& biblioteca) :
	nom(NULL), dataInauguracio(biblioteca.dataInauguracio), capacitat(0), qtatFitxes(0), t(NULL)
{
	setNom(biblioteca.nom);
	try {
		setCapacitat(biblioteca.capacitat);
	}
	catch (const char* ex) {
		delete[] nom; //Alliberem el nom que ja hem copiat
		nom = NULL;
		throw "Error de memòria en copiar biblioteca";
	}
	for (int i = 0; i < biblioteca.qtatFitxes; i++) {
		try {
			t[i] = new Fitxa(*(biblioteca.t[i])); //Cada fitxa és ara de la biblioteca, per tant, hem de crear una nova fitxa a partir de la fitxa original. Això és un procés de còpia profunda (deep copy).
			//afegirFitxa(biblioteca.t[i]);
			if (t[i] == NULL) {
				throw "No hi ha memòria per copiar una fitxa de la biblioteca";
			}
		}
		catch (const char* ex) {
			//Si no es pot copiar una fitxa, hem d'alliberar les fitxes que ja hem copiat i el nom, i deixar la biblioteca en un estat consistent (per exemple, amb 0 fitxes i nom NULL).
			for (int j = 0; j < i; j++) {
				delete t[j];
			}
			delete[] t;
			t = NULL;
			delete[] nom;
			nom = NULL;
			throw "Error de memòria en copiar biblioteca"; //Re-llançar l'excepció perquè el constructor de còpia també falli.
		}
	}
	qtatFitxes = biblioteca.qtatFitxes;
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
	// Opcional? però aconsellable:
	nom = NULL;
	t = NULL;
	capacitat = 0;
	qtatFitxes = 0;
}




//==================SETTERS==================
void Biblioteca::setNom(const char* nom)
{
	// 1. Validar
	if (nom == NULL || strlen(nom) == 0) {
		throw "El nom de la biblioteca és obligatori";
	}
	if (this->nom != NULL && strlen(this->nom) == strlen(nom)) {
		strcpy(this->nom, nom);
	}
	else {
	// 2. Reservar espai en una variable auxiliar
	char* nomAux = new char[strlen(nom) + 1];

	// (Si 'new' fallés aquí, el mètode s'aturaria i 'this->nom' no s'hauria esborrat)
	if (nomAux == NULL) {
		throw "No hi ha memòria pel títol de la fitxa";
	}
	// 3. Copiar dades a l'auxiliar
	strcpy(nomAux, nom);

	// 4. Alliberar l'antic i reassignar
	delete[] this->nom;
	this->nom = nomAux;

	}
}

void Biblioteca::setCapacitat(const int& capacitat)
{
	if (capacitat <= 0) throw "La capacitat de la biblioteca ha de ser positiva";
	if (capacitat < this->qtatFitxes) throw "La capacitat no pot ser inferior a les fitxes actuals";
	if (capacitat == this->capacitat) return;

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
	//Intercanvi
	delete[] this->t;
	this->t = tAux;
	this->capacitat = capacitat;


}

void Biblioteca::setDataInauguracio(const Data& dataInauguracio)
{
	this->dataInauguracio = dataInauguracio;
	//C++ invoca automàticament el constructor de còpia de Data.
}


//==================GETTERS==================

const char* Biblioteca::getNom() const { return nom; }
const Data& Biblioteca::getDataInauguracio() const { return dataInauguracio; }
const int& Biblioteca::getCapacitat() const { return capacitat; }
const int& Biblioteca::getQtatFitxes() const { return qtatFitxes; }
const Fitxa** Biblioteca::getFitxes() const { return (const Fitxa**)t; }


//==================OPERADORS==================
Biblioteca& Biblioteca::operator=(const Biblioteca& b)
{
	throw "No es permet l'assignació de biblioteques.";
}

ostream& operator<<(ostream& os, const Biblioteca& biblioteca)
{
	os << "Nom: " << biblioteca.getNom() << std::endl;
	os << "Data d'inauguració: " << biblioteca.getDataInauguracio() << std::endl;
	os << "Capacitat: " << biblioteca.getCapacitat() << std::endl;
	os << "Quantitat de fitxes: " << biblioteca.getQtatFitxes() << std::endl;
	os << "Fitxes:" << std::endl;
	for (int i = 0; i < biblioteca.getQtatFitxes(); i++) {
		os << "\t" << *(biblioteca.t[i]) << std::endl;
	}
	return os;

}


//==================ALTRES MÈTODES==================

/// <summary>
/// Mètode que afegeix una fitxa a la biblioteca i retorna true si s'ha afegit correctament. La taula resultant ha d'estar ordenada. 
/// Si la fitxa és NULL o si la biblioteca ha arribat a la seva capacitat màxima de fitxes, llança una excepció amb un missatge d'error adequat.
/// </summary>
/// <param name="fitxa">És la fitxa a afegir</param>
/// <returns></returns>
bool Biblioteca::afegirFitxa(const Fitxa* fitxa)
{
	if (fitxa == NULL) {
		throw "La fitxa a afegir no pot ser NULL";
	}
	if (qtatFitxes >= capacitat) {
		throw "La biblioteca ha arribat a la seva capacitat màxima de fitxes";
	}
	//Busquem la posició on s'ha d'inserir la nova fitxa per mantenir l'ordre
	int i = 0;
	while (i < qtatFitxes && strcmp(t[i]->getReferencia(), fitxa->getReferencia()) < 0) {
		if (i < qtatFitxes&& strcmp(t[i]->getReferencia(), fitxa->getReferencia()) == 0) {
			throw "Ja existeix una fitxa amb la mateixa referencia a la biblioteca";
		}
		i++;
	}
	//Desplacem les fitxes a la dreta per fer espai a la nova fitxa --> SEGUR EXAMEN
	for (int j = qtatFitxes; j > i; j--) {
		t[j] = t[j - 1];
	}
	//Inserim la nova fitxa a la posició correcta
	t[i] = (Fitxa*) new Fitxa(*fitxa); //Creem una nova fitxa a partir de la fitxa original per evitar compartir la mateixa adreça de memòria. Això és un procés de còpia profunda (deep copy).
	if (t[i] == NULL) {
		throw "No hi ha memòria per afegir la nova fitxa a la biblioteca";
	}
	qtatFitxes++;
	return true;
}


/// <summary>
/// Busca una fitxa por su referencia en la biblioteca y devuelve una referencia a la fitxa encontrada. Lanza una excepción si la referencia es NULL o vacía, o si no se encuentra la fitxa.
/// </summary>
/// <param name="referencia">Cadena C que identifica la referencia de la fitxa. No puede ser NULL ni estar vacía; si lo es, la función lanza una excepción (const char*).</param>
/// <returns>Referencia a la Fitxa (Fitxa&) correspondiente a la referencia proporcionada. Si no existe ninguna fitxa con esa referencia, la función lanza una excepción (const char*).</returns>
Fitxa& Biblioteca::cercarFitxa(const char* referencia)
{
	if (referencia == NULL || strlen(referencia) == 0) {
		throw "La referencia de la fitxa a cercar no pot ser NULL o buida";
	}
	int i = 0;
	while (i < qtatFitxes && strcmp(t[i]->getReferencia(), referencia) < 0) {
		if (i < qtatFitxes && strcmp(t[i]->getReferencia(), referencia) == 0) {
			return *(t[i]);
		}
		i++;
	}
	throw "No s'ha trobat cap fitxa amb la referencia indicada";
}



void Biblioteca::actualitzarFitxa(const Fitxa* fitxa)
{
	if (fitxa == NULL) {
		throw "La fitxa proporcionada és nul·la";
	}
	//Busquem la fitxa dins del nostre vector 't' (que és un Fitxa**)
	// Com que cercarFitxa retorna una Fitxa&, n'obtenim l'adreça amb '&'
	Fitxa* fitxaDinsBiblioteca = &cercarFitxa(fitxa->getReferencia());

	// 3. Ara que tenim el punter, fem l'assignació.
	*fitxaDinsBiblioteca = *fitxa;
}

Fitxa* Biblioteca::extreureFitxa(const char* referencia)
{
	if (referencia == NULL || strlen(referencia) == 0) {
		throw "La referencia de la fitxa a extreure no pot ser NULL o buida";
	}
	int i = 0;
	for (i = 0; i < qtatFitxes && strcmp(t[i]->getReferencia(), referencia) < 0; i++) {
		if (i < qtatFitxes && strcmp(t[i]->getReferencia(), referencia) == 0) {
			Fitxa* fitxaExtreta = t[i];
			//Desplacem les fitxes a la esquerra per omplir l'espai deixat per la fitxa extreta
			for (int j = i; j < qtatFitxes - 1; j++) {
				t[j] = t[j + 1];
			}
			t[qtatFitxes - 1] = NULL; //Opcional: posar a NULL la última posición del vector después de desplazar las fitxes
			qtatFitxes--;
			return fitxaExtreta;
		}
		else {
			return NULL; //Si no se encuentra la fitxa, se devuelve NULL en lugar de lanzar una excepción. Esto es una decisión de diseño que puede variar según las necesidades del programa.
		}
	}
}

void Biblioteca::visualitzar(ostream& os)
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
