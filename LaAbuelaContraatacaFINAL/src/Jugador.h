#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
class Jugador: public ObjetoMovil
{
private:
	float altura;
	float acel_inicial = -30.0f;
	float impulso = 20.0f; //impulso vertical inicial del salto
	bool tocandosuelo;
	float vel_nom=5.0f;
protected:
	int numbonus;
public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void salto();
	void morir();
	//void crecer();
	float getAltura() { return altura; }
	void setAltura(float nalt) { altura = nalt; }
	//void IncrementaNumBonus();
	void setNumBonus(int num) { numbonus = num; }
	int GetNumBonus() { return numbonus; }
	void setImpulso(float imp) { impulso = imp; }
	void subirEscalera();
	float getvelNom() { return vel_nom; }
	void setvelNom();
	bool suelo();

	friend class Interaccion;
};

