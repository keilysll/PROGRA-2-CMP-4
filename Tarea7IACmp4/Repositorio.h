#pragma once
#include"Nodo.h"
template <class T>
class Repositorio
{
private:
	Nodo<T>* primerNodo;
	int tam;
public:
	Repositorio();
	~Repositorio();
	void agregar(T* valor);
	T* obtener(int posicion);
	T* buscar(string clave);
	int size();
	string toJson();
	void limpiar();
};


template<class T>
Repositorio<T>::Repositorio()
{
	primerNodo = NULL;
	tam = 0;
}

template<class T>
Repositorio<T>::~Repositorio()
{
	limpiar();
}

template<class T>
void Repositorio<T>::agregar(T* valor)
{
	string clave = valor->getClave();         
	Nodo<T>* aux = primerNodo;
	while (aux != NULL)
	{
		if (aux->getDato()->getClave() == clave)
		{
			delete valor;
			throw exception(("clave duplicada: " + clave).c_str());   
		}
		aux = aux->getSig();
	}
	if (primerNodo == NULL)
		primerNodo = new Nodo<T>(valor);       
	else
	{
		Nodo<T>* tmp = primerNodo;
		while (tmp->getSig() != NULL)
			tmp = tmp->getSig();
		tmp->crearSig(valor);
	}
	tam++;
}

template<class T>
T* Repositorio<T>::obtener(int posicion)
{
	Nodo<T>* tmp = primerNodo;
	for (int i = 0; i < posicion; i++)
	{
		tmp = tmp->getSig();
	}
	return tmp->getDato();
}

template<class T>
T* Repositorio<T>::buscar(string clave)
{
	Nodo<T>* tmp = primerNodo;
	while (tmp != NULL)
	{
		if (tmp->getDato()->getClave() == clave)
			return tmp->getDato();
		tmp = tmp->getSig();
	}
	throw exception(("clave no encontrada: " + clave).c_str());
}

template<class T>
int Repositorio<T>::size()
{
	return tam;
}

template<class T>
string Repositorio<T>::toJson()
{
	stringstream ss;
	ss << "[";
	Nodo<T>* tmp = primerNodo;
	while (tmp != NULL)
	{
		ss << tmp->getDato()->toJson();
		if (tmp->getSig() != NULL)
			ss << ",";
		tmp = tmp->getSig();
	}
	ss << "]";
	return ss.str();
}

template<class T>
inline void Repositorio<T>::limpiar()
{
	Nodo<T>* tmp = primerNodo;
	while (tmp != NULL)
	{
		Nodo<T>* sig = tmp->getSig();
		delete tmp->getDato();
		delete tmp;
		tmp = sig;
	}
	primerNodo = NULL;
	tam = 0;
}
