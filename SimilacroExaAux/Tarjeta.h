#pragma once
#include"Operacion.h"
#include"PagoViaje.h"
#include"Carga.h"
#include"ListaEnlazada.h"
#include"Traspaso.h"
#include"Abono.h"
class Tarjeta
{
protected:
	int codigo;
	string titular;
	int saldo;
	ListaEnlazada<Operacion>operaciones;
public:
	Tarjeta(int codigo,string titular);
	~Tarjeta();
	int getCod();
	string getTitular();
	virtual string toJson() = 0;
	virtual int limiteDiario() = 0;
	virtual int tarifaExtra() = 0; 
	virtual int bonificacion(int monto) = 0;
	virtual string tipo() = 0;
	void registrar(Operacion* o);
	void anularViaje(int idViaje);
	int totalBonificacion();
	int totalTarifas(); 
	int getSaldo(); 
	string descripcion();
	bool esIgual(const Tarjeta& otra);
	void heredarDe(Tarjeta* otra);        
	static string toJsonPtr(Tarjeta* t);
	static bool mayorCodigo(Tarjeta* a, Tarjeta* b);
	bool operator ==(Tarjeta* t);

};

