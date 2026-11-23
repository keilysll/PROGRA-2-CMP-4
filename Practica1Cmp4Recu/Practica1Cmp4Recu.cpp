/*
* Una red de transporte metropolitano necesita un sistema centralizado para administrar
las tarjetas de sus pasajeros, que realizan cargas de saldo, validaciones en torniquetes
y transferencias de saldo entre tarjetas, usando una unica instancia global (Singleton)
y manejo de excepciones ante reglas invalidas.
*/
#include "GestorTransporte.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include"TarjetaEstandar.h"
#include"TarjetaUniversitaria.h"
using namespace std;

int pregunta1()
{
	cout << "----Pregunta 1----" << endl;
	cout << "Resultado esperado:" << endl;
	cout << "{\"codigo\":50011,\"titular\":\"carla\",\"tipo\":\"estandar\",\"saldo\":65,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":100},{\"id\":2,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":15,\"linea\":\"linea-a\",\"bonificacion\":0,\"anulada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":20,\"linea\":\"linea-b\",\"bonificacion\":0,\"anulada\":false}]}" << endl;
	cout << "Error esperado: monto invalido en la operacion 4" << endl;
	TarjetaEstandar tarjeta(50011, "carla");
	string error;
	try {
		tarjeta.registrar(new Carga(1, 20261101, 100));
		tarjeta.registrar(new ValidacionViaje(2, 20261101, 15, "linea-a"));
		tarjeta.registrar(new ValidacionViaje(3, 20261101, 20, "linea-b"));
		// debe lanzar excepcion y no modificarse
		tarjeta.registrar(new ValidacionViaje(4, 20261101, 0, "linea-c"));
	}
	catch (exception& e) {
		error = e.what();
	}

	cout << "Resultado obtenido:" << endl;
	cout << tarjeta.toJson() << endl;
	cout << "Error obtenido: " << error << endl;

	if (error == "monto invalido en la operacion 4"
		&& tarjeta.toJson() == "{\"codigo\":50011,\"titular\":\"carla\",\"tipo\":\"estandar\",\"saldo\":65,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":100},{\"id\":2,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":15,\"linea\":\"linea-a\",\"bonificacion\":0,\"anulada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":20,\"linea\":\"linea-b\",\"bonificacion\":0,\"anulada\":false}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 30;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int pregunta2()
{
	cout << "----Pregunta 2----" << endl;
	cout << "Resultado esperado:" << endl;
	cout << "{\"codigo\":50022,\"titular\":\"diego\",\"tipo\":\"universitaria\",\"saldo\":153,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":45,\"linea\":\"linea-a\",\"bonificacion\":2,\"anulada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":4,\"linea\":\"linea-b\",\"bonificacion\":0,\"anulada\":false}]}" << endl;
	cout << "Error esperado: la operacion 4 supera el limite diario de la tarjeta 50022" << endl;

	Tarjeta* t1 = new TarjetaUniversitaria(50022, "diego");
	string error;
	try {
		t1->registrar(new Carga(1, 20261101, 200));
		t1->registrar(new ValidacionViaje(2, 20261101, 45, "linea-a"));
		t1->registrar(new ValidacionViaje(3, 20261101, 4, "linea-b"));
		// 45 + 4 + 60 = 109 > 100 (limite diario universitaria)
		t1->registrar(new ValidacionViaje(4, 20261101, 60, "linea-c"));
	}
	catch (exception& e) {
		error = e.what();
	}

	string salida = t1->toJson();
	cout << "Resultado obtenido:" << endl;
	cout << salida << endl;
	cout << "Error obtenido: " << error << endl;
	delete t1;

	if (error == "la operacion 4 supera el limite diario de la tarjeta 50022"
		&& salida == "{\"codigo\":50022,\"titular\":\"diego\",\"tipo\":\"universitaria\",\"saldo\":153,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":45,\"linea\":\"linea-a\",\"bonificacion\":2,\"anulada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"validacion\",\"monto\":4,\"linea\":\"linea-b\",\"bonificacion\":0,\"anulada\":false}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 30;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int pregunta3()
{
	cout << "----Pregunta 3----" << endl;
	cout << "Resultado esperado:" << endl;
	cout << "{\"nombre\":\"GestorTransporte\",\"tarjetas\":[{\"codigo\":50011,\"titular\":\"carla\",\"tipo\":\"estandar\",\"saldo\":79,\"operaciones\":[{\"id\":1,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":100},{\"id\":2,\"fecha\":20261105,\"tipo\":\"transferencia\",\"monto\":20,\"destino\":50099,\"tarifaExtra\":1}]},{\"codigo\":50099,\"titular\":\"metro-sa\",\"tipo\":\"corporativa\",\"ruc\":908070,\"saldo\":220,\"operaciones\":[{\"id\":2,\"fecha\":20261105,\"tipo\":\"abono\",\"monto\":20,\"origen\":50011},{\"id\":3,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":200}]}]}" << endl;
	cout << "Error esperado: saldo insuficiente en la tarjeta 50011 para la operacion 4" << endl;

	GestorTransporte& gestor = GestorTransporte::instancia();
	string error;
	try {
		gestor.registrarTarjeta(new TarjetaEstandar(50011, "carla"));
		gestor.registrarTarjeta(new TarjetaCorporativa(50099, "metro-sa", 908070));
		gestor.registrar(50011, new Carga(1, 20261105, 100));
		// saldo 100 - 20 - 1 = 79
		gestor.transferir(2, 20261105, 50011, 50099, 20);
		gestor.registrar(50099, new Carga(3, 20261105, 200));
		// saldo de 50011 es 79, con tarifa extra 1 necesita 80 para transferir 79
		gestor.transferir(4, 20261106, 50011, 50099, 79);
	}
	catch (exception& e) {
		error = e.what();
	}

	cout << "Resultado obtenido:" << endl;
	cout << gestor.toJson() << endl;
	cout << "Error obtenido: " << error << endl;

	if (error == "saldo insuficiente en la tarjeta 50011 para la operacion 4"
		&& gestor.toJson() == "{\"nombre\":\"GestorTransporte\",\"tarjetas\":[{\"codigo\":50011,\"titular\":\"carla\",\"tipo\":\"estandar\",\"saldo\":79,\"operaciones\":[{\"id\":1,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":100},{\"id\":2,\"fecha\":20261105,\"tipo\":\"transferencia\",\"monto\":20,\"destino\":50099,\"tarifaExtra\":1}]},{\"codigo\":50099,\"titular\":\"metro-sa\",\"tipo\":\"corporativa\",\"ruc\":908070,\"saldo\":220,\"operaciones\":[{\"id\":2,\"fecha\":20261105,\"tipo\":\"abono\",\"monto\":20,\"origen\":50011},{\"id\":3,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":200}]}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 40;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int main()
{
	int nota = pregunta1() + pregunta2()+pregunta3();
	cout << endl;
	cout << "====================" << endl;
	cout << "===> NOTA: " << nota << "/100" << endl;
	cout << "====================" << endl;
	system("pause");
	return 0;
}