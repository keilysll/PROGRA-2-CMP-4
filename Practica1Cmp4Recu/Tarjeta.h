#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include"ListaEnlazada.h"
#include"Operacion.h"
#include"Abono.h"
#include"Transferencia.h"
#include"Carga.h"
#include"ValidacionViaje.h"
using namespace std;
class Tarjeta
{
protected:
	int codigo;
	string titular;
	string tipo;
	int saldo;
	ListaEnlazada<Operacion> operaciones;

public:
	Tarjeta(int codigo,string titular);
	~Tarjeta();
	int getCodigo();
	string getTitular();
	virtual string toJson() = 0;
	void registrar(Operacion* o);
	virtual int limiteDiario();
	virtual int porcentajeBonificacion();
	int consumoDelDia(int fecha);
	bool operator ==(Tarjeta* t);
	virtual int tarifaExtra();
	static string toJsonPtr(Tarjeta* t);

	


};

