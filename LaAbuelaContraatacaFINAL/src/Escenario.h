#pragma once
#include "Plataforma.h"
class Escenario
{
private:
	Plataforma suelo;
	Plataforma techo;
	Plataforma pared_izq;
	Plataforma pared_dcha;

public:
	Escenario();
	virtual ~Escenario();
	void dibuja();

	friend class Interaccion;
};

