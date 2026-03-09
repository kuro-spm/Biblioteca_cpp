#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include "Fitxa.h"
#include "Data.h"
#include <memory>

class Biblioteca
{
	friend ostream& operator<<(ostream& os, const Biblioteca& biblioteca);


private:
	char* nom;
	Data dataInauguracio;
	int capacitat;
	int qtatFitxes;
	Fitxa** t;

public:
	//Constructors:
	Biblioteca(const char* nom, const int& capacitat, const Data& dataInauguracio);

	// Regla dels Cinc (Move Semantics)
	Biblioteca(const Biblioteca& biblioteca);            // Constructor de còpia
	Biblioteca(Biblioteca&& biblioteca) noexcept;         // Constructor de MOVIMENT
	Biblioteca& operator=(const Biblioteca& b);           // Operador d'assignació
	Biblioteca& operator=(Biblioteca&& b) noexcept;      // Assignació de MOVIMENT
	
	//Destructor
	//Amb punters normals, necessitem un destructor per alliberar la memòria que hem reservat dinàmicament. Amb punters intel·ligents (smart pointers), el destructor no és estrictament necessari, ja que els smart pointers s'encarreguen de gestionar la memòria automàticament. No obstant això, si tenim altres recursos a gestionar (com fitxers o connexions de xarxa), podríem necessitar un destructor per alliberar aquests recursos. En aquest cas, com només tenim punters intel·ligents, el destructor pot ser buit o fins i tot no ser declarat explícitament, ja que el compilador generarà un destructor per defecte que farà el treball adequadament.
	~Biblioteca(); 

	//Getters i setters
	//Setters
	void setNom(const char* nom);
	void setCapacitat(const int& capacitat);
	void setDataInauguracio(const Data& dataInauguracio);

	//Getters
	const char* getNom() const;                
	const Data& getDataInauguracio() const;    
	const int& getCapacitat() const;                   
	const int& getQtatFitxes() const;                 
	const Fitxa** getFitxes() const;          
	/*const Data&, està retornant un "àlies" a l'objecte original que 
	ja existeix dins de la biblioteca. És instantani. El const garanteix 
	que, encara que tinguin accés a l'original, no el puguin modificar.*/

	//Altres mètodes
	bool afegirFitxa(const Fitxa* fitxa);
	Fitxa& cercarFitxa(const char* referencia);
	void actualitzarFitxa(const Fitxa* fitxa);
	Fitxa* extreureFitxa(const char* referencia);

	void visualitzar(ostream& os);
};



#endif
