#pragma once
#include"CuentaJugador.h"
#include"CuentaVeterana.h"
#include"CuentaNovata.h"
#include"ListaEnlazada.h"
#include"CuentaClub.h"
class Plataforma
{
private:
	string nombre;
	ListaEnlazada<CuentaJugador> cuentas;
public:
	Plataforma(string nombre);
	~Plataforma();
	void registrarCuenta(CuentaJugador* c);
	void registrar(int idCuenta,Transaccion* t);
	void enviar(int idTran,int fecha,int origen,int destino,int cantidad);
	string toJson();

};

