#include "Plataforma.h"

Plataforma::Plataforma(string nombre)
{
	this->nombre = nombre;
}

Plataforma::~Plataforma()
{
}

void Plataforma::registrarCuenta(CuentaJugador* c)
{
	cuentas.registrar(c);
}


void Plataforma::registrar(int idCuenta, Transaccion* t)
{
	CuentaJugador* c = cuentas.buscar(new CuentaNovata(idCuenta));
	if (c == NULL)
		throw exception(("cuenta " + to_string(idCuenta) + " no encontrada").c_str());
	c->registrar(t);
}

void Plataforma::enviar(int idTran, int fecha, int origen, int destino, int cantidad)
{
	CuentaJugador* orig = cuentas.buscar(new CuentaNovata(origen));
	if (orig == NULL)
		throw exception(("cuenta "+ to_string(origen)+ " no encontrada").c_str());

	CuentaJugador* dest = cuentas.buscar(new CuentaNovata(destino));
	if (dest == NULL)
		throw exception(("cuenta " + to_string(destino) + " no encontrada").c_str());

	
	orig->registrar(new Envio(idTran, fecha, cantidad, destino));
	dest->registrar(new Recepcion(idTran, fecha, cantidad, origen));
	
}

string Plataforma::toJson()
{
	stringstream ss;
	ss << "{\"nombre\":\""<<nombre<<"\",\"cuentas\":"<<cuentas.toJson(CuentaJugador::toJsonPtr)<<"}";
	return ss.str();
}
