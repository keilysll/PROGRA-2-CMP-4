#include "Operacion.h"

Operacion::Operacion(int id, int fecha, int monto)
{
	this->id = id;
	this->fecha = fecha;
	this->monto = monto;
}

Operacion::~Operacion()
{
}

int Operacion::getId()
{
	return id;
}

int Operacion::getFecha()
{
	return fecha;
}

int Operacion::getMonto()
{
	return monto;
}

string Operacion::toJsonPtr(Operacion* o)
{
	return o->toJson();
}
