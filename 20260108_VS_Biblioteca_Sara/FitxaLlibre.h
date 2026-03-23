#pragma once
#include "Fitxa.h"

#define ISBN_LEN 13
#define ISBN10_LEN 10


class FitxaLlibre :
    public Fitxa
{
    char* editorial; //no obligatori
	char isbn[ISBN_LEN + 1]; //no obligatori

public:
    FitxaLlibre();
    FitxaLlibre(const char* referencia, const char* titol, const char* editorial, const char* isbn);
    FitxaLlibre(const FitxaLlibre& fitxa);

    FitxaLlibre& operator = (const FitxaLlibre& fitxa);

    ~FitxaLlibre();

    void setEditorial(const char* editorial);
    void setIsbn(const char* isbn);
    const char* getEditorial() const;
    const char* getIsbn() const;

	void visualitzar();


};

