#include "FitxaLlibre.h"

//==================== CONSTRUCTORS, DESTRUCTOR AND OPERATOR= ====================

FitxaLlibre::FitxaLlibre(): Fitxa(), editorial(NULL)
{
	memset(isbn, 0, sizeof(isbn)); //Inicialitzar tot l'array a 0. Això és equivalent a posar isbn[0] = '\0', però assegura que tot l'array està net.
}

FitxaLlibre::FitxaLlibre(const char* referencia, const char* titol, const char* editorial, const char* isbn): Fitxa(referencia, titol), editorial(NULL)
{
	setEditorial(editorial);
	setIsbn(isbn);
}

FitxaLlibre::FitxaLlibre(const FitxaLlibre& fitxa): Fitxa(fitxa), editorial(NULL)
{
	setEditorial(fitxa.editorial);
	setIsbn(fitxa.isbn);
}

FitxaLlibre& FitxaLlibre::operator=(const FitxaLlibre& fitxa)
{
	Fitxa::operator=(fitxa);
	setEditorial(fitxa.editorial);
	setIsbn(fitxa.isbn);
	return *this;
}

FitxaLlibre::~FitxaLlibre()
{
	delete[] editorial;
	editorial = NULL;
}

//==================== SETTERS ====================
void FitxaLlibre::setEditorial(const char* editorial)
{
	if (editorial == NULL || strlen(editorial) == 0) {
		delete[] this->editorial;
		this->editorial = NULL;
		return;
	}
	if (this->editorial == editorial) return; //Si el punter apunta a la mateixa adreça, no fem res.

	if (this->editorial != NULL) {
		//Si el contingut és el mateix, no fem res. Això és una optimització per evitar fer una còpia innecessària si el contingut no ha canviat.
		if(strlen(this->editorial)==strlen(editorial)) {
			if (strcmp(this->editorial, editorial) == 0) {
				return; //Si el contingut és el mateix, no fem res.
			}
			else {
				//Si el contingut és diferent, actualitzem l'editorial. En aquest cas, com que ja tenim una cadena al·locada, podem reutilitzar-la si la nova cadena té la mateixa longitud o menys. Si la nova cadena és més llarga, haurem de tornar a al·locar.
				delete[] this->editorial;
				this->editorial = new char[strlen(editorial) + 1];
				if (this->editorial == NULL) {
					throw "No hi ha memoria per l'editorial de la fitxa";
				}
				strcpy(this->editorial, editorial);
			}

		}
	}
	else {
		//Si no tenim cap cadena al·locada, simplement al·loquem i copiem el nou contingut.
		this->editorial = new char[strlen(editorial) + 1];
		if (this->editorial == NULL) {
			throw "No hi ha memoria per l'editorial de la fitxa";
		}
		strcpy(this->editorial, editorial);
	}
}


void FitxaLlibre::setIsbn(const char* isbn)
{
	if (strlen(isbn)!=0 && strlen(isbn)!=ISBN10_LEN && strlen(isbn) != ISBN_LEN) {
		throw "L'ISBN ha de tenir 10 o 13 caràcters, o ser buit.";
	}
	strcpy(this->isbn, isbn);
}

//==================== GETTERS ====================
const char* FitxaLlibre::getEditorial() const
{
	return editorial;
}

const char* FitxaLlibre::getIsbn() const
{
	return isbn;
}

//==================== VISUALITZAR ====================
void FitxaLlibre::visualitzar()
{
	Fitxa::visualitzar();
	cout << "Editorial: " << (editorial != NULL ? editorial : "No especificada") << endl;
	cout << "ISBN: " << (strlen(isbn) > 0 ? isbn : "No especificat") << endl;
}

