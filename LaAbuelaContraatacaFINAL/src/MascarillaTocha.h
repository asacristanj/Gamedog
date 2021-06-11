#pragma once
#include "Bonus.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;
class MascarillaTocha :    public Bonus
{
private:
	SpriteSequence sprite{ "imagenes/ffp2.png", 1 };
public:
	MascarillaTocha();
	MascarillaTocha(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~MascarillaTocha();
	void dibuja();
};

