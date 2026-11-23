#include "TarjetaEstandar.h"

TarjetaEstandar::TarjetaEstandar(int codigo, string titular):Tarjeta(codigo,titular)
{
}

TarjetaEstandar::TarjetaEstandar(int codigo) :Tarjeta(codigo, " ")
{
}

TarjetaEstandar::~TarjetaEstandar()
{
}

string TarjetaEstandar::toJson()
{
	stringstream ss;
	ss << "{\"codigo\":"<<codigo<<",\"titular\":\"" << titular << "\",\"tipo\":\"" << tipo() << "\",\"saldo\":" << saldo << ",\"operaciones\":"<<operaciones.toJson(Operacion::toJsonPtr)<<"}";
	return ss.str();
}

int TarjetaEstandar::limiteDiario()
{
	return 100;
}

int TarjetaEstandar::tarifaExtra()
{
	return 1;
}

int TarjetaEstandar::bonificacion(int monto)
{
	return 0;
}

string TarjetaEstandar::tipo()
{
	return "estandar";
}
