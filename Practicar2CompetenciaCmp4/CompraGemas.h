#pragma once
#include "Transaccion.h"
class CompraGemas :
    public Transaccion
{
public:
	CompraGemas(int id, int fecha, int cantidad);
	~CompraGemas();
	string toJson();
	int efecto();
};

