#pragma once
#include"Solicitud.h"
#include"SolicitudTexto.h"
#include"Repositorio.h"
#include"SolicitudImagen.h"
#include"Catalogo.h"
class Usuario
{
protected:
	string nombre;
	Repositorio<Solicitud>solicitudes;
	int tokDisp;
public:
	Usuario(string nombre);
	~Usuario();
	string getNombre();
	virtual string toJson() = 0;
	virtual int TokensDisp() = 0;
	void procesar(Solicitud* s);
	virtual void validarPlan(Solicitud* s, int costo) = 0;   // reglas de cada plan (lanza si no cumple)
	virtual void descontar(Solicitud* s, int costo) = 0;     // qué se le descuenta al usuario
	int ingresoTotal();
	int tokensProcesados();
	string getClave() const;
};

