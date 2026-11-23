#pragma once
#include "Usuario.h"
class UsuarioGratis :
    public Usuario
{
public:
    UsuarioGratis(string nombre);
    ~UsuarioGratis();
    string toJson();
    int TokensDisp();
    void validarPlan(Solicitud* s, int costo);
    void descontar(Solicitud* s, int costo);
};

