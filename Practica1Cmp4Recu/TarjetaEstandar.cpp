#include "TarjetaEstandar.h"

TarjetaEstandar::TarjetaEstandar(int codigo, string titular):Tarjeta(codigo,titular)
{

	this->tipo = "estandar";
}

TarjetaEstandar::TarjetaEstandar(int codigo):Tarjeta(codigo," ")
{
	
}

int TarjetaEstandar::tarifaExtra()
{
	return 1;
}

string TarjetaEstandar::toJson()
{
	stringstream ss;
	ss << "{\"codigo\":"<<codigo<<",\"titular\":\""<<titular<<"\",\"tipo\":\""<<tipo<<"\",\"saldo\":"<<saldo<<",\"operaciones\":"<<operaciones.toJson(Operacion::toJsonPtr)<<"}";
	return ss.str();
}
