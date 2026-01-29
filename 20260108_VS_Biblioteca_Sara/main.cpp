#include "fitxa.h"
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

// --- MAIN PRINCIPAL ---
int main(int argc, char** argv) {
    try {
        bool esDeixa = true;
        Fitxa* f1 = new Fitxa("0123456789", "El camino de los reyes", &esDeixa);

        std::cout << *f1 << std::endl;
        delete f1; // Bona pràctica: alliberar memòria
    }
    catch (const char* missatge) {
        cout << "Error: " << missatge << endl;
    }
    return 0;
}

// --- COMPARADORS ---
int main_comparadors(int argc, char** argv) {
    try {
        bool esDeixa = true;
        Fitxa* f1 = new Fitxa("0123456789", "Titol1", &esDeixa);
        std::cout << "==========Fitxa f1==========" << std::endl;
        f1->visualitzar();

        Fitxa* f2 = new Fitxa("0123456789", "Titol2", &esDeixa);
        std::cout << "==========Fitxa f2==========" << std::endl;
        f2->visualitzar();

        printf("\n");

        if ((*f1) == (*f2)) {
            std::cout << "Les fitxes son iguals" << std::endl;
        }
        else {
            std::cout << "Les fitxes son diferents" << std::endl;
        }

        delete f1;
        delete f2;
    }
    catch (const char* missatge) {
        cout << "Error: " << missatge << endl;
    }
    return 0;
}

// --- COPIES I DESTRUCTORS ---
int main_copia_destructors(int argc, char** argv) {
    try {
        bool esDeixa = true;
        Fitxa* f1 = new Fitxa("0123456789", "Titol", &esDeixa);
        std::cout << "==========Fitxa f1==========" << std::endl;
        f1->visualitzar();

        // Primer copiem, DESPRÉS borrem
        Fitxa f3(*f1);
        std::cout << "==========Fitxa f3 (copia de f1)==========" << std::endl;
        f3.visualitzar();

        delete f1;
        f1 = NULL; // Recordatori: Sempre a NULL després de delete

        Fitxa f2;
        std::cout << "==========Fitxa f2 (per defecte)==========" << std::endl;
        f2.visualitzar();
    }
    catch (const char* missatge) {
        cout << "Error: " << missatge << endl;
    }
    return 0;
}

// --- ANTIC MAIN ---
int old_main(int argc, char** argv) {
    try {
        Fitxa fest("0123456789", "Titol"); // Fitxa estàtica
        cout << "S'ha creat la fitxa 111" << endl;
        cout << "Fitxa fest: " << endl;
        cout << "  Referencia: " << fest.getReferencia() << endl;
        cout << "  Títol: " << fest.getTitol() << endl;
        cout << "  Es deixa?: " << fest.getEsDeixa() << endl;

        Fitxa* fdin = new Fitxa(); // Fitxa dinàmica
        printf("Operacions exitoses!");
        delete fdin;
    }
    catch (const char* missatge) {
        cout << "No s'ha pogut crear la fitxa" << endl;
        cout << "Error: " << missatge << endl;
    }
    return 0;
}