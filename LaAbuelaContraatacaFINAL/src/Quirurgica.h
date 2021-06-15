#pragma once
#include "Bonus.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Quirurgica :    public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/mascarilla.png", 1 };
public:
	Quirurgica();
	Quirurgica(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);//Constructor sobrecargado para agregarlas posteriormente
	virtual ~Quirurgica();
	void dibuja();//Dibujo individual del sprite
};

