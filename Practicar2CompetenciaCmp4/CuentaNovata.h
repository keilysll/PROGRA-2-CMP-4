#pragma once
#include"CuentaJugador.h"
class CuentaNovata :
    public CuentaJugador
{
public:
    CuentaNovata(int id, string alias);
    CuentaNovata(int id);
    ~CuentaNovata();
    string toJson();
     string rango();
     double Porcentajecash();
     double porcentajeRecargo();
     int limiteDiario();
};

