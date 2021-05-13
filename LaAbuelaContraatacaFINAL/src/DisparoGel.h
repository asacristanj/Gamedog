#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
class DisparoGel: public ObjetoMovil
{
private:
	float radio;
	Vector2D origen;

public:
	DisparoGel();
	virtual ~DisparoGel();
	void dibuja();
	void mueve(float t);
	void setPos(float ix, float iy);
	float getRadio() { return radio; }
};

