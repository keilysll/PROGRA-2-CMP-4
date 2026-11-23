#pragma once
#include "Tarjeta.h"
class TarjetaEstandar :
    public Tarjeta
{
public:
    TarjetaEstandar(int codigo, string titular);
	TarjetaEstandar(int codigo);
    ~TarjetaEstandar();
	string toJson();
	int limiteDiario();
	int tarifaExtra();
	int bonificacion(int monto);
	string tipo();

};

