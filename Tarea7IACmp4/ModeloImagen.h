#pragma once
#include "Modelo.h"
class ModeloImagen :
    public Modelo
{
public:
    ModeloImagen(string nombre, int precio);
    ~ModeloImagen();
    string toJson() const;
    int costo(int imagenes);
};



