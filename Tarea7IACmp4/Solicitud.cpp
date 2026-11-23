#include "Solicitud.h"

Solicitud::Solicitud(int id, string modelo, int tokens)
{
	this->id = id;
	this->modelo = modelo;
	this->tokens = tokens;
	this->costo = 0;
}

Solicitud::~Solicitud()
{
}

int Solicitud::getId()
{
	return id;
}

string Solicitud::getModelo()
{
	return modelo;
}

int Solicitud::getTokens()
{
	return tokens;
}

int Solicitud::getCosto()
{
	return costo;
}

string Solicitud::getClave() const
{
	return to_string(id);
}

void Solicitud::setCosto(int costo)
{
	this->costo = costo;
}
