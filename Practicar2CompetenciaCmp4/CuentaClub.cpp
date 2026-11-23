#include "CuentaClub.h"

CuentaClub::CuentaClub(int id, string alias, string claveClub):CuentaJugador(id,alias)
{
	this->claveclub = claveClub;
}

CuentaClub::~CuentaClub()
{
}

string CuentaClub::getClaveClub()
{
	return claveclub;
}

string CuentaClub::toJson()
{
	stringstream ss;
	ss << "{\"idCuenta\":"<<id<<",\"alias\":\"" << alias << "\",\"rango\":\"" << rango() << "\",\"claveClub\":\"" << claveclub<< "\",\"balance\":"<<balance<<",\"transacciones\":"<<transacciones.toJson(Transaccion::toJsonPtr)<<"}";
	return ss.str();
}

string CuentaClub::rango()
{
	return "club";
}

double CuentaClub::Porcentajecash()
{
	return 0.02;
}

int CuentaClub::limiteDiario()
{
	return 2000;
}

double CuentaClub::porcentajeRecargo()
{
	return 0.02;
}


