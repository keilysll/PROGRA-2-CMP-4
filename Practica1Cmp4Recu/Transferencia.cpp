#include "Transferencia.h"

Transferencia::Transferencia(int id, int fecha, int monto, int destino, int tarijaExtra):Operacion(id,fecha,"transferencia", monto)
{
	this->destino = destino;
	this->tarifaExtra = tarijaExtra;
}

Transferencia::~Transferencia()
{
}

int Transferencia::getDestino()
{
	return destino;
}

int Transferencia::getTarifa()
{
	return tarifaExtra;
}

string Transferencia::toJson()
{
	stringstream ss;
	ss << "{\"id\":" << id << ",\"fecha\":" << fecha << ",\"tipo\":\"" << tipo << "\",\"monto\":" << monto<< ",\"destino\":" << destino << ",\"tarifaExtra\":" << tarifaExtra << "}";
	return ss.str();
}

int Transferencia::efectoSaldo()
{
	return -(monto + tarifaExtra);
}
