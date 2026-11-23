#include "Abono.h"

Abono::Abono(int id, int fecha, int monto, int origen):Operacion(id,fecha,"abono",monto)
{
	this->origen = origen;
}

int Abono::efectoSaldo()
{
	return monto;
}

string Abono::toJson()
{
	stringstream ss;
	ss << "{\"id\":" << id << ",\"fecha\":" << fecha << ",\"tipo\":\"" << tipo << "\",\"monto\":" << monto<< ",\"origen\":" << origen << "}";
	return ss.str();
}
