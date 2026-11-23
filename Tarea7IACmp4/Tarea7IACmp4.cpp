/*
Una plataforma de inteligencia artificial en la nube ofrece modelos que generan texto
o imagenes y cobra a sus usuarios segun el consumo. Se debe considerar:

- Implementar una clase plantilla Repositorio<T> (un solo tipo parametrizado) que almacena
punteros T* en orden de llegada y es duena de sus elementos (los libera al destruirse).
El tipo T debe proveer: string getClave() const y string toJson() const.
* void agregar(T* valor): si ya existe un elemento con la misma clave libera valor y lanza
"clave duplicada: <clave>".
* T* buscar(string clave): si no existe lanza "clave no encontrada: <clave>".
* int size(); T* obtener(int posicion).
* string toJson(): "[" + valor->toJson() de cada elemento separados por "," + "]".
* 
* 
- Un Catalogo unico (Singleton) de modelos, guardados en un Repositorio por nombre:
* ModeloTexto(nombre, precio): precio en Bs por cada 1000 tokens o fraccion
(ej. 2500 tokens = 3 bloques).
* ModeloImagen(nombre, precio): precio en Bs por imagen.
* Catalogo::getInst(), registrar(modelo), buscar(nombre), limpiar(), toJson().
- Usuarios (clase abstracta Usuario):
* UsuarioGratis(nombre): tiene 10000 tokens disponibles, no paga (costo 0) y no puede
generar imagenes.
* UsuarioPro(nombre, creditos): paga cada solicitud con sus creditos (Bs).
- Solicitudes (clase abstracta Solicitud):
* SolicitudTexto(id, modelo, tokens) y SolicitudImagen(id, modelo, imagenes).
- procesar(solicitud) en el usuario valida en este orden:
1. cantidad > 0: "cantidad invalida en la solicitud <id>"
2. el modelo existe en el catalogo (excepcion del Repositorio)
3. el modelo es del tipo de la solicitud (texto con texto, imagen con imagen):
"el modelo <m> no es compatible con la solicitud <id>"
4. reglas del plan:
"el plan gratis no permite imagenes (solicitud <id>)"
"<usuario> supero su cuota de tokens en la solicitud <id>"
"creditos insuficientes <usuario> en la solicitud <id>"
Si la solicitud es valida se descuenta del usuario, se guarda su costo y se agrega a sus
solicitudes. Si falla no se modifica nada y la solicitud se libera.
- Una Plataforma(nombre) con usuarios en un Repositorio por nombre (operator+=), que procesa
solicitudes: procesar(nombreUsuario, solicitud).
- Reportes: ingresoTotal() (suma de costos), tokensProcesados() (suma de tokens de las
solicitudes de texto) y conteo de usuarios por tipo con una funcion miembro plantilla
contar<T>().
Los tipos de modelo, solicitud y usuario se distinguen con dynamic_cast<> (no con tipo()).
*/
#include<iostream>
using namespace std;
#include "Plataforma.h"
#include"Catalogo.h"
// Catalogo base usado en varias preguntas
void cargarCatalogo()
{
	Catalogo::getInst().limpiar();
	// ModeloTexto(nombre, Bs por cada 1000 tokens o fraccion)
	Catalogo::getInst().registrar(new ModeloTexto("lince-1", 2));
	Catalogo::getInst().registrar(new ModeloTexto("puma-2", 5));
	// ModeloImagen(nombre, Bs por imagen)
	Catalogo::getInst().registrar(new ModeloImagen("condor-2", 3));
}

