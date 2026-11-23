#pragma once
#include "Tarjeta.h"
class TarjetaEstudiantil :
    public Tarjeta
{
public:
    TarjetaEstudiantil(int codigo, string titular);
    ~TarjetaEstudiantil();
	string toJson();
	int limiteDiario();
	int tarifaExtra();
	int bonificacion(int monto);
	string tipo();
};

