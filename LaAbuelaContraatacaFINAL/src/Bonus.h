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
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;

class Bonus: public ObjetoMovil
{
protected:
	float lado;
	ColorRVA color;
	int tipo;
	SpriteSequence sprite0{ "imagenes/astrazeneca.png", 1 };
	SpriteSequence sprite1{ "imagenes/ffp2.png", 1 };
	SpriteSequence sprite2{ "imagenes/janssen.png", 1 };
	SpriteSequence sprite3{ "imagenes/pfizer.png", 1 };
	SpriteSequence sprite4{ "imagenes/mascarilla.png", 1 };
	SpriteSequence sprite5{ "imagenes/sputnik.png", 1 };

public:
	friend class Interaccion;
	Bonus();
	virtual ~Bonus();
	virtual void dibuja();
	void mueve(float t);
	int getTipo() { return tipo; }
	float getlado() { return lado; }
};
