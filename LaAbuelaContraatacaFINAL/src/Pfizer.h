#pragma once
#include "Bonus.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Pfizer :    public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/pfizer.png", 1 };
public:
	Pfizer();
	Pfizer(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);//Constructor sobrecargado para agregarlas posteriormente
	virtual ~Pfizer();
	void dibuja();//Dibujo individual del sprite
};

