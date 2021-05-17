#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
class Bonus: public ObjetoMovil
{
private:
	float lado;

public:
	friend class Interaccion;
	Bonus();
	virtual ~Bonus();
	void dibuja();
	void mueve(float t);
	float getlado() { return lado; }
};
