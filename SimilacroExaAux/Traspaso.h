#pragma once
#include "Operacion.h"
class Traspaso : public Operacion
{
private:
    int destino;
    int tarifa;
public:
    Traspaso(int id, int fecha, int monto, int destino);
    string tipo();
    string toJson();
    int efecto();
    int getDestino(); 
    int getTarifa(); 
    void setTarifa(int tarifa);
};

