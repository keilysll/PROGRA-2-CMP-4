#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
class Transaccion
{
protected:
	int id;
	int fecha;
	int cantidad;
	int cashback;
public:
	Transaccion(int id, int fecha, int cantidad);
	~Transaccion();
	int getId();
	int getFecha();
	int getCantidad();
	virtual string toJson() = 0;
	static string toJsonPtr(Transaccion* t);
	virtual int efecto() = 0;
	void setCash(int cashback);
};

