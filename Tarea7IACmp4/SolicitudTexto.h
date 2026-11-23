#pragma once
#include "Solicitud.h"
class SolicitudTexto :
    public Solicitud
{
public:
    SolicitudTexto(int id,string modelo,int tokens);
    ~SolicitudTexto();
    string toJson() const;

};

