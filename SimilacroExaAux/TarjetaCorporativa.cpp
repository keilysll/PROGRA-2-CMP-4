#include "TarjetaCorporativa.h"

TarjetaCorporativa::TarjetaCorporativa(int codigo, string titular, int nit):TarjetaEstudiantil(codigo,titular)
{
	this->nit = nit;
}

TarjetaCorporativa::~TarjetaCorporativa()
{
}

int TarjetaCorporativa::getNit()
{
	return nit;
}

string TarjetaCorporativa::toJson()
{
	stringstream ss;
	ss << "{\"codigo\":"<<codigo<<",\"titular\":\"" << titular << "\",\"tipo\":\""<<tipo()<<"\",\"nit\":" << nit << ",\"saldo\":" << saldo << ",\"operaciones\":"<<operaciones.toJson(Operacion::toJsonPtr)<<"}";
	return ss.str();
}

int TarjetaCorporativa::limiteDiario()
{
	return 1500;
}

int TarjetaCorporativa::tarifaExtra()
{
	return 0;
}

int TarjetaCorporativa::bonificacion(int monto)
{
	return monto / 20;
}

string TarjetaCorporativa::tipo()
{
	return "corporativa";
}
