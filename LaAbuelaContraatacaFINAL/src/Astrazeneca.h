#pragma once
#include "ETSIDI.h"
#include "Bonus.h"
using ETSIDI::SpriteSequence;
class Astrazeneca : public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/astrazeneca.png", 1 };
public:
	Astrazeneca();
	Astrazeneca(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);//Constructor sobrecargado para agregarlas posteriormente
	virtual ~Astrazeneca();//Dibuja particular del astrazeneca
	void dibuja();//Dibujo individual del sprite
};

