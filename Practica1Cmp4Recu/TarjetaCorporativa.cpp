#include "TarjetaCorporativa.h"

TarjetaCorporativa::TarjetaCorporativa(int codigo, string titular, int ruc):Tarjeta(codigo,titular)
{
	this->ruc = ruc;
}

TarjetaCorporativa::~TarjetaCorporativa()
{
}

int TarjetaCorporativa::getRuc()
{
	return ruc;
}

string TarjetaCorporativa::toJson()
{
	stringstream ss;
	ss << "{\"codigo\":"<<codigo<<",\"titular\":\""<<titular<<"\",\"tipo\":\"corporativa\",\"ruc\":"<<ruc<<",\"saldo\":"<<saldo<<",\"operaciones\":"<<operaciones.toJson(Operacion::toJsonPtr)<<"}";
	return ss.str();
}
