#include "TarjetaEstudiantil.h"

TarjetaEstudiantil::TarjetaEstudiantil(int codigo, string titular): Tarjeta(codigo, titular)
{
}

TarjetaEstudiantil::~TarjetaEstudiantil()
{
}

string TarjetaEstudiantil::toJson()
{
	stringstream ss;
	ss << "{\"codigo\":"<<codigo<<",\"titular\":\"" << titular << "\",\"tipo\":\"" << tipo() << "\",\"saldo\":" << saldo << ",\"operaciones\":"<<operaciones.toJson(Operacion::toJsonPtr)<<"}";
	return ss.str();
}

int TarjetaEstudiantil::limiteDiario()
{
	return 300;
}

int TarjetaEstudiantil::tarifaExtra()
{
	return 0;
}

int TarjetaEstudiantil::bonificacion(int monto)
{
	return monto/20;
}

string TarjetaEstudiantil::tipo()
{
	return "estudiantil";
}
