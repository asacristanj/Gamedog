#pragma once
#include "Enemigo.h"

class CepaBrasileņa: public Enemigo
{
private:
	Vector2D origenSalto;
	
public:
	CepaBrasileņa();
	CepaBrasileņa(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void saltar(float salto);
	
	friend class Interaccion;
};

