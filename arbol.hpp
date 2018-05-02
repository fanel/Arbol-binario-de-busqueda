#include <stdio.h>
#include <iostream>
using namespace std;

class colisiones {
	int col;
public:
	void set (int n) {
		col = n;
	}
	int get () {
		return col;
	}
	
	colisiones (){col = 0;}
};

template <class T>
class nodo{
public:
	nodo <T>* iz;
	nodo <T>* de;
	nodo <T>* pa;
	colisiones col;
	T dato;

	void printall () {
		bool haymas = true;
		int n = 0;
		while (haymas) {
			haymas = false;
			cout << "Nivel " << n << ": ";
			if (print (n))
				haymas = true;
			cout << endl;
			n++;
		}
		cout << "Nivel " << n << ": ";
		print (n);
		cout << endl;
	}

	bool print (int obj) {
		if (obj == 0) {
			cout << dato << " ";
			if ((de != NULL) || (iz != NULL))
			    return (true);
			else
			    return (false);
		} else if (obj > 0){
			if (iz == NULL){
				if (obj == 1) {
                    cout << "[.] ";
				}
			} else {
				(*iz).print (obj - 1);
			}
			if (de == NULL) {
				if (obj == 1) {
                    cout << "[.] ";
				}
			} else {
				(*de).print (obj - 1);
			}
		}
	}

	nodo (T d){
		iz = de = pa = NULL;
		dato = d;
		col.set (0);
	}
	nodo (){iz = de = pa = NULL; col.set (0);}
};

template <class T>
class ABB{
public:
    int comp;
	nodo <T>* padre;

	ABB (){padre = NULL;}

	void print () {
		if (padre != NULL)
			(*padre).printall();
		else
			cout << "Nivel 0: [.]" << endl;
	}

	nodo <T>* buscarn (T x){
	    comp = 0;
		nodo <T>* n = padre;
		while (n != NULL){
            comp++;
			if (x == (*n).dato)
				return (n);
			else if (x < (*n).dato)
				n = (*n).iz;
			else
				n = (*n).de;
		}
		return (NULL);
	}

	bool buscar (T x) {
		if (buscarn (x) != NULL)
			return (true);
		else
			return (false);
	}

	void insertar (T x) {
    comp = 0;
	if (padre == NULL) {
        comp++;
		padre = new nodo <T> (x);
	} else {
		nodo<T>* a;
		nodo<T>* b;
		a = b = padre;
		while (a != NULL){
		    comp++;
			b = a;
			if (x == (*a).dato) {
				a -> col.set (a -> col.get() + 1);
				return;
			}
			if (x < (*a).dato)
				a = (*a).iz;
			else
				a = (*a).de;
		}
		a = new nodo <T> (x);
		if (x > (*b).dato) {
			(*b).de = a;
			b->de->pa = b;
		} else {
			(*b).iz = a;
			b->iz->pa = b;
        }
	}}

	void eliminar (T x){
	if (buscar (x)){
		nodo <T>* n = buscarn (x);

		if (n != padre) {
            if (n->pa->iz == n)
                n->pa->iz = NULL;
            else
                n->pa->de = NULL;

			if ((*n).iz != NULL) {
				if ((*(*n).pa).iz == n)
					(*(*n).pa).iz = (*n).iz;
				else
					(*(*n).pa).de = (*n).iz;
				redist (n->de);
			} else {
				if ((*(*n).pa).iz == n)
					(*(*n).pa).iz = (*n).de;
				else
					(*(*n).pa).de = (*n).de;
			}
            delete n;
		} else {
			if ((*n).iz != NULL) {
				padre = (*n).iz;
				n->iz->pa = NULL;
				redist ((*n).de);
			} else {
				if (n->de != NULL)n->de->pa = NULL;
				padre = (*n).de;
			}
            delete n;
		}
	}}

	void redist (nodo <T>* n) {
		if (n != NULL) {
            nodo <T>* z;
            while (((*n).iz != NULL) || ((*n).de != NULL)){
                z = n;
                while (((*z).iz != NULL) || ((*z).de != NULL)){
                    if ((*z).iz != NULL)
                        z = (*z).iz;
                    else
                        z = (*z).de;
                }
                if ((*(*z).pa).iz == z)
                    (*(*z).pa).iz = NULL;
                else
                    (*(*z).pa).de = NULL;
                insertar ((*z).dato);
                delete z;
            }
            insertar ((*n).dato);
            delete n;
		}
	}
};
