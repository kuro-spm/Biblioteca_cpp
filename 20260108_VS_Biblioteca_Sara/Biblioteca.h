#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#define REF_LEN 10
#include "Fitxa.h"
#include "Data.h"



class Biblioteca
{
	friend ostream& operator<<(ostream& os, Biblioteca& biblioteca);

private:
	char nom[REF_LEN + 1];
	Data dataInauguracio;
	int capacitat;
	int qtatFitxes;
	Fitxa** t;

public:
	//Constructors:
	Biblioteca(const char* nom, const int& capacitat, const Data& dataInauguracio);

	//Constructor de copia
	Biblioteca(const Biblioteca& biblioteca); //Copia (imprescindible <=> dades dinàmiques)

	//Operadors
	Biblioteca &operator=(const Biblioteca& b); //Asignació (imprescindible <=> dades dinàmiques)

	//Destructor
	~Biblioteca(); //Destructor (imprescindible <=> dades dinàmiques)

	//Getters i setters
	//Setters
	void setNom(const char* nom);
	void setDataInauguracio(const Data* dataInauguracio);

	//Getters
	const char* getNom();
	const Data* getDataInauguracio();
	const int getCapacitat();
	const int getQtatFitxes();
	const Fitxa** getFitxes();

	//Altres mètodes
	void afegirFitxa(const Fitxa* fitxa);
	Fitxa& cercarFitxa(const char* referencia);
	void eliminarFitxa(const char* referencia);
	void actualitzarFitxa(const Fitxa* fitxa);

	void visualitzar();
};

#endif
