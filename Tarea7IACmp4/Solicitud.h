#pragma once
#include<iostream>
#include<sstream>
#include<string>
using namespace std;
class Solicitud
{
protected:
	int id;
	string modelo;
	int tokens;
	int costo;
public:
	Solicitud(int id,string modelo,int tokens);
	~Solicitud();
	int getId();
	string getModelo();
	int getTokens();
	int getCosto();
	string getClave() const;;
	virtual string toJson() const = 0;
	void setCosto(int costo);
};

