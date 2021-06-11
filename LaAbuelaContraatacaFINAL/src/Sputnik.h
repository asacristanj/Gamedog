#pragma once
#include "Bonus.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Sputnik :    public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/sputnik.png", 1 };
public:
	Sputnik();
	Sputnik(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Sputnik();
	void dibuja();
};


