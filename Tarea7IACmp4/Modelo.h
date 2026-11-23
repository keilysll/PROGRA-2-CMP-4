#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
class Modelo
{
protected:
	string nombre;
	int precio;
public:
	Modelo(string nombre,int precio);
	~Modelo();
	string getNombre();
	int getPrecio();
	string getClave() const;
	virtual int costo(int cantidad) = 0;
	virtual string toJson() const = 0;
	   

};

