#include "SolicitudTexto.h"

SolicitudTexto::SolicitudTexto(int id, string modelo, int tokens):Solicitud(id,modelo,tokens)
{
}

SolicitudTexto::~SolicitudTexto()
{
}

string SolicitudTexto::toJson() const
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"modelo\":\"" << modelo << "\",\"tipo\":\"texto\",\"cantidad\":" << tokens << ",\"costo\":"<<costo<<"}";
	return ss.str();
}
