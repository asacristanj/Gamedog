#pragma once
#include "Enemigo.h"
class CepaChina: public Enemigo
{
public:
	CepaChina();
	CepaChina(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();

	friend class Interaccion;
};

