#include "UsuarioPro.h"

UsuarioPro::UsuarioPro(string nombre,int creditos):Usuario(nombre)
{
	this->creditos = creditos;
}

UsuarioPro::~UsuarioPro()
{
}

string UsuarioPro::toJson()
{
	stringstream ss;
	ss << "{\"nombre\":\"" << nombre << "\",\"plan\":\"pro\",\"creditos\":" << creditos << ",\"solicitudes\":" << solicitudes.toJson() << "}";
	return ss.str();
}

int UsuarioPro::TokensDisp()
{
	return 0;
}

void UsuarioPro::validarPlan(Solicitud* s, int costo)
{
	if (costo > creditos)
		throw exception(("creditos insuficientes " + nombre + " en la solicitud " + to_string(s->getId())).c_str());
}

void UsuarioPro::descontar(Solicitud* s, int costo)
{
	creditos = creditos - costo;
}
