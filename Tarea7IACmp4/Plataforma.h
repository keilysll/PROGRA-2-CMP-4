#pragma once
#include"Repositorio.h"
#include"UsuarioPro.h"
#include"Usuario.h"
#include"UsuarioGratis.h"
class Plataforma
{
private:
	string nombre;
	Repositorio<Usuario> usuarios;
public:
	Plataforma(string nombre);
	~Plataforma();
	string getNombre();
	void operator+=(Usuario* u);
	void procesar(string nombre,Solicitud* s);
	template <class T> int contar();
	string toJson();
	int ingresoTotal();
	int tokensProcesados();
};

template<class T>
inline int Plataforma::contar()
{
	int cont = 0;
	for (int i = 0; i < usuarios.size(); i++)
	{
		if (dynamic_cast<T*>(usuarios.obtener(i)) != NULL)
		cont++;
	}
	return cont;
}
