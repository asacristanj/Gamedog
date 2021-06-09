#pragma once
#include "Enemigo.h"
class MurcielagoPequeño: public Enemigo
{
private:
	float velocidad_china;
public:
	MurcielagoPequeño();
	MurcielagoPequeño(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	float getVelChina() { return velocidad_china; }
};

