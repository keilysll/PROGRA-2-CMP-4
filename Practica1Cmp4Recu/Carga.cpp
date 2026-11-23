#include "Carga.h"

Carga::Carga(int id, int fecha, int monto):Operacion(id,fecha,"carga",monto)
{

}

int Carga::efectoSaldo()
{
	return monto;
}

string Carga::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":"<<fecha<<",\"tipo\":\""<<tipo<<"\",\"monto\":"<<monto<<"}";
	return ss.str();
}
