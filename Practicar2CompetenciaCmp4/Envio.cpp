#include "Envio.h"

Envio::Envio(int id, int fecha, int cantidad, int receptor):Transaccion(id,fecha,cantidad)
{
	this->receptor = receptor;
	this->recarga = 0;
}

Envio::~Envio()
{
}

string Envio::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":" << fecha<< ",\"tipo\":\"envio\",\"cantidad\":" << cantidad << ",\"receptor\":" << receptor<< ",\"recargo\":"<<recarga<<"}";
	return ss.str();
}

void Envio::setRecargo(int recargo)
{
	this->recarga = recargo;
}

int Envio::efecto()
{
	return - (cantidad + recarga);
}


