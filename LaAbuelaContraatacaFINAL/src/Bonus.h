#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
class Bonus: public ObjetoMovil
{
private:
	float lado;

public:
	Bonus();
	virtual ~Bonus();
	void dibuja();
	void mueve(float t);
};
