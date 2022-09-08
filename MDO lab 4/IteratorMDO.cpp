#include "IteratorMDO.h"
#include "MDO.h"
#include <exception>

//complexitate Theta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	curent = d.prim;
}

//complexitate Theta(1)
void IteratorMDO::prim(){
	curent = dict.prim;
}
//complexitate Theta(1)
void IteratorMDO::urmator(){
	if (!valid()) {
		throw exception();
	}
	curent = dict.urm[curent];
}

//complexitate Theta(1)
bool IteratorMDO::valid() const{
	if (curent != -1)
		return true;
	return false;
}
//complexitate Theta(1)
TElem IteratorMDO::element() const{
	if (!valid())
		throw exception();
	return pair <TCheie, TValoare>  (dict.e[curent].first, dict.e[curent].second);
}