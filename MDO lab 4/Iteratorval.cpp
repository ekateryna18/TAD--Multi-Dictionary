#include "MDO.h"
#include "Iteratorval.h"
#include <exception>
/*
* pseudocod:
* subalgoritm constructor(dict,cheie)
*	{daca nu exista cheia in dictionar, nu se creeaza iteratorul}
*	{daca exista cheia, se creeaza iteratorul}
*	index <- dict.prim
*	cat timp index != -1
*		daca cheie de dict.e[index] == cheie
*			curent <- index
*			sf subalgoritm
*		index <- d.urm[index]
* sfsubalgoritm
*/
//complexitate Theta(dimensiune dictionar)
IteratorValori::IteratorValori(const MDO& d, TCheie cheie) : dict(d), cheie(cheie) {
	int index = d.prim;
	while (index != -1) {
		if (d.e[index].first == cheie) {
			curent = index;
			return;
		}
		index = d.urm[index];
	}
	//nu a fost gasit => iterator invalid
	curent = -1;
}

/* pseudocod
* subalgoritm prim(dict, cheie)
*	{daca nu este valid iteratorul, arunca exceptie}
*	{daca este valid, se cauta prima aparitie a cheii in multidictionar}
*	daca iteratorul nu este valid
*		arunca exceptie
*		sfalgoritm
*	index <- dict.prim
*	cat timp index != -1
*		daca cheie de dict.e[index] == cheie
*			curent <- index
*			sf subalgoritm
*		index <- d.urm[index]
* sfalgoritm
*/
//complexitate Theta(dimensiune dictionar)
void IteratorValori::prim() {
	if (!valid()) {
		throw exception();
	}

	int index = dict.prim;
	while (index != -1) {
		if (dict.e[index].first == cheie) {
			curent = index;
			return;
		}
		index = dict.urm[index];
	}
}

/* pseudocod
* subalgoritm urmator(dict, cheie)
*	{daca nu este valid iteratorul, arunca exceptie}
*	{se verifica daca exista o urmatoare valoare pentru cheie, iar daca exista se trece la aceasta}
*	daca iteratorul nu este valid
*		arunca exceptie
*		sfalgoritm
*	next <- dict.urm[curent]
*	
*	daca cheie de dict.e[index] == cheie
*		curent <- next
*	altfel curent = -1
* sfalgoritm
*/
//complexitate Theta(1)
void IteratorValori::urmator() {
	if (!valid()) {
		throw exception();
	}
	int next = dict.urm[curent];
	if (dict.e[next].first == cheie) {
		curent = next;
	}
	else
		curent = -1;
}

/* pseudocod
* subalgoritm valid(dict, cheie)
*	{daca pozitia curenta nu este -1, iteratorul este valid}
*	{altfel, acesta este invalid}
*	daca curent != -1
*		return true
*	return false
* sfalgoritm
*/
//complexitate Theta(1)
bool IteratorValori::valid() const {
	if (curent != -1)
		return true;
	return false;
}

/*
* pseudocod 
* subalgortim element(dict,cheie)
* {returneaza valoarea curenta}
*	return valoare de dict.e[curent]
* sfalgoritm
*/

//complexitate Theta(1)
TValoare IteratorValori::element() const {
	return dict.e[curent].second;
}