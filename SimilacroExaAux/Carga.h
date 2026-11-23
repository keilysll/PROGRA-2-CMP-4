#pragma once
#include "Operacion.h"
class Carga :
    public Operacion
{
public:
    Carga(int id, int fecha, int monto);
    ~Carga();
    string tipo();
    string toJson();
    int efecto();

};

