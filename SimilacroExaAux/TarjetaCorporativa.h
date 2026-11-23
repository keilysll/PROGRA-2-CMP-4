#pragma once
#include "TarjetaEstudiantil.h"
class TarjetaCorporativa :
    public TarjetaEstudiantil
{
private:
    int nit;
public:
    TarjetaCorporativa(int codigo,string titular, int nit);
    ~TarjetaCorporativa();
    int getNit();
    string toJson();
    int limiteDiario();
    int tarifaExtra();
    int bonificacion(int monto);
    string tipo();

};

