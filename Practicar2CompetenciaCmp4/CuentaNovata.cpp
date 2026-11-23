#include "CuentaNovata.h"

CuentaNovata::CuentaNovata(int id, string alias):CuentaJugador(id,alias)
{
}

CuentaNovata::CuentaNovata(int id) :CuentaJugador(id, " ")
{
}

CuentaNovata::~CuentaNovata()
{
}

string CuentaNovata::toJson()
{
	stringstream ss;
	ss << "{\"idCuenta\":"<<id<<",\"alias\":\""<<alias<<"\",\"rango\":\""<<rango()<<"\",\"balance\":"<<balance<<",\"transacciones\":"<<transacciones.toJson(Transaccion::toJsonPtr)<<"}";
	return ss.str();
}

string CuentaNovata::rango()
{
	return "novata";
}

double CuentaNovata::Porcentajecash()
{
	return 0;
}

double CuentaNovata::porcentajeRecargo()
{
	return 0.05;
}

int CuentaNovata::limiteDiario()
{
	return 500;
}
