#pragma once
#include "Transaccion.h"
class Recepcion :
    public Transaccion
{
private:
	int emisor;
public:
	Recepcion(int id, int fecha, int cantidad, int emisor);
	~Recepcion();
	string toJson();
	int efecto();
};

