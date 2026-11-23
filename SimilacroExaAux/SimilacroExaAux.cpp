/*
Una red de transporte urbano desea un sistema para controlar las tarjetas de sus usuarios,
que realizan cargas de saldo, pagos de viaje y traspasos de saldo entre tarjetas.
Se debe considerar:
- Registrar tarjetas en la red (ordenadas por codigo, sin codigos repetidos).
- Registrar cargas y pagos de viaje en una tarjeta, y anular pagos de viaje.
- Realizar traspasos de saldo entre tarjetas de la red.
- Mejorar una tarjeta estandar a estudiantil.
- Obtener reportes y una descripcion breve de cada tarjeta.

JERARQUIA OBLIGATORIA
- Tarjeta (abstracta) con metodos virtuales puros: limiteDiario(), tarifaExtra(), bonificacion(monto), tipo().
	- TarjetaEstandar:     limite diario 100, tarifa extra por traspaso 1, sin bonificacion.
	- TarjetaEstudiantil:  limite diario 300, sin tarifa extra, bonificacion en pagos de viaje de
						   1 Bs por cada 20 Bs pagados (division entera), abonada al saldo.
		- TarjetaCorporativa(codigo, titular, nit): hereda de TarjetaEstudiantil (misma bonificacion
						   y tarifa extra), pero su limite diario es 1500. Su JSON incluye "nit".
- Operacion (abstracta) con metodo virtual puro tipo().
	- Carga, Abono (ingresos);  PagoViaje, Traspaso (egresos).
No se permite distinguir tipos de tarjeta o de operacion con atributos de texto, enumeraciones
ni if/switch sobre tipo(): el tipo real se identifica con dynamic_cast<>, que es OBLIGATORIO en:
  * Tarjeta::registrar (saber que clase de operacion llega),
  * anularViaje (solo se puede anular un PagoViaje),
  * mejorarTarjeta (solo se puede mejorar una TarjetaEstandar),
  * los reportes de bonificacion y tarifas (datos que solo existen en PagoViaje / Traspaso),
  * contar<T>() (una TarjetaCorporativa tambien cuenta como TarjetaEstudiantil).

REGLAS (todos los montos son enteros, en Bs)
Al registrar un egreso se valida en este orden; si una regla falla se lanza la excepcion
y NO se modifica nada:
1. El monto debe ser mayor a 0: "monto invalido en la operacion <id>" (tambien en ingresos).
2. Los egresos del dia (pagos de viaje no anulados + traspasos enviados con la misma fecha,
   sin contar tarifas) no pueden superar el limite diario:
   "la operacion <id> supera el limite diario de la tarjeta <codigo>".
3. El saldo debe cubrir monto + tarifa:
   "saldo insuficiente en la tarjeta <codigo> para la operacion <id>".
Una operacion que falla no se registra y no cuenta para el limite.
Traspasos: primero se buscan origen y destino ("tarjeta <codigo> no encontrada");
se registra "traspaso" en el origen y "abono" (mismo id) en el destino.
Anulacion de un pago de viaje (anularViaje(idViaje)):
   "operacion <id> no encontrada en la tarjeta <codigo>"
   "la operacion <id> no es un pago de viaje"
   "el viaje <id> ya fue anulado"
   Al anular se devuelve al saldo el monto menos la bonificacion recibida; el viaje queda en el
   detalle con "anulado":true, deja de contar para el limite diario y su bonificacion deja de
   contar en los reportes.
Mejorar tarjeta (mejorarTarjeta(codigo)): "la tarjeta <codigo> no es estandar". La tarjeta
   estudiantil conserva codigo, titular, saldo y operaciones, y desde ese momento aplica las
   reglas estudiantiles.

INTERFAZ REQUERIDA
Operaciones: Carga(id, fecha, monto), PagoViaje(id, fecha, monto, linea).
   (Traspaso y Abono los crea la red al traspasar.)
Tarjeta:
   TarjetaEstandar(codigo, titular), TarjetaEstudiantil(codigo, titular),
   TarjetaCorporativa(codigo, titular, nit); toda tarjeta inicia con saldo 0.
   void registrar(Operacion* op)     la tarjeta pasa a ser duena de la operacion
									 (si falla, lo libera)
   void anularViaje(int idViaje)
   int totalBonificacion()           bonificacion de pagos de viaje no anulados
   string descripcion()              ej: [estandar] 50011 ana: 20 Bs
   bool esIgual(const Tarjeta& otra) compara solo el codigo
   string toJson()
RedTransporte(nombre):
   void registrarTarjeta(Tarjeta* t) "la tarjeta <codigo> ya existe"
   Tarjeta* buscar(int codigo)       "tarjeta <codigo> no encontrada"
   void registrar(int codigo, Operacion* op)
   void traspasar(int id, int fecha, int origen, int destino, int monto)
   void anularViaje(int codigo, int idViaje)
   void mejorarTarjeta(int codigo)
   int totalBonificacion()           suma de la bonificacion vigente de todas las tarjetas
   int totalTarifas()                suma de tarifas cobradas en traspasos
   int saldoTotal()                  suma de saldos
   string tarjetaMayorSaldo()        titular de la tarjeta con mayor saldo
   template <class T> int contar()   tarjetas cuyo tipo real es T o deriva de T
   string toJson()
*/
#include "RedTransporte.h"
#include "Tarjeta.h"
#include "TarjetaEstandar.h"
#include "TarjetaEstudiantil.h"
//#include "TarjetaCorporativa.h"
#include <iostream>
using namespace std;

