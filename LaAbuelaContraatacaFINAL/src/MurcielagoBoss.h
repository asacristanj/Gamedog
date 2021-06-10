#pragma once
#include "Enemigo.h"
#include <time.h>

class MurcielagoBoss: public Enemigo
{
private:
	SpriteSequence sprite{ "imagenes/murcielago.png", 4 };
	float posicion_bajada;
	float velocidad_bajada; // velocidad a la que baja al ser disparado
	float velocidad_china;
	time_t horaIniciocaida;
public:
	MurcielagoBoss();
	MurcielagoBoss(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void dibuja();
	void mueve(float t);
	void setVidas(int vida) { vidas += vida; }
	void setPisoton(bool pisada) { pisoton = pisada; }
	float getPosicionBajada() { return posicion_bajada; }
	float getVelocidadBajada() { return velocidad_bajada; }
	float getVelChina() { return velocidad_china; }
	bool getPisoton() { return pisoton; }
};