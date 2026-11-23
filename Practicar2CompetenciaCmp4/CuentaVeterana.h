#pragma once
#include "CuentaJugador.h"
class CuentaVeterana :
    public CuentaJugador
{
public:
    CuentaVeterana(int id, string alias);
    ~CuentaVeterana();
    string toJson();
    string rango();
    double Porcentajecash();
    int limiteDiario();
    double porcentajeRecargo();
};