int pregunta1()
{
	cout << "----Pregunta 1----" << endl;
	cout<<"{\"codigo\":50011,\"titular\":\"ana\",\"tipo\":\"estandar\",\"saldo\":30,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":40,\"linea\":\"linea-1\",\"bonificacion\":0,\"anulado\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":50,\"linea\":\"linea-2\",\"bonificacion\":0,\"anulado\":false},{\"id\":4,\"fecha\":20261102,\"tipo\":\"pagoviaje\",\"monto\":80,\"linea\":\"linea-3\",\"bonificacion\":0,\"anulado\":false}]}"
		"{\"codigo\":50022,\"titular\":\"luis\",\"tipo\":\"estudiantil\",\"saldo\":100,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":45,\"linea\":\"linea-1\",\"bonificacion\":2,\"anulado\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":19,\"linea\":\"linea-2\",\"bonificacion\":0,\"anulado\":false},{\"id\":4,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":40,\"linea\":\"linea-3\",\"bonificacion\":2,\"anulado\":false}]}"<<endl;
	string error;
	// Crear tarjetas(codigo, titular)
	TarjetaEstandar ana(50011, "ana");
	TarjetaEstudiantil luis(50022, "luis");
	try {
		// Carga(id, fecha, monto)
		ana.registrar(new Carga(1, 20261101, 200));
		// PagoViaje(id, fecha, monto, linea)
		ana.registrar(new PagoViaje(2, 20261101, 40, "linea-1"));
		ana.registrar(new PagoViaje(3, 20261101, 50, "linea-2"));
		// otro dia: el limite diario se reinicia
		ana.registrar(new PagoViaje(4, 20261102, 80, "linea-3"));
		// estudiantil: bonificacion de 1 Bs por cada 20 Bs pagados
		luis.registrar(new Carga(1, 20261101, 200));
		luis.registrar(new PagoViaje(2, 20261101, 45, "linea-1"));
		luis.registrar(new PagoViaje(3, 20261101, 19, "linea-2"));
		luis.registrar(new PagoViaje(4, 20261101, 40, "linea-3"));
	}
	catch (exception& e) {
		error = e.what();
	}
	string result = ana.toJson() + luis.toJson();
	cout << result << endl;
	cout << error << endl;
	if (error == "" && result == "{\"codigo\":50011,\"titular\":\"ana\",\"tipo\":\"estandar\",\"saldo\":30,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":40,\"linea\":\"linea-1\",\"bonificacion\":0,\"anulado\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":50,\"linea\":\"linea-2\",\"bonificacion\":0,\"anulado\":false},{\"id\":4,\"fecha\":20261102,\"tipo\":\"pagoviaje\",\"monto\":80,\"linea\":\"linea-3\",\"bonificacion\":0,\"anulado\":false}]}"
		"{\"codigo\":50022,\"titular\":\"luis\",\"tipo\":\"estudiantil\",\"saldo\":100,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":200},{\"id\":2,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":45,\"linea\":\"linea-1\",\"bonificacion\":2,\"anulado\":false},{\"id\":3,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":19,\"linea\":\"linea-2\",\"bonificacion\":0,\"anulado\":false},{\"id\":4,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":40,\"linea\":\"linea-3\",\"bonificacion\":2,\"anulado\":false}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 20;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int pregunta2()
{
	cout << "----Pregunta 2----" << endl;
	string error1, error2, error3, error4;
	TarjetaEstandar tarjeta(50033, "rosa");
	try {
		tarjeta.registrar(new Carga(1, 20261101, 150));
		tarjeta.registrar(new PagoViaje(2, 20261101, 80, "linea-1"));
		// 80 + 30 supera el limite diario de 100
		tarjeta.registrar(new PagoViaje(3, 20261101, 30, "linea-2"));
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		// otro dia: no supera el limite, pero el saldo no alcanza
		tarjeta.registrar(new PagoViaje(4, 20261102, 80, "linea-3"));
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		tarjeta.registrar(new Carga(5, 20261102, 0));
	}
	catch (exception& e) {
		error3 = e.what();
	}
	try {
		// la operacion 3 fallo, por lo tanto no cuenta para el limite: 80 + 20 = 100
		tarjeta.registrar(new PagoViaje(6, 20261101, 20, "linea-4"));
	}
	catch (exception& e) {
		error4 = e.what();
	}
	string result = tarjeta.toJson();
	cout << result << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	cout << error4 << endl;
	if (error1 == "la operacion 3 supera el limite diario de la tarjeta 50033"
		&& error2 == "saldo insuficiente en la tarjeta 50033 para la operacion 4"
		&& error3 == "monto invalido en la operacion 5"
		&& error4 == ""
		&& result == "{\"codigo\":50033,\"titular\":\"rosa\",\"tipo\":\"estandar\",\"saldo\":50,\"operaciones\":[{\"id\":1,\"fecha\":20261101,\"tipo\":\"carga\",\"monto\":150},{\"id\":2,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":80,\"linea\":\"linea-1\",\"bonificacion\":0,\"anulado\":false},{\"id\":6,\"fecha\":20261101,\"tipo\":\"pagoviaje\",\"monto\":20,\"linea\":\"linea-4\",\"bonificacion\":0,\"anulado\":false}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 20;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int pregunta3()
{
	cout << "----Pregunta 3----" << endl;
	string error1, error2, error3, error4;
	TarjetaEstudiantil tarjeta(50044, "eva");
	int bonificacion = -1;
	try {
		tarjeta.registrar(new Carga(1, 20261110, 400));
		// bonificacion 6 -> saldo 286
		tarjeta.registrar(new PagoViaje(2, 20261110, 120, "linea-1"));
		// bonificacion 4 -> saldo 210
		tarjeta.registrar(new PagoViaje(3, 20261110, 80, "linea-2"));
		// devuelve 120 - 6 -> saldo 324
		tarjeta.anularViaje(2);
		// el viaje 2 anulado ya no cuenta: 80 + 220 = 300 <= 300; bonificacion 11 -> saldo 115
		tarjeta.registrar(new PagoViaje(4, 20261110, 220, "linea-3"));
		// bonificacion de viajes no anulados: 4 + 11
		bonificacion = tarjeta.totalBonificacion();
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		tarjeta.anularViaje(2);
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		tarjeta.anularViaje(1);
	}
	catch (exception& e) {
		error3 = e.what();
	}
	try {
		tarjeta.anularViaje(9);
	}
	catch (exception& e) {
		error4 = e.what();
	}
	string result = tarjeta.toJson();
	cout << result << endl;
	cout << "totalBonificacion: " << bonificacion << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	cout << error4 << endl;
	if (error1 == "" && error2 == "el viaje 2 ya fue anulado"
		&& error3 == "la operacion 1 no es un pago de viaje"
		&& error4 == "operacion 9 no encontrada en la tarjeta 50044"
		&& bonificacion == 15
		&& result == "{\"codigo\":50044,\"titular\":\"eva\",\"tipo\":\"estudiantil\",\"saldo\":115,\"operaciones\":[{\"id\":1,\"fecha\":20261110,\"tipo\":\"carga\",\"monto\":400},{\"id\":2,\"fecha\":20261110,\"tipo\":\"pagoviaje\",\"monto\":120,\"linea\":\"linea-1\",\"bonificacion\":6,\"anulado\":true},{\"id\":3,\"fecha\":20261110,\"tipo\":\"pagoviaje\",\"monto\":80,\"linea\":\"linea-2\",\"bonificacion\":4,\"anulado\":false},{\"id\":4,\"fecha\":20261110,\"tipo\":\"pagoviaje\",\"monto\":220,\"linea\":\"linea-3\",\"bonificacion\":11,\"anulado\":false}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 25;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}
int pregunta4()
{
	cout << "----Pregunta 4----" << endl;
	string error1, error2, error3, error4, error5;
	// Crear red(nombre)
	RedTransporte r("MetroBus");
	int bonificacion = -1, tarifas = -1, saldoTotal = -1, estudiantiles = -1, corporativas = -1, estandar = -1;
	string mayor, texto, result;
	bool igual = false;
	try {
		// registrarTarjeta(tarjeta): se registran desordenadas, la red las ordena por codigo
		r.registrarTarjeta(new TarjetaEstudiantil(50022, "luis"));
		// TarjetaCorporativa(codigo, titular, nit)
		r.registrarTarjeta(new TarjetaCorporativa(50099, "acme", 1020));
		r.registrarTarjeta(new TarjetaEstandar(50011, "ana"));
		r.registrarTarjeta(new TarjetaEstandar(50011, "otro"));
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		// registrar(codigoTarjeta, operacion)
		r.registrar(50011, new Carga(1, 20261105, 300));
		// traspasar(id, fecha, origen, destino, monto): ana es estandar, tarifa 1
		r.traspasar(2, 20261105, 50011, 50099, 70);
		// destino inexistente: no se modifica ninguna tarjeta
		r.traspasar(8, 20261105, 50011, 59999, 10);
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		// ana es estandar: 70 + 40 supera el limite de 100
		r.traspasar(3, 20261105, 50011, 50022, 40);
	}
	catch (exception& e) {
		error3 = e.what();
	}
	try {
		r.mejorarTarjeta(50022);
	}
	catch (exception& e) {
		error4 = e.what();
	}
	try {
		r.mejorarTarjeta(50011);
		// ana ahora es estudiantil: limite 300 y sin tarifa
		r.traspasar(4, 20261105, 50011, 50022, 50);
		r.registrar(50099, new Carga(5, 20261105, 1000));
		// la corporativa tiene limite 1500 (una estudiantil no podria pagar 400)
		r.registrar(50099, new PagoViaje(6, 20261105, 400, "linea-corp"));
		r.registrar(50022, new PagoViaje(7, 20261105, 40, "linea-1"));
		// anularViaje(codigoTarjeta, idViaje)
		r.anularViaje(50022, 7);
		bonificacion = r.totalBonificacion();
		tarifas = r.totalTarifas();
		saldoTotal = r.saldoTotal();
		mayor = r.tarjetaMayorSaldo();
		estudiantiles = r.contar<TarjetaEstudiantil>();
		corporativas = r.contar<TarjetaCorporativa>();
		estandar = r.contar<TarjetaEstandar>();
		texto = r.buscar(50011)->descripcion() + " | " + r.buscar(50022)->descripcion() + " | " + r.buscar(50099)->descripcion();
		// esIgual compara solo el codigo, aunque los tipos de tarjeta sean distintos
		TarjetaEstandar copia(50099, "otro");
		igual = r.buscar(50099)->esIgual(copia);
		result = r.toJson();
	}
	catch (exception& e) {
		error5 = e.what();
	}
	cout << result << endl;
	cout << texto << endl;
	cout << "bonificacion: " << bonificacion << " tarifas: " << tarifas << " saldoTotal: " << saldoTotal << " mayor: " << mayor << endl;
	cout << "estudiantiles: " << estudiantiles << " corporativas: " << corporativas << " estandar: " << estandar << " igual: " << igual << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	cout << error4 << endl;
	cout << error5 << endl;
	if (error1 == "la tarjeta 50011 ya existe" && error2 == "tarjeta 59999 no encontrada"
		&& error3 == "la operacion 3 supera el limite diario de la tarjeta 50011"
		&& error4 == "la tarjeta 50022 no es estandar" && error5 == ""
		&& bonificacion == 20 && tarifas == 1 && saldoTotal == 919 && mayor == "acme"
		&& estudiantiles == 3 && corporativas == 1 && estandar == 0 && igual == true
		&& texto == "[estudiantil] 50011 ana: 179 Bs | [estudiantil] 50022 luis: 50 Bs | [corporativa] 50099 acme: 690 Bs"
		&& result == "{\"nombre\":\"MetroBus\",\"tarjetas\":["
		"{\"codigo\":50011,\"titular\":\"ana\",\"tipo\":\"estudiantil\",\"saldo\":179,\"operaciones\":[{\"id\":1,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":300},{\"id\":2,\"fecha\":20261105,\"tipo\":\"traspaso\",\"monto\":70,\"destino\":50099,\"tarifa\":1},{\"id\":4,\"fecha\":20261105,\"tipo\":\"traspaso\",\"monto\":50,\"destino\":50022,\"tarifa\":0}]},"
		"{\"codigo\":50022,\"titular\":\"luis\",\"tipo\":\"estudiantil\",\"saldo\":50,\"operaciones\":[{\"id\":4,\"fecha\":20261105,\"tipo\":\"abono\",\"monto\":50,\"origen\":50011},{\"id\":7,\"fecha\":20261105,\"tipo\":\"pagoviaje\",\"monto\":40,\"linea\":\"linea-1\",\"bonificacion\":2,\"anulado\":true}]},"
		"{\"codigo\":50099,\"titular\":\"acme\",\"tipo\":\"corporativa\",\"nit\":1020,\"saldo\":690,\"operaciones\":[{\"id\":2,\"fecha\":20261105,\"tipo\":\"abono\",\"monto\":70,\"origen\":50011},{\"id\":5,\"fecha\":20261105,\"tipo\":\"carga\",\"monto\":1000},{\"id\":6,\"fecha\":20261105,\"tipo\":\"pagoviaje\",\"monto\":400,\"linea\":\"linea-corp\",\"bonificacion\":20,\"anulado\":false}]}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 35;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}
int main()
{
	int nota = pregunta1() + pregunta2() +pregunta3() + pregunta4();
	cout << endl;
	cout << "====================" << endl;
	cout << "===> NOTA: " << nota << "/100" << endl;
	cout << "====================" << endl;
	system("pause");
	return 0;
}