#pragma once
#include "CuentaJugador.h"
class CuentaClub :
    public CuentaJugador
{
private:
    string claveclub;
public:
    CuentaClub(int id, string alias,string claveClub);
    ~CuentaClub();
    string getClaveClub();
    string toJson();
    string rango();
    double Porcentajecash();
    int limiteDiario();
    double porcentajeRecargo();
};

