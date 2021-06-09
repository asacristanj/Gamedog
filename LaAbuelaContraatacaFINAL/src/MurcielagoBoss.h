#pragma once
#include "Enemigo.h"
class MurcielagoBoss: public Enemigo
{
private:
	float posicion_bajada;
	float velocidad_bajada; // velocidad a la que baja al ser disparado
	float velocidad_china;
public:
	MurcielagoBoss();
	MurcielagoBoss(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void setVidas(int vida) { vidas += vida; }
	void setPisoton(bool pisada) { pisoton = pisada; }
	float getPosicionBajada() { return posicion_bajada; }
	float getVelocidadBajada() { return velocidad_bajada; }
	float getVelChina() { return velocidad_china; }
	bool getPisoton() { return pisoton; }
};

