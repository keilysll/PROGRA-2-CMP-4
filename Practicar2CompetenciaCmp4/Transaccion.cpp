#include "Transaccion.h"

Transaccion::Transaccion(int id, int fecha, int cantidad)
{
	this->id = id;
	this->fecha = fecha;
	this->cantidad = cantidad;
	this->cashback = 0;
}

Transaccion::~Transaccion()
{
}

int Transaccion::getId()
{
	return id;
}

int Transaccion::getFecha()
{
	return fecha;
}

int Transaccion::getCantidad()
{
	return cantidad;
}

string Transaccion::toJsonPtr(Transaccion* t)
{
	return t->toJson();
}

void Transaccion::setCash(int cashback)
{
	this->cashback = cashback;
}
