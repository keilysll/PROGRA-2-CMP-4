#include "ModeloTexto.h"

ModeloTexto::ModeloTexto(string nombre, int precio):Modelo(nombre,precio)
{
}

ModeloTexto::~ModeloTexto()
{
}

string ModeloTexto::toJson() const
{
	stringstream ss;
	ss << "{\"nombre\":\""<<nombre<<"\",\"tipo\":\"texto\",\"precio\":"<<precio<<"}";
	return ss.str();
}

int ModeloTexto::costo(int tokens)
{
	return ((tokens + 999) / 1000) * precio;
}
