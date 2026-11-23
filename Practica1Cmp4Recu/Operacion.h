#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
class Operacion
{
protected:
	int id;
	int fecha;
	string tipo;
	int monto;
public:
	Operacion(int id, int fecha, string tipo, int monto);
	~Operacion();
	int getId();
	int getFecha();
	string getTipo();
	int getMonto();
	virtual int efectoSaldo() = 0;
	virtual string toJson() = 0;
	static string toJsonPtr(Operacion* o);
	virtual int montoViaje();
	virtual void bonificar(int porcentaje);
};
