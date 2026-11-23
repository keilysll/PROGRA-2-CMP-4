#pragma once
#include "Solicitud.h"
class SolicitudImagen :
    public Solicitud
{
public:

    SolicitudImagen(int id, string modelo, int tokens);
    ~SolicitudImagen();
    string toJson() const;
};

