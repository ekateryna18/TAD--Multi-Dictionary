#pragma once

#include "MDO.h"

/*pseudocod IteratorValori
* dict: MDO - multidictionarul orodnat
*cheie: TCheie - numar intreg, valoarea cheii peste care 
*				se itereaza
*curent: Intreg - indexul iteratorului
*/
class IteratorValori {
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorValori(const MDO& dictionar, TCheie cheie);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;

	TCheie cheie;
	/* aici e reprezentarea  specifica a iteratorului */
	int curent;

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TValoare element() const;
};