#include "Catalogo.h"
Catalogo::Catalogo()
{
}
Catalogo::~Catalogo()
{
}

Catalogo& Catalogo::getInst()
{
	static Catalogo inst;
	return inst;
}


void Catalogo::registrar(Modelo* m)
{
	modelos.agregar(m);
}

Modelo* Catalogo::buscar(string nombre)
{
	return modelos.buscar(nombre);
}

void Catalogo::limpiar()
{
	modelos.limpiar();
}

string Catalogo::toJson()
{
	stringstream ss;
	ss << "{\"modelos\":" + modelos.toJson() + "}";
	return ss.str();
}

