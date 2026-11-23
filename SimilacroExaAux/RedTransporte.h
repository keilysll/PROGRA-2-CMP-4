#pragma once
#include"ListaEnlazada.h"
#include"Tarjeta.h"
#include"TarjetaEstandar.h"
#include"TarjetaEstudiantil.h"
#include"TarjetaCorporativa.h"
class RedTransporte
{
private:
	string nombre;
	ListaEnlazada<Tarjeta> tarjetas;
public:
	RedTransporte(string nombre);
	~RedTransporte();
	void registrarTarjeta(Tarjeta* t);
	void registrar(int CodTarjeta, Operacion* o);
	void traspasar(int id,int fecha, int orige, int destino,int monto);
	void anularViaje(int codTarjeta, int idViaje);
	void mejorarTarjeta(int codTarjeta);
	template <class T> int contar();
	Tarjeta* buscar(int codTarjeta);
	int totalBonificacion(); 
	int totalTarifas(); 
	int saldoTotal();
	string tarjetaMayorSaldo();
	string toJson();
	int posicion(int codTarjeta);

};

template<class T>
inline int RedTransporte::contar()
{
	int cont = 0;
	for (int i = 0; i < tarjetas.getTam(); i++)
	{
		if (dynamic_cast<T*>(tarjetas.obtener(i)) != NULL)
		{
			cont++;
		}
	}
	return cont;
}
