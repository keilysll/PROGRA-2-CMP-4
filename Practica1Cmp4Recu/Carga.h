#pragma once
#include "Operacion.h"
class Carga :
    public Operacion
{
public:
	Carga(int id, int fecha, int monto);
	int efectoSaldo();
	string toJson();
};

