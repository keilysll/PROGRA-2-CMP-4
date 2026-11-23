#include "CompraGemas.h"

CompraGemas::CompraGemas(int id, int fecha, int cantidad):Transaccion(id,fecha,cantidad)
{
}

CompraGemas::~CompraGemas()
{
}

string CompraGemas::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":"<<fecha<<",\"tipo\":\"compra\",\"cantidad\":"<<cantidad<<"}";
	return ss.str();
}

int CompraGemas::efecto()
{
	return + cantidad;
}
