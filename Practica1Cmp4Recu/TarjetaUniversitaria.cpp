#include "TarjetaUniversitaria.h"

TarjetaUniversitaria::TarjetaUniversitaria(int codigo, string titular):Tarjeta(codigo,titular)
{
    this->tipo = "universitaria";
}

int TarjetaUniversitaria::limiteDiario()
{
    return 100;
}

int TarjetaUniversitaria::porcentajeBonificacion()
{
    return 5;
}

string TarjetaUniversitaria::toJson()
{
    stringstream ss;
    ss << "{\"codigo\":" << codigo << ",\"titular\":\"" << titular << "\",\"tipo\":\"" << tipo << "\",\"saldo\":" << saldo << ",\"operaciones\":" << operaciones.toJson(Operacion::toJsonPtr) << "}";
    return ss.str();
}
