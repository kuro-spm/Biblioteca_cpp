#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include "Fitxa.h"
#include "Data.h"



class Biblioteca
{
	friend ostream& operator<<(ostream& os, Biblioteca& biblioteca);

private:
	char *nom;
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
	Biblioteca& operator=(const Biblioteca& b); //Asignació (imprescindible <=> dades dinàmiques)

	//Destructor
	~Biblioteca(); //Destructor (imprescindible <=> dades dinàmiques)

	//Getters i setters
	//Setters
	void setNom(const char* nom);
	void setCapacitat(const int& capacitat);
	void setDataInauguracio(const Data& dataInauguracio);

	//Getters
	const char* getNom();
	//S'utilitza & per eficiència amb objectes complexos.
	const Data& getDataInauguracio();
	const int getCapacitat();
	const int getQtatFitxes();
	const Fitxa& getFitxes();
	/*const Data&, està retornant un "àlies" a l'objecte original que 
	ja existeix dins de la biblioteca. És instantani. El const garanteix 
	que, encara que tinguin accés a l'original, no el puguin modificar.*/

	//Altres mètodes
	bool afegirFitxa(const Fitxa* fitxa);
	Fitxa& cercarFitxa(const char* referencia);
	void eliminarFitxa(const char* referencia);
	void actualitzarFitxa(const Fitxa* fitxa);
	Fitxa* extreureFitxa(const char* referencia);

	void visualitzar();
};

#endif
