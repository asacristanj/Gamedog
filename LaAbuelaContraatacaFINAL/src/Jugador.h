#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
#include "ETSIDI.h"
using ETSIDI::SpriteSequence;

class Jugador: public ObjetoMovil
{
	
private:
	SpriteSequence sprite{ "imagenes/sprite_abuela.png", 6 };
	float altura;
	float vel_normal = 5.0f;
	float coeficiente_velx; // coeficiente de velocidad x
	float coef_vel_rapida = 2.0; // coeficiente para velocidad rapida
	float coef_vel_lenta = 1.0 / 2.0; // coeficiente para velocidad lenta
	float acel_inicial = -30.0f;
	float impulso = 20.0f; //impulso vertical inicial del salto
	bool tocandosuelo;
protected:
	int numbonus;
public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void mueve(float t);
	void salto();
	void morir();
	//void crecer();
	float getAltura() { return altura; }
	float getVelNormal() { return vel_normal; }
	float getVelRapida() { return coef_vel_rapida; }
	float getVelLenta() { return coef_vel_lenta; }
	float getCoefVelx() { return coeficiente_velx; }
	void setAltura(float nalt) { altura = nalt; }
	void setCoefVelx(float coef_vel) { coeficiente_velx = coef_vel; }
	//void IncrementaNumBonus();
	void setNumBonus(int num) { numbonus = num; }
	int GetNumBonus() { return numbonus; }
	void setImpulso(float imp) { impulso = imp; }
	void subirEscalera();
	bool suelo();

	friend class Interaccion;
};

