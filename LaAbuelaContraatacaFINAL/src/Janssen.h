#pragma once
#include "Bonus.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class Janssen :    public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/janssen.png", 1 };
public:
	Janssen();
	Janssen(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Janssen();
	void dibuja();
};