int pregunta1()
{
	cout << "----Pregunta 1----" << endl;
	string error1, error2;
	// Repositorio local (no es el del catalogo)
	Repositorio<Modelo> r;
	try {
		r.agregar(new ModeloTexto("lince-1", 2));
		r.agregar(new ModeloImagen("condor-2", 3));
		r.agregar(new ModeloTexto("puma-2", 5));
		r.agregar(new ModeloImagen("puma-2", 9));
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		r.buscar("halcon-9");
	}
	catch (exception& e) {
		error2 = e.what();
	}
	// obtener(2) es puma-2: 2500 tokens = 3 bloques * 5 Bs = 15
	string result = r.toJson() + " " + r.buscar("condor-2")->getNombre() + " " + to_string(r.obtener(2)->costo(2500)) + " " + to_string(r.size());
	cout << result << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	if (error1 == "clave duplicada: puma-2" && error2 == "clave no encontrada: halcon-9"
		&& result == "[{\"nombre\":\"lince-1\",\"tipo\":\"texto\",\"precio\":2},{\"nombre\":\"condor-2\",\"tipo\":\"imagen\",\"precio\":3},{\"nombre\":\"puma-2\",\"tipo\":\"texto\",\"precio\":5}] condor-2 15 3")
	{
		cout << "Resultado: correcto" << endl;
		return 25;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}
#include"UsuarioGratis.h"
#include"UsuarioPro.h"
int pregunta2()
{
	cout << "----Pregunta 2----" << endl;
	cout<< "{\"modelos\":[{\"nombre\":\"lince-1\",\"tipo\":\"texto\",\"precio\":2},{\"nombre\":\"puma-2\",\"tipo\":\"texto\",\"precio\":5},{\"nombre\":\"condor-2\",\"tipo\":\"imagen\",\"precio\":3}]}"
		"{\"nombre\":\"ana\",\"plan\":\"gratis\",\"tokensDisponibles\":1000,\"solicitudes\":[{\"id\":1,\"modelo\":\"lince-1\",\"tipo\":\"texto\",\"cantidad\":4000,\"costo\":0},{\"id\":2,\"modelo\":\"puma-2\",\"tipo\":\"texto\",\"cantidad\":5000,\"costo\":0}]}" <<endl;
	string error1, error2, error3;
	UsuarioGratis u("ana");
	try {
		cargarCatalogo();
		Catalogo::getInst().registrar(new ModeloImagen("lince-1", 9));
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		u.procesar(new SolicitudTexto(1, "lince-1", 4000));
		u.procesar(new SolicitudTexto(2, "puma-2", 5000));
		// quedan 1000 tokens
		u.procesar(new SolicitudTexto(3, "lince-1", 1500));
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		u.procesar(new SolicitudImagen(4, "condor-2", 1));
	}
	catch (exception& e) {
		error3 = e.what();
	}
	string result = Catalogo::getInst().toJson() + u.toJson();
	cout << result << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	if (error1 == "clave duplicada: lince-1"
		&& error2 == "ana supero su cuota de tokens en la solicitud 3"
		&& error3 == "el plan gratis no permite imagenes (solicitud 4)"
		&& result == "{\"modelos\":[{\"nombre\":\"lince-1\",\"tipo\":\"texto\",\"precio\":2},{\"nombre\":\"puma-2\",\"tipo\":\"texto\",\"precio\":5},{\"nombre\":\"condor-2\",\"tipo\":\"imagen\",\"precio\":3}]}"
		"{\"nombre\":\"ana\",\"plan\":\"gratis\",\"tokensDisponibles\":1000,\"solicitudes\":[{\"id\":1,\"modelo\":\"lince-1\",\"tipo\":\"texto\",\"cantidad\":4000,\"costo\":0},{\"id\":2,\"modelo\":\"puma-2\",\"tipo\":\"texto\",\"cantidad\":5000,\"costo\":0}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 25;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int pregunta3()
{
	cout << "----Pregunta 3----" << endl;
	string error1, error2, error3, error4;
	UsuarioPro u("luis", 50);
	try {
		cargarCatalogo();
		// 2500 tokens = 3 bloques * 2 Bs = 6
		u.procesar(new SolicitudTexto(1, "lince-1", 2500));
		// 4 imagenes * 3 Bs = 12
		u.procesar(new SolicitudImagen(2, "condor-2", 4));
		// 1000 tokens = 1 bloque * 5 Bs = 5
		u.procesar(new SolicitudTexto(3, "puma-2", 1000));
		u.procesar(new SolicitudTexto(4, "condor-2", 500));
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		u.procesar(new SolicitudImagen(5, "halcon-9", 1));
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		// 10 imagenes * 3 Bs = 30 > 27
		u.procesar(new SolicitudImagen(6, "condor-2", 10));
	}
	catch (exception& e) {
		error3 = e.what();
	}
	try {
		u.procesar(new SolicitudTexto(7, "lince-1", 0));
	}
	catch (exception& e) {
		error4 = e.what();
	}
	string result = u.toJson();
	cout << result << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	cout << error4 << endl;
	if (error1 == "el modelo condor-2 no es compatible con la solicitud 4"
		&& error2 == "clave no encontrada: halcon-9"
		&& error3 == "creditos insuficientes luis en la solicitud 6"
		&& error4 == "cantidad invalida en la solicitud 7"
		&& result == "{\"nombre\":\"luis\",\"plan\":\"pro\",\"creditos\":27,\"solicitudes\":[{\"id\":1,\"modelo\":\"lince-1\",\"tipo\":\"texto\",\"cantidad\":2500,\"costo\":6},{\"id\":2,\"modelo\":\"condor-2\",\"tipo\":\"imagen\",\"cantidad\":4,\"costo\":12},{\"id\":3,\"modelo\":\"puma-2\",\"tipo\":\"texto\",\"cantidad\":1000,\"costo\":5}]}")
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
	string error1, error2, error3;
	// Crear plataforma(nombre)
	Plataforma p("NubeIA");
	int ingreso = -1, tokens = -1, pros = -1, gratis = -1, usuarios = -1;
	string result;
	try {
		cargarCatalogo();
		p += new UsuarioPro("luis", 100);
		p += new UsuarioGratis("ana");
		p += new UsuarioPro("rosa", 50);
		p += new UsuarioGratis("luis");
	}
	catch (exception& e) {
		error1 = e.what();
	}
	try {
		// 3001 tokens = 4 bloques * 5 Bs = 20
		p.procesar("luis", new SolicitudTexto(1, "puma-2", 3001));
		p.procesar("luis", new SolicitudImagen(2, "condor-2", 2));
		p.procesar("ana", new SolicitudTexto(3, "puma-2", 8000));
		p.procesar("rosa", new SolicitudTexto(4, "lince-1", 999));
		p.procesar("maria", new SolicitudTexto(5, "lince-1", 10));
	}
	catch (exception& e) {
		error2 = e.what();
	}
	try {
		ingreso = p.ingresoTotal();
		tokens = p.tokensProcesados();
		pros = p.contar<UsuarioPro>();
		gratis = p.contar<UsuarioGratis>();
		usuarios = p.contar<Usuario>();
		result = p.toJson();
	}
	catch (exception& e) {
		error3 = e.what();
	}
	cout << result << endl;
	cout << "ingresoTotal: " << ingreso << " tokensProcesados: " << tokens << endl;
	cout << "pro: " << pros << " gratis: " << gratis << " usuarios: " << usuarios << endl;
	cout << error1 << endl;
	cout << error2 << endl;
	cout << error3 << endl;
	if (error1 == "clave duplicada: luis" && error2 == "clave no encontrada: maria" && error3 == ""
		&& ingreso == 28 && tokens == 12000 && pros == 2 && gratis == 1 && usuarios == 3
		&& result == "{\"nombre\":\"NubeIA\",\"usuarios\":["
		"{\"nombre\":\"luis\",\"plan\":\"pro\",\"creditos\":74,\"solicitudes\":[{\"id\":1,\"modelo\":\"puma-2\",\"tipo\":\"texto\",\"cantidad\":3001,\"costo\":20},{\"id\":2,\"modelo\":\"condor-2\",\"tipo\":\"imagen\",\"cantidad\":2,\"costo\":6}]},"
		"{\"nombre\":\"ana\",\"plan\":\"gratis\",\"tokensDisponibles\":2000,\"solicitudes\":[{\"id\":3,\"modelo\":\"puma-2\",\"tipo\":\"texto\",\"cantidad\":8000,\"costo\":0}]},"
		"{\"nombre\":\"rosa\",\"plan\":\"pro\",\"creditos\":48,\"solicitudes\":[{\"id\":4,\"modelo\":\"lince-1\",\"tipo\":\"texto\",\"cantidad\":999,\"costo\":2}]}]}")
	{
		cout << "Resultado: correcto" << endl;
		return 25;
	}
	cout << "Resultado: incorrecto" << endl;
	return 0;
}

int main()
{
	int nota = pregunta1() + pregunta2() + pregunta3() +pregunta4();
	cout << endl;
	cout << "====================" << endl;
	cout << "===> NOTA: " << nota << "/100" << endl;
	cout << "====================" << endl;
	system("pause");
	return 0;
}