#pragma once
#include "Enemigo.h"
class MurcielagoBoss: public Enemigo
{
private:
	int vidas;
	float velocidad_china;
public:
	MurcielagoBoss();
	void volar();
	MurcielagoBoss(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void setVidas(int vida) { vidas += vida; }
	int getVidas() { return vidas; }
	float getVelChina() { return velocidad_china; }
};

