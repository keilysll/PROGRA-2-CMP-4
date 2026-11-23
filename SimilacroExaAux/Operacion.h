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
	int monto;
public:
	Operacion(int id,int fecha,int monto);
	~Operacion();
	int getId();
	int getFecha();
	int getMonto();
	virtual string tipo() = 0;
	virtual string toJson() = 0;
	static string toJsonPtr(Operacion* o);
	virtual int efecto() = 0;

};

