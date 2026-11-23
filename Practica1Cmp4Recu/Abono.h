#pragma once
#include "Operacion.h"
class Abono :
	public Operacion
{
private:
	int origen;
public:
	Abono(int id, int fecha, int monto, int origen);
	int efectoSaldo();
	string toJson();
};