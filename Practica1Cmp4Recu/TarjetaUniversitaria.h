#pragma once
#include "Tarjeta.h"
class TarjetaUniversitaria :
    public Tarjeta
{
public:
    TarjetaUniversitaria(int codigo, string titular);
    int limiteDiario();
    int porcentajeBonificacion();
    string toJson();
};

