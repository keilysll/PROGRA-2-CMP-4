#pragma once
#include"Tarjeta.h"
#include"TarjetaCorporativa.h"
#include"TarjetaEstandar.h"
#include"TarjetaUniversitaria.h"
#include"ListaEnlazada.h"
class GestorTransporte
{
private:
	string nombre;
	ListaEnlazada<Tarjeta> tarjetas;
public:
	~GestorTransporte();
	static GestorTransporte& instancia();
	void registrarTarjeta(Tarjeta* t);
	void registrar(int codigo, Operacion* o);
	void transferir(int id, int fecha, int codOrigen, int codDestino, int monto);
	string toJson();
private:
	GestorTransporte(string nombre);
};

