#pragma once
#include "Enemigo.h"
class MurcielagoPequeño: public Enemigo
{
private:
	float velocidad_china;
	SpriteSequence sprite{ "imagenes/murcielago.png", 4 };
public:
	MurcielagoPequeño();
	MurcielagoPequeño(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	float getVelChina() { return velocidad_china; }
	void mueve(float t);
};

