#pragma once
#include "ObjetoMovil.h"
#include "ColorRVA.h"
class Llave : public ObjetoMovil
{private:
	float lado;
	ColorRVA color;
public:
	friend class Interaccion;
	Llave();
	Llave(float l, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	virtual ~Llave();
	void dibuja();
	float getLado();
};

