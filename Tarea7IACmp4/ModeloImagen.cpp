#include "ModeloImagen.h"



ModeloImagen::ModeloImagen(string nombre, int precio):Modelo(nombre , precio)
{
}

ModeloImagen::~ModeloImagen()
{
}

string ModeloImagen::toJson()const
{
	stringstream ss;
	ss << "{\"nombre\":\""<<nombre<<"\",\"tipo\":\"imagen\",\"precio\":"<<precio<<"}";
	return ss.str();
}

int ModeloImagen::costo(int imagenes)
{
	return imagenes* precio;
}
