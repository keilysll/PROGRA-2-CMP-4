#include "CuentaJugador.h"

CuentaJugador::CuentaJugador(int id, string alias)
{
	this->id = id;
	this->alias = alias;
	this->balance = 0;
}

CuentaJugador::~CuentaJugador()
{
}

int CuentaJugador::getId()
{
	return id;
}

string CuentaJugador::getAlias()
{
	return alias;
}

int CuentaJugador::getBalance()
{
	return balance;
}

void CuentaJugador::registrar(Transaccion* t)
{
	if (t->getCantidad() <= 0)
		throw exception(("cantidad invalida en la operacion "+ to_string(t->getId())).c_str());

	if (t->efecto() < 0)
	{
		int gastoDelDia = 0;
		for (int i = 0; i < transacciones.getTam(); i++)
		{
			Transaccion* tr = transacciones.obtener(i);
			if (tr->efecto() < 0 && tr->getFecha() == t->getFecha())
			{
				gastoDelDia = gastoDelDia + tr->getCantidad();
			}
		}
		if (gastoDelDia + t->getCantidad() > limiteDiario())
		{
			throw exception(("la operacion "+ to_string(t->getId()) + " supera el tope diario de la cuenta " + to_string (id)).c_str());
			delete t;
		}

	}
	int cashback = 0;
	InscripcionTorneo* i = dynamic_cast<InscripcionTorneo*>(t);
	if (i != NULL)
	{
		double calculo = i->getCantidad() * Porcentajecash();
		cashback = (int)round(calculo);
		i->setCash(cashback);
	}

	Envio* e = dynamic_cast<Envio*>(t);
	if (e != NULL)
	{
		e->setRecargo((int)round(e->getCantidad() * porcentajeRecargo()));

	}
	balance = balance + t->efecto() + cashback;

	transacciones.registrar(t);
}

bool CuentaJugador::operator==(CuentaJugador* c)
{
	return c->id == id;
}

string CuentaJugador::toJsonPtr(CuentaJugador* c)
{
	return c->toJson();
}
