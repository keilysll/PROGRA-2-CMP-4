#include "UsuarioGratis.h"

UsuarioGratis::UsuarioGratis(string nombre):Usuario(nombre)
{
	this->tokDisp = 10000;
}

UsuarioGratis::~UsuarioGratis()
{
}

string UsuarioGratis::toJson()
{
	stringstream ss;
	ss << "{\"nombre\":\""<<nombre<<"\",\"plan\":\"gratis\",\"tokensDisponibles\":"<<tokDisp<<",\"solicitudes\":"<<solicitudes.toJson()<<"}";
	return ss.str();
}

int UsuarioGratis::TokensDisp()
{
	return 1000;
}

void UsuarioGratis::validarPlan(Solicitud* s, int costo)
{
	if (dynamic_cast<SolicitudImagen*>(s) != NULL)
		throw exception(("el plan gratis no permite imagenes (solicitud " + to_string(s->getId()) + ")").c_str());
	if (s->getTokens() > tokDisp)
		throw exception((nombre + " supero su cuota de tokens en la solicitud " + to_string(s->getId())).c_str());
}

void UsuarioGratis::descontar(Solicitud* s, int costo)
{
	tokDisp = tokDisp - s->getTokens();
	s->setCosto(0);                       // el plan gratis no paga
}