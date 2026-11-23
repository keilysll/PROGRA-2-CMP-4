#pragma once
#include "Operacion.h"
class Transferencia :
    public Operacion
{   private:
    int destino;
    int tarifaExtra;

    public:
        Transferencia(int id, int fecha, int monto,int destino,int tarijaExtra);
        ~Transferencia();
        int getDestino();
        int getTarifa();
        string toJson();
        int efectoSaldo();
};

