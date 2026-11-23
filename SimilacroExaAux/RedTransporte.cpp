#include "RedTransporte.h"

RedTransporte::RedTransporte(string nombre)
{
	this->nombre = nombre;
}

RedTransporte::~RedTransporte()
{
}

void RedTransporte::registrarTarjeta(Tarjeta* t)
{
	if (posicion(t->getCod()) != -1)
		throw exception(("la tarjeta " + to_string(t->getCod()) + " ya existe").c_str());
	tarjetas.registrar(t);
	tarjetas.ordenar(Tarjeta::mayorCodigo);
}

void RedTransporte::registrar(int CodTarjeta, Operacion* o)
{
	Tarjeta* t = buscar(CodTarjeta);
	t->registrar(o);
}

void RedTransporte::traspasar(int id, int fecha, int orige, int destino, int monto)
{
	Tarjeta* o = buscar(orige);
	Tarjeta* d = buscar(destino);
	o->registrar(new Traspaso(id, fecha, monto, destino));
	d->registrar(new Abono(id, fecha, monto, orige));
}

void RedTransporte::anularViaje(int codTarjeta, int idViaje)
{
	Tarjeta* t = buscar(codTarjeta);
	t->anularViaje(idViaje);
}

void RedTransporte::mejorarTarjeta(int codTarjeta)
{
	Tarjeta* t = buscar(codTarjeta);
	TarjetaEstandar* ts = dynamic_cast<TarjetaEstandar*>(t);
	if (ts == NULL)
		throw exception(("la tarjeta " + to_string(codTarjeta) + " no es estandar").c_str());
	TarjetaEstudiantil* nueva = new TarjetaEstudiantil(t->getCod(), t->getTitular());
	nueva->heredarDe(t);
	tarjetas.reemplazar(posicion(codTarjeta), nueva);
	delete t;
}

Tarjeta* RedTransporte::buscar(int codTarjeta)
{
	int pos = posicion(codTarjeta);
	if (pos == -1)
		throw exception(("tarjeta " + to_string(codTarjeta) + " no encontrada").c_str());
	return tarjetas.obtener(pos);
}

int RedTransporte::totalBonificacion()
{
	int total = 0;
	for (int i = 0; i < tarjetas.getTam(); i++)
	{
		total = total + tarjetas.obtener(i)->totalBonificacion();
	}
	return total;
}

int RedTransporte::totalTarifas()
{
	int total = 0;
	for (int i = 0; i < tarjetas.getTam(); i++)
	{
		total = total + tarjetas.obtener(i)->totalTarifas();
	}
	return total;
}

int RedTransporte::saldoTotal()
{
	int total = 0;
	for (int i = 0; i < tarjetas.getTam(); i++)
	{
		total = total + tarjetas.obtener(i)->getSaldo();
	}
	return total;
}

string RedTransporte::tarjetaMayorSaldo()
{
	Tarjeta* mayor = tarjetas.obtener(0);
	for (int i = 0; i < tarjetas.getTam(); i++)
	{
		if (tarjetas.obtener(i)->getSaldo() > mayor->getSaldo())
		{
			mayor = tarjetas.obtener(i);
		}
	}
	return mayor->getTitular();
}

string RedTransporte::toJson()
{
	stringstream ss;
	ss << "{\"nombre\":\"" << nombre << "\",\"tarjetas\":" << tarjetas.toJson(Tarjeta::toJsonPtr) << "}";
	return ss.str();
}

int RedTransporte::posicion(int codTarjeta)
{
	for (int i = 0; i < tarjetas.getTam(); i++)
		if (tarjetas.obtener(i)->getCod() == codTarjeta) return i;
	return -1;
}
