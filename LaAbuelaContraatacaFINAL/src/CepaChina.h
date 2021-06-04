#pragma once
#include "Enemigo.h"
class CepaChina: public Enemigo
{
private:
	float tiempo_disparo = 5.0f;
	float radio;
	Vector2D origen;
public:
	CepaChina();
	CepaChina(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	float getTiempo() { return tiempo_disparo; }
	float getRadio() { return radio; }

	friend class Interaccion;
};

