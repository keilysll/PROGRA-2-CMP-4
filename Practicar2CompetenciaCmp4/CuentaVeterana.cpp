#include "CuentaVeterana.h"

CuentaVeterana::CuentaVeterana(int id, string alias):CuentaJugador(id,alias)
{
}

CuentaVeterana::~CuentaVeterana()
{
}

string CuentaVeterana::toJson()
{
	stringstream ss;
	ss << "{\"idCuenta\":"<<id<<",\"alias\":\""<<alias<<"\",\"rango\":\""<<rango()<<"\",\"balance\":"<<balance<<",\"transacciones\":"<<transacciones.toJson(Transaccion::toJsonPtr)<<"}";
	return ss.str();
}

string CuentaVeterana::rango()
{
	return "veterana";
}

double CuentaVeterana::Porcentajecash()
{
	return 0.015;
}

int CuentaVeterana::limiteDiario()
{
	return 800;
}

double CuentaVeterana::porcentajeRecargo()
{
	return 0.03;
}
