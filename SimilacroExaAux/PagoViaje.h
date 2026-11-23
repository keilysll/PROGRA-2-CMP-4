#pragma once
#include "Operacion.h"
class PagoViaje :
    public Operacion
{
private:
    string linea;
    int bonificado;
    string anulado;
public:
    PagoViaje(int id, int fecha, int monto,string linea);
    ~PagoViaje();
    string getLinea();
    string toJson();
    string tipo();
    int getBonificado();
    void setBonific(int bonificacion);
    int efecto();
    bool estaAnulado();
    void anular();

};

