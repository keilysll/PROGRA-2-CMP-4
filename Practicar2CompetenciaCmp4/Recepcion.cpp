#include "Recepcion.h"

Recepcion::Recepcion(int id, int fecha, int cantidad, int emisor):Transaccion(id,fecha,cantidad)
{
	this->emisor = emisor;
}

Recepcion::~Recepcion()
{
}

string Recepcion::toJson()
{
	stringstream ss;
	ss << "{\"id\":" << id << ",\"fecha\":" << fecha << ",\"tipo\":\"recepcion\",\"cantidad\":" << cantidad<< ",\"emisor\":" << emisor << "}";
	return ss.str();
}

int Recepcion::efecto()
{
	return + cantidad;
}
