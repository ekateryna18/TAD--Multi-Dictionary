#include "IteratorMDO.h"
#include "Iteratorval.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//constructor
//complexitate Theta(1)
MDO::MDO(Relatie r) {
	prim = -1;
	ultim = -1;
	prim_liber = 0;
	e = new TElem[cp];
	urm = new int[cp];
	prec = new int[cp];
	for (int i = 0;i < cp-1;i++)
		urm[i] = i + 1;
	urm[cp - 1] = -1;
	rel = r;
}

//caz favorabil: complexitate Theta(1),daca dictionarul este gol
//caz defavorabil: complexitate Theta(dimensiune), trebuie cautat unde se respecta relatia pentru element pentru a fi adaugat
//caz mediu: complexitate Theta(dimensiune)
void MDO::adauga(TCheie c, TValoare v) {
	//creeam elementul
	TElem elem;
	elem.first = c;
	elem.second = v;
	int poz = creeazaNod(elem);
	//daca dictionarul este gol, adaugam elementul la inceput
	if (this->dimensiune == 0) {
		prec[poz] = -1;
		urm[poz] = -1;
		prim = poz;
		ultim = poz;
		this->dimensiune++;
		return;
	}
	//altfel cautam sa adaugam elementul unde se respecta relatia
	int i = this->prim;
	//verificam daca elemntul trebuie adaugat inainte de prim
	if (rel(c,this->e[i].first)) {
		prec[poz] = -1;
		urm[poz] = prim;
		prec[prim] = poz;
		prim = poz;
		this->dimensiune++;
		return;
	}

	i = urm[i];

	while (i!=-1) {
		if (rel(c,this->e[i].first))
			//daca se respecta relatia inseamna ca trebuie inserat inaintea elementului
		{
			prec[poz] = prec[i];
			urm[poz] = i;
			urm[prec[i]] = poz;
			prec[i] = poz;
			this->dimensiune++;
			return;
		}
		i = urm[i];
	}
	//daca iesim din while inseamna ca elementul trebuie adaugat pe ultima pozitie, dupa ultim
	urm[ultim] = poz;
	prec[poz] = ultim;
	ultim = poz;
	urm[poz] = -1;
	this->dimensiune++;
}

//complexitate Theta(dimensiune)
vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> valori;
	int i = prim;
	while (i != -1 && rel(e[i].first,c)) {
		int ok = 0;
		if (e[i].first == c)
		{
			ok = 1;
			valori.push_back(e[i].second);
		}
		else if (ok == 1)
			return valori;
		i = urm[i];
	}
	//daca nu gaseste va returna un vector gol
	return valori;
}
//caz favorabil: complexitate Theta(1),daca dictionarul este gol
//caz defavorabil: complexitate Theta(dimensiune), trebuie cautat elementul de sters
//caz mediu: complexitate Theta(dimensiune)
bool MDO::sterge(TCheie c, TValoare v) {
	//daca dictionarul nu contine elemente,returnam false
	if(dimensiune == 0)
		return false;

	//cautam elementul in dictionar dupa cheie si apoi dupa valoare
	int i = prim;
	// daca dictionarul contine un singur element, iar acela trebuie sters
	if (dimensiune == 1 && e[i].first == c && e[i].second == v)
	{
		dealoca(i);
		dimensiune--;
		return true;
	}
	//verificam daca trebuie sters primul element
	if (e[i].first == c && e[i].second == v) {
		prec[urm[i]] = -1;
		prim = urm[i];
		dealoca(i);
		dimensiune--;
		return true;
	}
	i = urm[i];
	//parcurgem restul elementelor
	while (i != -1 && i!=ultim) 
	{
		if (e[i].first == c && e[i].second == v)
		{	
			urm[prec[i]] = urm[i];
			prec[urm[i]] = prec[i];
			dealoca(i);
			dimensiune--;
			return true;
		}
		i = urm[i];
	}
	//verificam daca ultimul element e cel care trebuie sters
	if (e[i].first == c && e[i].second == v) {
		urm[prec[i]] = -1;
		ultim = prec[i];
		dealoca(i);
		dimensiune--;
		return true;
	}
	//nu a fost gasit elementul
	return false;
}

//complexitate Theta(1)
int MDO::dim() const {
	return dimensiune;
}

//complexitate Theta(1)
bool MDO::vid() const {
	return dimensiune == 0;
}

//complexitate Theta(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

IteratorValori MDO::iterator_val(TCheie cheie) {
	return IteratorValori(*this, cheie);
}
//complexitate Theta(1)
MDO::~MDO() {
	delete[] e;
	delete[] prec;
	delete[] urm;
}
