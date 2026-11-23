#include "ValidacionViaje.h"

ValidacionViaje::ValidacionViaje(int id, int fecha, int monto, string linea) : Operacion(id, fecha, "validacion", monto)
{
	this->linea = linea;
	this->bonificacion = 0;
	this->anulada = "false";
}

int ValidacionViaje::efectoSaldo() 
{ 
	return -monto + bonificacion;
}

string ValidacionViaje::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":"<<fecha<<",\"tipo\":\""<<tipo<<"\",\"monto\":"<<monto<<",\"linea\":\""<<linea<<"\",\"bonificacion\":"<<bonificacion<<",\"anulada\":"<<anulada<<"}";
	return ss.str();
}

int ValidacionViaje::montoViaje()
{
	return monto;
}

void ValidacionViaje::bonificar(int porcentaje)
{
	bonificacion = monto * porcentaje / 100;
}
