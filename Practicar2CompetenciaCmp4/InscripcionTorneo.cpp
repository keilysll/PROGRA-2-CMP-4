#include "InscripcionTorneo.h"

InscripcionTorneo::InscripcionTorneo(int id, int fecha, int cantidad, string torneo):Transaccion(id,fecha,cantidad)
{
	this->torneo = torneo;
	this->reembolsada = "false";
}

InscripcionTorneo::~InscripcionTorneo()
{
}

string InscripcionTorneo::getTorneo()
{
	return torneo;
}

string InscripcionTorneo::toJson()
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"fecha\":"<<fecha<<",\"tipo\":\"inscripcion\",\"cantidad\":"<<cantidad<<",\"torneo\":\""<<torneo<<"\",\"cashback\":"<<cashback<<",\"reembolsada\":"<<reembolsada<<"}";
	return ss.str();
}


int InscripcionTorneo::efecto()
{
	return - cantidad;
}
