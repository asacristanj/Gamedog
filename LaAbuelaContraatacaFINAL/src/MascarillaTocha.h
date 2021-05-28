#pragma once
#include "Bonus.h"
class MascarillaTocha :    public Bonus
{
public:
	MascarillaTocha();
	MascarillaTocha(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~MascarillaTocha();
	void dibuja();
};

