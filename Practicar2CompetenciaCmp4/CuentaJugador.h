#pragma once
#include"CompraGemas.h"
#include"Transaccion.h"
#include"InscripcionTorneo.h"
#include"Envio.h"
#include"Recepcion.h"
#include"ListaEnlazada.h"
class CuentaJugador
{
protected:
	int id;
	string alias;
	int balance;
	ListaEnlazada<Transaccion>transacciones;
public:
	CuentaJugador(int id,string alias);
	~CuentaJugador();
	int getId();
	string getAlias();
	int getBalance();
	virtual string toJson() = 0;
	void registrar(Transaccion* t);
	virtual string rango() = 0;
	virtual double Porcentajecash() = 0;
	virtual int limiteDiario() = 0;
	bool operator == (CuentaJugador* c);
	static string toJsonPtr(CuentaJugador* c);
	virtual double porcentajeRecargo() = 0;



};

