#pragma once
#include "Enemigo.h"
class CepaIndia: public Enemigo
{
public:
	CepaIndia();
	CepaIndia(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();

	friend class Interaccion;
};

