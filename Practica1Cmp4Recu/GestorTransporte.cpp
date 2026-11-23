#include "GestorTransporte.h"



GestorTransporte::~GestorTransporte()
{
}

GestorTransporte& GestorTransporte::instancia()
{
    static GestorTransporte inst("GestorTransporte");
    return inst;
}

void GestorTransporte::registrarTarjeta(Tarjeta* t)
{
    tarjetas.registrar(t);
}

void GestorTransporte::registrar(int codigo, Operacion* o)
{
    Tarjeta* t = tarjetas.buscar(new TarjetaEstandar(codigo));
    t->registrar(o);
}

void GestorTransporte::transferir(int id, int fecha, int codOrigen, int codDestino, int monto)
{
    Tarjeta* Torigen = tarjetas.buscar(new TarjetaEstandar(codOrigen));
    Tarjeta* Tdestino = tarjetas.buscar(new TarjetaEstandar(codDestino));
    Torigen->registrar(new Transferencia(id, fecha, monto, codDestino, Torigen->tarifaExtra()));
    Tdestino->registrar(new Abono(id, fecha, monto, codOrigen));

}

string GestorTransporte::toJson()
{
    stringstream ss;
    ss << "{\"nombre\":\"" << nombre << "\",\"tarjetas\":" << tarjetas.toJson(Tarjeta::toJsonPtr) << "}";
    return ss.str();
}


GestorTransporte::GestorTransporte(string nombre)
{
    this->nombre = nombre;
}
