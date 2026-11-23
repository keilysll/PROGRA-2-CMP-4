#include "Carga.h"

Carga::Carga(int id, int fecha, int monto):Operacion(id,fecha,monto)
{
}

Carga::~Carga()
{
}

string Carga::tipo()
{
	return "carga";
}

string Carga::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":" << fecha<< ",\"tipo\":\""<<tipo()<<"\",\"monto\":" << monto << "}";
	return ss.str();
}

int Carga::efecto()
{
	return + monto;
}
