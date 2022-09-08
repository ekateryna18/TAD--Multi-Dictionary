#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

class IteratorValori;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
	friend class IteratorValori;
    private:
	/* aici e reprezentarea */
		TElem* e;
		Relatie rel;
		int* urm;
		int* prec;
		int cp = 2, dimensiune = 0;
		int prim, ultim, prim_liber;

		//complexitate Theta(1)
		int aloca() {
			int i = prim_liber;
			prim_liber = urm[prim_liber];
			return i;
		}

		//complexitate Theta(1)
		void dealoca(int i) {
			urm[i] = prim_liber;
			prim_liber = i;
		}

		//complexitate Theta(cp)
		void redim() {
			int* urm_nou = new int[2 * cp];
			for (int i = 0;i < cp;i++)
				urm_nou[i] = urm[i];
			urm = urm_nou;

			int* prec_nou = new int[2 * cp];
			for (int i = 0;i < cp;i++)
				prec_nou[i] = prec[i];
			prec = prec_nou;

			TElem* e_nou = new TElem[2 * cp];
			for (int i = 0;i < cp;i++)
				e_nou[i] = e[i];
			e = e_nou;

			for (int i = cp;i < 2*cp -1 ;i++) {
				urm[i] = i + 1;
			}
			urm[2 * cp -1] = -1;
			prim_liber = cp;
			cp = cp * 2;
		}
		//complexitatet Theta(1)
		int creeazaNod(TElem e) {
			if (dimensiune == cp) {
				redim();
			}
			int i = aloca();
			this->e[i] = e;
			return i;
		}
    public:

	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	IteratorValori iterator_val(TCheie cheie);

	// destructorul 	
	~MDO();

};
