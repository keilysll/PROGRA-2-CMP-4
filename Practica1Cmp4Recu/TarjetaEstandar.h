#pragma once
#include "Tarjeta.h"
class TarjetaEstandar :
    public Tarjeta
{
public:
	TarjetaEstandar(int codigo, string titular);
	TarjetaEstandar(int codigo);
	int tarifaExtra();
	string toJson();
};

