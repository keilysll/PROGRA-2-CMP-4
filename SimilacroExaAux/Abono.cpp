#include "Abono.h"

Abono::Abono(int id, int fecha, int monto, int origen) :Operacion(id, fecha, monto) 
{ 
	this->origen = origen;
}
string Abono::tipo() 
{ 
	return "abono"; 
}
string Abono::toJson() {
	stringstream ss;
	ss << "{\"id\":" << id << ",\"fecha\":" << fecha << ",\"tipo\":\"" << tipo()<< "\",\"monto\":" << monto << ",\"origen\":" << origen << "}";
	return ss.str();
}
int Abono::efecto() 
{
	return +monto; 
}