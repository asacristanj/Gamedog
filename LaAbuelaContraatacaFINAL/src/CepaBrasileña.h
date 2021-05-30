#pragma once
#include "Enemigo.h"
class CepaBrasileña: public Enemigo
{
private:
	Vector2D origenSalto;
public:
	CepaBrasileña();
	CepaBrasileña(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void saltar();
	
	friend class Interaccion;
};

