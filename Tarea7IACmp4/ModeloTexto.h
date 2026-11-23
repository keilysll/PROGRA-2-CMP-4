#pragma once
#include "Modelo.h"
class ModeloTexto :
    public Modelo
{
public:
    ModeloTexto(string nombre, int precio);
    ~ModeloTexto();
    string toJson() const;
    int costo(int tokens);
};

