#pragma once
#include "Usuario.h"
class UsuarioPro :
    public Usuario
{
private:
    int creditos;
public:
    UsuarioPro(string nombre, int creditos);
    ~UsuarioPro();
    string toJson();
    int TokensDisp();
    void validarPlan(Solicitud* s, int costo);
    void descontar(Solicitud* s, int costo);
};

