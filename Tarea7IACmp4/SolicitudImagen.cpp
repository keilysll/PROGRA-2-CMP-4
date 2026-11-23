#include "SolicitudImagen.h"

SolicitudImagen::SolicitudImagen(int id, string modelo, int tokens):Solicitud(id,modelo,tokens)
{
}

SolicitudImagen::~SolicitudImagen()
{
}

string SolicitudImagen::toJson() const
{
	stringstream ss;
	ss << "{\"id\":"<<id<<",\"modelo\":\""<<modelo<<"\",\"tipo\":\"imagen\",\"cantidad\":"<<tokens<<",\"costo\":"<<costo<<"}";
	return ss.str();
}
