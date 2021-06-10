#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;

class DisparoGel:public ObjetoMovil
{
private:
	float radio;
	Vector2D origen;
	SpriteSequence sprite{ "imagenes/disparo.png", 4 };
public:
	DisparoGel();
	virtual ~DisparoGel();
	void dibuja();
	void mueve(float t);
	void setPos(float ix, float iy);
	float getRadio() { return radio; }

	friend class Interaccion;
};

