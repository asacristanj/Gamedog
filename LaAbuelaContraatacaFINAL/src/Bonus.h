#pragma once
#define NINGUNO -1
#define ASTRAZENECA 0
#define MATOCHA 1
#define JANSSEN 2
#define PFIZER 3
#define QUIRURGICA 4
#define SPUTNIK 5
#include "Vector2D.h"
#include "ObjetoMovil.h"
#include "ColorRVA.h"
class Bonus: public ObjetoMovil
{
protected:
	float lado;
	ColorRVA color;
	int tipo;

public:
	friend class Interaccion;
	Bonus();
	virtual ~Bonus();
	virtual void dibuja();
	void mueve(float t);
	int getTipo() { return tipo; }
	float getlado() { return lado; }
};
