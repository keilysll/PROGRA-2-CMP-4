#pragma once
#include "Tarjeta.h"
class TarjetaCorporativa :
    public Tarjeta
{
private:
    int ruc;
public:
    TarjetaCorporativa(int codigo, string titular,int ruc);
    ~TarjetaCorporativa();
    int getRuc();
    string toJson();

};

