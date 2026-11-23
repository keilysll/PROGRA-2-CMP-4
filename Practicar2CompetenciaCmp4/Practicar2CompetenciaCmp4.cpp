/*
* Una plataforma de videojuegos competitivos requiere una aplicacion para administrar
las cuentas de sus jugadores, que realizan compras de gemas, inscripciones a torneos
y envios de gemas entre cuentas, con manejo de excepciones ante reglas invalidas.
*/
//#include "Plataforma.h"
#include <iostream>
#include <exception>
#include <cstdlib>
#include"CuentaNovata.h"
#include"CuentaVeterana.h"
#include"Plataforma.h"
using namespace std;

int pregunta1()
{
	cout << "----Pregunta 1----" << endl;
	cout << "Resultado esperado:" << endl;
	cout << "{\"idCuenta\":1001,\"alias\":\"shadow\",\"rango\":\"novata\",\"balance\":320,\"transacciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"compra\",\"cantidad\":500},{\"id\":2,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":100,\"torneo\":\"copa-oro\",\"cashback\":0,\"reembolsada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":80,\"torneo\":\"liga-rapida\",\"cashback\":0,\"reembolsada\":false}]}" << endl;
	cout << "Error esperado: cantidad invalida en la operacion 4" << endl;
	CuentaNovata cuenta(1001, "shadow");
	string error;
	try {
		cuenta.registrar(new CompraGemas(1, 20261101, 500));
		cuenta.registrar(new InscripcionTorneo(2, 20261101, 100, "copa-oro"));
		cuenta.registrar(new InscripcionTorneo(3, 20261101, 80, "liga-rapida"));
		// cantidad <= 0 debe lanzar excepcion
		cuenta.registrar(new InscripcionTorneo(4, 20261101, -10, "copa-plata"));
	}
	catch (exception& e) {
		error = e.what();
	}

	cout << "Resultado obtenido:" << endl;
	cout << cuenta.toJson() << endl;
	cout << "Error obtenido: " << error << endl;

	if (error == "cantidad invalida en la operacion 4"
		&& cuenta.toJson() == "{\"idCuenta\":1001,\"alias\":\"shadow\",\"rango\":\"novata\",\"balance\":320,\"transacciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"compra\",\"cantidad\":500},{\"id\":2,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":100,\"torneo\":\"copa-oro\",\"cashback\":0,\"reembolsada\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":80,\"torneo\":\"liga-rapida\",\"cashback\":0,\"reembolsada\":false}]}")
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
	cout << "{\"idCuenta\":1002,\"alias\":\"nova\",\"rango\":\"veterana\",\"balance\":354,\"transacciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"compra\",\"cantidad\":600},{\"id\":2,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":250,\"torneo\":\"copa-oro\",\"cashback\":4,\"reembolsada\":false}]}" << endl;
	cout << "Error esperado: la operacion 3 supera el tope diario de la cuenta 1002" << endl;
	CuentaJugador* c1 = new CuentaVeterana(1002, "nova");
	string error;
	try {
		c1->registrar(new CompraGemas(1, 20261101, 600));
		c1->registrar(new InscripcionTorneo(2, 20261101, 250, "copa-oro"));
		// 250 + 600 = 850 > 800 (tope diario veterana)
		c1->registrar(new InscripcionTorneo(3, 20261101, 600, "masters"));
	}
	catch (exception& e) {
		error = e.what();
	}

	string salida = c1->toJson();
	cout << "Resultado obtenido:" << endl;
	cout << salida << endl;
	cout << "Error obtenido: " << error << endl;
	delete c1;

	if (error == "la operacion 3 supera el tope diario de la cuenta 1002"
		&& salida == "{\"idCuenta\":1002,\"alias\":\"nova\",\"rango\":\"veterana\",\"balance\":354,\"transacciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"compra\",\"cantidad\":600},{\"id\":2,\"fecha\":20261101,\"tipo\":\"inscripcion\",\"cantidad\":250,\"torneo\":\"copa-oro\",\"cashback\":4,\"reembolsada\":false}]}")
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
	cout << "{\"nombre\":\"ArenaGG\",\"cuentas\":[{\"idCuenta\":1001,\"alias\":\"shadow\",\"rango\":\"novata\",\"balance\":395,\"transacciones\":[{\"id\":1,\"fecha\":20261105,\"tipo\":\"compra\",\"cantidad\":500},{\"id\":2,\"fecha\":20261105,\"tipo\":\"envio\",\"cantidad\":100,\"receptor\":1009,\"recargo\":5}]},{\"idCuenta\":1009,\"alias\":\"clan-alfa\",\"rango\":\"club\",\"claveClub\":\"ALFA2026\",\"balance\":1100,\"transacciones\":[{\"id\":2,\"fecha\":20261105,\"tipo\":\"recepcion\",\"cantidad\":100,\"emisor\":1001},{\"id\":3,\"fecha\":20261105,\"tipo\":\"compra\",\"cantidad\":1000}]}]}" << endl;
	cout << "Error esperado: cuenta 9999 no encontrada" << endl;

	Plataforma plataforma("ArenaGG");
	string error;
	try {
		plataforma.registrarCuenta(new CuentaNovata(1001, "shadow"));
		plataforma.registrarCuenta(new CuentaClub(1009, "clan-alfa", "ALFA2026"));
		plataforma.registrar(1001, new CompraGemas(1, 20261105, 500));
		plataforma.enviar(2, 20261105, 1001, 1009, 100);
		plataforma.registrar(1009, new CompraGemas(3, 20261105, 1000));
		// receptor inexistente debe lanzar excepcion
		plataforma.enviar(4, 20261105, 1001, 9999, 10);
	}
	catch (exception& e) {
		error = e.what();
	}

	cout << "Resultado obtenido:" << endl;
	cout << plataforma.toJson() << endl;
	cout << "Error obtenido: " << error << endl;

	if (error == "cuenta 9999 no encontrada"
		&& plataforma.toJson() == "{\"nombre\":\"ArenaGG\",\"cuentas\":[{\"idCuenta\":1001,\"alias\":\"shadow\",\"rango\":\"novata\",\"balance\":395,\"transacciones\":[{\"id\":1,\"fecha\":20261105,\"tipo\":\"compra\",\"cantidad\":500},{\"id\":2,\"fecha\":20261105,\"tipo\":\"envio\",\"cantidad\":100,\"receptor\":1009,\"recargo\":5}]},{\"idCuenta\":1009,\"alias\":\"clan-alfa\",\"rango\":\"club\",\"claveClub\":\"ALFA2026\",\"balance\":1100,\"transacciones\":[{\"id\":2,\"fecha\":20261105,\"tipo\":\"recepcion\",\"cantidad\":100,\"emisor\":1001},{\"id\":3,\"fecha\":20261105,\"tipo\":\"compra\",\"cantidad\":1000}]}]}")
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