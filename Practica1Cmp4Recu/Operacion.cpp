#include "Operacion.h"

Operacion::Operacion(int id, int fecha, string tipo, int monto)
{
	this->id = id;
	this->fecha = fecha;
	this->tipo = tipo;
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

string Operacion::getTipo()
{
	return tipo;
}

int Operacion::getMonto()
{
	return monto;
}

string Operacion::toJsonPtr(Operacion* o)
{
	return o->toJson();
}

int Operacion::montoViaje()
{
	return 0;
}

void Operacion::bonificar(int porcentaje)
{
}
