#include "Modelo.h"

Modelo::Modelo(string nombre, int precio)
{
	this->nombre = nombre;
	this->precio = precio;
}

Modelo::~Modelo()
{
}

string Modelo::getNombre()
{
	return nombre;
}

int Modelo::getPrecio()
{
	return precio;
}

string Modelo::getClave() const
{
	return nombre;
}



