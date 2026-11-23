#pragma once
#include "Operacion.h"
class ValidacionViaje :
    public Operacion
{
private:
	string linea;
	int bonificacion;
	string anulada;

public:
	ValidacionViaje(int id, int fecha, int monto, string linea);
	int efectoSaldo();
	string toJson();
	int montoViaje();
	void bonificar(int porcentaje);
};

