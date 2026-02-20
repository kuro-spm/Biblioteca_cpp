# Biblioteca.cpp
Aquest projecte s’ha fet com a part de la assignatura de Programació Estructurada i Modular (PEM) del cicle de Desenvolupament d’Aplicacions Multiplataforma en l’institud Milà i Fontanals d’Igualada, per tal d’aprendre com fer una correcta gestió de classes en C++.

El projecte consta de les classes Fitxa, Data i Biblioteca.
Una biblioteca està composada de fitxes.
Les Fitxes i la Biblioteca contenen Dates.

A continuació es presenten uns quants apunts -que serviràn també per estudiar-
# 1 La Regla dels Tres (Rule of Three)
Si una classe gestiona memòria dinàmica (punters com `char*` o `Fitxa**`), el compilador no sap "copiar" o "esborrar" correctament l'objecte per si sol. És necessari implementar:
Destructor: Allibera la memòria amb `delete` o `delete[]` per evitar fuites de memòria (memory leaks).
Constructor de Còpia: Serveix per crear un objecte nou com a còpia d'un existent. En lloc de copiar l'adreça del punter (còpia superficial) tal i com fa el constructor còpia per defecte, és necessari fer una còpia profunda reservant nova memòria.
Operador d'Assignació (operator=): Semblant al constructor de còpia, però s'usa quan l'objecte ja existeix. 



# 2 Estratègies de Gestió de Memòria
Quan una classe ha de gestionar dades complexes (com Data o cadenes de caràcters), triem l'estratègia segons qui hagi de ser el propietari de la informació:
Guardar el valor: S'utilitza quan vols que l'objecte tingui la seva pròpia còpia independent de les dades. Podem fer deep copy si és un punter o còpia directa.
Guardar un punter al valor:  S'utilitza quan només vols apuntar a una informació que ja existeix en un altre lloc i que no vols duplicar. Exemple: relacions temporals. Perill: Dangling Pointers.

## 2.1 Objecte Directe (Còpia per Valor)
És l'opció més senzilla i segura. L'atribut no és un punter, sinó l'objecte mateix (com Data dataInauguracio;).
Quan fer-la: Per a objectes amb una mida fixa o coneguda (com la classe Data).
Com funciona: Es defineix l'atribut directament pel seu tipus (ex: Data dataAlta;). C++ gestiona la còpia automàticament usant el constructor de còpia intern de la classe.
Propietat: La classe és la propietària total.
Avantatges: No cal fer new ni delete manualment, evitant errors humans i fuites de memòria.

## 2.2 Còpia Profunda (Deep Copy)
S'utilitza quan vols que l'objecte tingui la seva pròpia còpia independent de les dades situades al heap.
Quan fer-la: Obligatori per a cadenes de text dinàmiques (char*) i quan l'objecte ha de ser l'amo de la informació (com char* nom o Fitxa** t).
Perill de no fer-la: Si només copies l'adreça i l'original s'esborra, el teu punter quedarà apuntant a memòria brossa (dangling pointer).
Propietat: La classe és la propietària i té l'obligació d'alliberar la memòria al destructor.
### 2.2.1 🛠️ Implementació Segura (en Setters i Constructors)
Per evitar que l'objecte quedi corrupte si falla la memòria, segueix aquests passos:
Validar: Comprovar que les dades d'entrada són correctes (ex: que el nom no sigui NULL).
Reservar espai (Auxiliar): Crear un punter temporal (ex: char* aux) i fer el new. Si el sistema es queda sense memòria, el programa llançarà una excepció aquí, però el teu atribut original seguirà intacte.
Copiar dades: Omplir aquest espai auxiliar amb la informació (usant strcpy per a textos o el constructor de còpia per a objectes).
Alliberar i Reassignar: Només quan la còpia ha anat bé, fem delete de l'atribut antic i assignem el nou punter (this->nom = aux;).

## 2.3 Còpia Superficial (Shallow Copy / Punter Simple)
Es tracta de guardar només l'adreça de memòria, sense duplicar la informació.
Com funciona: S'assigna directament l'adreça rebuda: this->ptr = ptrOriginal;.
Quan fer-la: Per a relacions temporals (agregacions) on només vols "apuntar" a informació que gestiona un altre lloc del programa.
Perills: * Dangling Pointers: Si l'amo original esborra les dades, el teu objecte "peta" en intentar accedir-hi.
Modificacions externes: Si algú canvia la informació des de fora, el teu objecte veurà el canvi encara que no ho vulgui.


