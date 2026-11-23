#pragma once
#include "Transaccion.h"
class InscripcionTorneo :
    public Transaccion
{
private:
    string torneo;
    string reembolsada;
public:
    InscripcionTorneo(int id, int fecha, int cantidad,string torneo);
    ~InscripcionTorneo();
    string getTorneo();
    string toJson();
    int efecto();
};

