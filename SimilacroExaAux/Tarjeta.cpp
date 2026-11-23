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

int Tarjeta::getCod()
{
	return codigo;
}

string Tarjeta::getTitular()
{
	return titular;
}

void Tarjeta::registrar(Operacion* o)
{
	PagoViaje* p = dynamic_cast<PagoViaje*>(o);
	Traspaso* t = dynamic_cast<Traspaso*>(o);
	if (o->getMonto() <= 0)
	{
		throw exception(("monto invalido en la operacion " + to_string(o->getId())).c_str());
	}
	if (p != NULL || t != NULL)          // <- antes solo: if (p != NULL)
	{
		int tarifa = 0;                  // <- nuevo: solo los traspasos pagan tarifa
		if (t != NULL)
		{
			tarifa = tarifaExtra();
		}

		int gastado = 0;
		for (int i = 0; i < operaciones.getTam(); i++)
		{
			PagoViaje* pv = dynamic_cast<PagoViaje*>(operaciones.obtener(i));
			if (pv != NULL && !pv->estaAnulado() && pv->getFecha() == o->getFecha())
			{
				gastado = gastado + pv->getMonto();
			}
			Traspaso* tr = dynamic_cast<Traspaso*>(operaciones.obtener(i));   // <- nuevo
			if (tr != NULL && tr->getFecha() == o->getFecha())
			{
				gastado = gastado + tr->getMonto();   // sin contar la tarifa
			}
		}

		if (gastado + o->getMonto() > limiteDiario())   // <- o->getMonto() en vez de p->getMonto()
		{
			throw exception(("la operacion " + to_string(o->getId()) + " supera el limite diario de la tarjeta " + to_string(codigo)).c_str());
		}
		else if (saldo < o->getMonto() + tarifa)        // <- monto + tarifa
		{
			throw exception(("saldo insuficiente en la tarjeta " + to_string(codigo) + " para la operacion " + to_string(o->getId())).c_str());
		}
	}
	if (p != NULL)
	{
		int bono = bonificacion(p->getMonto());
		p->setBonific(bono);
		saldo = saldo + bono;
	}
	if (t != NULL)                       // <- nuevo: guarda la tarifa en el traspaso
	{
		t->setTarifa(tarifaExtra());
	}
	saldo = saldo + o->efecto();
	operaciones.registrar(o);
}

void Tarjeta::anularViaje(int idViaje)
{
	Operacion* op = NULL;
	for (int i = 0; i < operaciones.getTam(); i++)
	{
		if (operaciones.obtener(i)->getId() == idViaje)
			op = operaciones.obtener(i);
	}
	if (op == NULL)
	{
		throw exception(("operacion " + to_string(idViaje) + " no encontrada en la tarjeta " + to_string(codigo)).c_str());
	}

	PagoViaje* pv = dynamic_cast<PagoViaje*>(op);
	if (pv == NULL)
		throw exception(("la operacion " + to_string(op->getId()) + " no es un pago de viaje").c_str());
	if (pv->estaAnulado())
		throw exception(("el viaje " + to_string(idViaje) + " ya fue anulado").c_str());

	saldo = saldo + pv->getMonto() - pv->getBonificado();
	pv->anular();
}

int Tarjeta::totalBonificacion()
{
	int total = 0;
	for (int i = 0; i < operaciones.getTam(); i++)
	{
		PagoViaje* pv = dynamic_cast<PagoViaje*>(operaciones.obtener(i));
		if(pv !=NULL &&  !pv->estaAnulado())
		total = total + pv->getBonificado();
	}
	return total;
}

int Tarjeta::totalTarifas()
{
	int total = 0;
	for (int i = 0; i < operaciones.getTam(); i++)
	{
		Traspaso* t = dynamic_cast<Traspaso*>(operaciones.obtener(i));
		if(t != NULL)
			total = total + t->getTarifa();
	}
	return total;
}

int Tarjeta::getSaldo()
{
	return saldo;
}

string Tarjeta::descripcion()
{
	return "[" + tipo() + "] " + to_string(codigo) + " " + titular + ": " + to_string(saldo) + " Bs";
}

bool Tarjeta::esIgual(const Tarjeta& otra)
{
	return codigo == otra.codigo;
}

void Tarjeta::heredarDe(Tarjeta* otra)
{
	saldo = otra->getSaldo();                                  // copia el saldo
	for (int i = 0; i < otra->operaciones.getTam(); i++)       // otra->, no this
	{
		operaciones.registrar(otra->operaciones.obtener(i));   // operaciones.registrar, NO registrar(...)
	}
}

string Tarjeta::toJsonPtr(Tarjeta* t)
{
	return t->toJson();
}

bool Tarjeta::mayorCodigo(Tarjeta* a, Tarjeta* b)
{
	return a->getCod() > b->getCod();
}

bool Tarjeta::operator==(Tarjeta* t)
{
	return t->codigo == codigo;
}
