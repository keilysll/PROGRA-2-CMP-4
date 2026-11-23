#include "Tarjeta.h"

Tarjeta::Tarjeta(int codigo, string titular)
{
	this->codigo = codigo;
	this->titular = titular;
	this->saldo = 0;
}

Tarjeta::~Tarjeta()
{
}

int Tarjeta::getCodigo()
{
	return codigo;
}

string Tarjeta::getTitular()
{
	return titular;
}

void Tarjeta::registrar(Operacion* o)
{
	if (o->getMonto() <= 0)
	{
		throw exception(("monto invalido en la operacion " + to_string(o->getId())).c_str());
	}
	int limite = limiteDiario();
	if (limite > 0 && consumoDelDia(o->getFecha()) + o->montoViaje() > limite)
	{
		string mensaje = "la operacion " + to_string(o->getId()) + " supera el limite diario de la tarjeta " + to_string(codigo);
		delete o;
		throw exception(mensaje.c_str());
	}
	o->bonificar(porcentajeBonificacion());
	if (saldo + o->efectoSaldo() < 0)
	{
		throw exception(("saldo insuficiente en la tarjeta " + to_string(codigo) + " para la operacion " + to_string(o->getId())).c_str());
	}
	saldo = saldo + o->efectoSaldo();
	operaciones.registrar(o);
}

int Tarjeta::limiteDiario()
{
	return 0;
}

int Tarjeta::porcentajeBonificacion()
{
	return 0;
}

int Tarjeta::consumoDelDia(int fecha)
{
	int total = 0;
	for (int i = 0; i < operaciones.getTam(); i++)
	{
		if (operaciones[i]->getFecha() == fecha)
			total = total + operaciones[i]->montoViaje();
	}
	return total;
}

bool Tarjeta::operator==(Tarjeta* t)
{
	return t->codigo == codigo;
}

int Tarjeta::tarifaExtra()
{
	return 0;
}

string Tarjeta::toJsonPtr(Tarjeta* t)
{
	return t->toJson();
}


