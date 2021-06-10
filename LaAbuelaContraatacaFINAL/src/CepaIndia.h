#pragma once
#include "Enemigo.h"
class CepaIndia: public Enemigo
{
private:
	SpriteSequence sprite{ "imagenes/sprite_india.png", 5 };
public:
	CepaIndia();
	CepaIndia(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void mueve(float t);

	friend class Interaccion;
};

