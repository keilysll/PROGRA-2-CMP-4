#include "Plataforma.h"

Plataforma::Plataforma(string nombre)
{
	this->nombre = nombre;
}

Plataforma::~Plataforma()
{
}

string Plataforma::getNombre()
{
	return nombre;
}

void Plataforma::operator+=(Usuario* u)
{
	usuarios.agregar(u);
}

void Plataforma::procesar(string nombre, Solicitud* s)
{
	Usuario* u = usuarios.buscar(nombre);
	u->procesar(s);
}

string Plataforma::toJson()
{
	stringstream ss;
	ss << "{\"nombre\":\"" << nombre << "\",\"usuarios\":" << usuarios.toJson() << "}";
	return ss.str(); return string();
}

int Plataforma::ingresoTotal()
{
	int total = 0;
	for (int i = 0; i < usuarios.size(); i++)
	{
		total = total + usuarios.obtener(i)->ingresoTotal();
	}
	return total;
}

int Plataforma::tokensProcesados()
{
	int total = 0;
	for (int i = 0; i < usuarios.size(); i++)
	{
		total = total + usuarios.obtener(i)->tokensProcesados();
	}
	return total;
}
