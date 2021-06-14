#pragma once
#define NINGUNO -1
#define CEPABRITANICA 0
#define CEPABRASILEÑA 1
#define CEPAINDIA 2
#define CEPACHINA 3
#define MURCIELAGOPEQUEÑO 4
#define MURCIELAGOBOSS 5

#include "Vector2D.h"
#include "ObjetoMovil.h"
#include "ETSIDI.h"

using ETSIDI::SpriteSequence;

class Enemigo: public ObjetoMovil
{
protected:
	float altura;
	int vidas;
	bool disparo_recibido; // se pone a true si es impactado por disparo de jugador
	bool pisoton; // se pone a true cuando es pisado por el jugador
	int tipo;

public:
	Enemigo();
	Enemigo(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Enemigo();
	virtual void dibuja();
	void mueve(float t);
	void setAltura(float alt);
	void setDisparoRecibido(bool disparo) { disparo_recibido = disparo; }
	void setVidas(int vida) { vidas += vida; }
	int getTipo() { return tipo; }
	float getAltura() { return altura; }
	bool getDisparoRecibido() { return disparo_recibido; }
	int getVidas() { return vidas; }

	friend class Interaccion;
};