#pragma once
#include"Nodo.h"
template<class T>
class ListaEnlazada
{
private:
	Nodo<T>* primerNod;
	int tam;

public:
	ListaEnlazada();
	~ListaEnlazada();
	void registrar(T* dato);
	T* buscar(T* dato);
	string toJson(string(*f)(T*));
	T* obtener(int pos);
	int getTam();

};

template<class T>
inline ListaEnlazada<T>::ListaEnlazada()
{
	primerNod = NULL;
	tam = 0;
}

template<class T>
inline ListaEnlazada<T>::~ListaEnlazada()
{
}

template<class T>
inline void ListaEnlazada<T>::registrar(T* dato)
{
	if (primerNod == NULL)
		primerNod = new Nodo<T>(dato);
	else
	{
		Nodo<T>* tmp = primerNod;
		while (tmp->getSig() != NULL)
		{
			tmp = tmp->getSig();
		}
		tmp->crearSig(dato);
	}
	tam++;
}

template<class T>
inline T* ListaEnlazada<T>::buscar(T* dato)
{
	Nodo<T>* tmp = primerNod;
	while (tmp!= NULL)
	{
		if (*(tmp->getDato()) == dato)
		{
			return tmp->getDato();
		}
		tmp = tmp->getSig();
	}
	return NULL;
}

template<class T>
inline string ListaEnlazada<T>::toJson(string(*f)(T*))
{
	stringstream ss;
	ss << "[";
	Nodo<T>* tmp = primerNod;
	while (tmp != NULL)
	{
		ss << (*f)(tmp->getDato());
		if (tmp->getSig() != NULL)
		{
			ss << ",";
		}
		tmp = tmp->getSig();
	}
	
	ss << "]";
	return ss.str();
}

template<class T>
inline T* ListaEnlazada<T>::obtener(int pos)
{
	Nodo<T>* tmp = primerNod;
	for (int i = 0; i < pos; i++)
	{
		tmp = tmp->getSig();
	}
	return tmp->getDato();
}

template<class T>
inline int ListaEnlazada<T>::getTam()
{
	return tam;
}
