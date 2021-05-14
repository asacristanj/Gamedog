#pragma once
#include "Vector2d.h"
#include "ColorRVA.h"
#include "ObjetoMovil.h"
class Enemigo: public ObjetoMovil
{
protected:
	float altura;
	ColorRVA color;

public:
	Enemigo();
	Enemigo(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Enemigo();
	void dibuja();
	void mueve(float t);
	void setColor(Byte r, Byte v, Byte a);
	void setAltura(float alt);
	float getAltura() { return altura; }

	friend class Interaccion;
};

