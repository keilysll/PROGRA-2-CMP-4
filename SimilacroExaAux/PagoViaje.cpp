#include "PagoViaje.h"

PagoViaje::PagoViaje(int id, int fecha, int monto, string linea):Operacion(id,fecha,monto)
{
	this->linea = linea;
	this->bonificado = 0;
	this->anulado = "false";
}

PagoViaje::~PagoViaje()
{
}

string PagoViaje::getLinea()
{
	return linea;
}

string PagoViaje::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":" << fecha<< ",\"tipo\":\""<<tipo()<<"\",\"monto\":" << monto << ",\"linea\":\""<<linea<<"\",\"bonificacion\":"<<bonificado<<",\"anulado\":"<<anulado<<"}";
	return ss.str();
}

string PagoViaje::tipo()
{
	return "pagoviaje";
}

int PagoViaje::getBonificado()
{
	return bonificado;
}

void PagoViaje::setBonific(int bonificacion)
{
	this->bonificado = bonificacion;
}

int PagoViaje::efecto()
{
	return -monto;
}

bool PagoViaje::estaAnulado()
{
	return anulado == "true";
}

void PagoViaje::anular()
{
	anulado = "true";
}
