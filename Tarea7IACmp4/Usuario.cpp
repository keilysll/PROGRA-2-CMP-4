#include "Usuario.h"

Usuario::Usuario(string nombre)
{
	this->nombre = nombre;
	this->tokDisp = 0;
}

Usuario::~Usuario()
{
}

string Usuario::getNombre()
{
	return nombre;
}

void Usuario::procesar(Solicitud* s)
{
	int costo = 0;
	if (s->getTokens() <= 0)
		throw exception(("cantidad invalida en la solicitud " + to_string(s->getId())).c_str());
	// 2. el modelo existe (el Repositorio lanza "clave no encontrada: ...")
	Modelo* m = Catalogo::getInst().buscar(s->getModelo());
	// 3. el modelo es del tipo de la solicitud
	bool compatible = (dynamic_cast<SolicitudTexto*>(s) != NULL && dynamic_cast<ModeloTexto*>(m) != NULL)
		|| (dynamic_cast<SolicitudImagen*>(s) != NULL && dynamic_cast<ModeloImagen*>(m) != NULL);
	if (!compatible)
		throw exception(("el modelo " + m->getNombre() + " no es compatible con la solicitud " + to_string(s->getId())).c_str());
	costo = m->costo(s->getTokens());
	// 4. reglas del plan (cada tipo de usuario las suyas)
	validarPlan(s, costo);
	solicitudes.agregar(s);
	s->setCosto(costo);
	descontar(s, costo);

}

int Usuario::ingresoTotal()
{
	int total = 0;
	for (int i = 0; i < solicitudes.size(); i++)
	{
		total = total + solicitudes.obtener(i)->getCosto();
	}

	return total;
}

int Usuario::tokensProcesados()
{
	int total = 0;
	for (int i = 0; i < solicitudes.size(); i++)
	{
		SolicitudTexto* st = dynamic_cast<SolicitudTexto*>(solicitudes.obtener(i));
		if(st != NULL)
			total = total + solicitudes.obtener(i)->getTokens();
	}

	return total;
}

string Usuario::getClave() const
{
	return nombre;
}
