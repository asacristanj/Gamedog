#pragma once
#include "Enemigo.h"
class CepaChina: public Enemigo
{

private:
	SpriteSequence sprite{ "imagenes/sprite_china.png", 5 };
	float tiempo_disparo = 5.0f;
	Vector2D origen;
	
public:
	
	CepaChina();
	CepaChina(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	float getTiempo() { return tiempo_disparo; }
	void mueve(float t);
};

