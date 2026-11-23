#include "Traspaso.h"

Traspaso::Traspaso(int id, int fecha, int monto, int destino):Operacion(id,fecha,monto)
{
	this->destino = destino;
	this->tarifa = 0;
}

string Traspaso::tipo()
{
	return "traspaso";
}

string Traspaso::toJson()
{
	stringstream ss;
	ss << "{\"id\":" << id << ",\"fecha\":" << fecha << ",\"tipo\":\"" << tipo()<< "\",\"monto\":" << monto << ",\"destino\":" << destino << ",\"tarifa\":" << tarifa << "}";
	return ss.str();
}

int Traspaso::efecto()
{
	return -(monto +tarifa);
}

int Traspaso::getDestino()
{
	return destino;
}

int Traspaso::getTarifa()
{
	return tarifa;
}

void Traspaso::setTarifa(int tarifa)
{
	this->tarifa = tarifa;
}
