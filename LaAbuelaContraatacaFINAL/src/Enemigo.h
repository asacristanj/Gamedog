#pragma once
#define NINGUNO -1
#define CEPABRITANICA 0
#define CEPABRASILEÑA 1
#define CEPAINDIA 2
#define CEPACHINA 3
#define MURCIELAGOPEQUEÑO 4
#define MURCIELAGOBOSS 5

#include "Vector2D.h"
#include "ColorRVA.h"
#include "ObjetoMovil.h"
class Enemigo: public ObjetoMovil
{
protected:
	float altura;
	ColorRVA color;
	int tipo;

public:
	Enemigo();
	Enemigo(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Enemigo();
	virtual void dibuja();
	void mueve(float t);
	void setColor(Byte r, Byte v, Byte a);
	void setAltura(float alt);
	int getTipo() { return tipo; }
	float getAltura() { return altura; }

	friend class Interaccion;
};

