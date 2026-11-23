#pragma once
#include"Modelo.h"
#include"ModeloImagen.h"
#include"ModeloTexto.h"
#include"Repositorio.h"
class Catalogo
{
private:
	Repositorio<Modelo> modelos;
public:
	~Catalogo();
	static Catalogo& getInst();
	void registrar(Modelo* m);
	Modelo* buscar(string nombre);
	void limpiar();
	string toJson();

private:
	Catalogo();
};

