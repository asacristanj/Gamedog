#pragma once
#include "Enemigo.h"
class MurcielagoPeque�o: public Enemigo
{
private:
	float velocidad_china;
	float posiciony_inicial;
public:
	MurcielagoPeque�o();
	MurcielagoPeque�o(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void setPosyInicial(float pos_y) { posiciony_inicial = pos_y; }
	float getPosyInicial() { return posiciony_inicial; }
	float getVelChina() { return velocidad_china; }
};

