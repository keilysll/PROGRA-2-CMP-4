#pragma once
#include "Transaccion.h"
class Envio :
    public Transaccion
{
private:

    int receptor;
    int recarga;
public:
    Envio(int id, int fecha, int cantidad, int receptor);
    ~Envio();
    string toJson();
    void setRecargo(int recargo);
    int efecto();
  

};

