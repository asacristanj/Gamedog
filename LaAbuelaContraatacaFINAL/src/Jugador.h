#pragma once
#include "Vector2D.h"
#include "ObjetoMovil.h"
#include "ETSIDI.h"
#include <time.h>
using ETSIDI::SpriteSequence;

class Jugador: public ObjetoMovil
{
private:
	SpriteSequence sprite{ "imagenes/sprite_abuela.png", 6 };
	float altura;
	float vel_normal = 5.0f;
	float velocidad_rebote = 15.0f; // intensidad del rebote cuando pisa a un enemigo
	Vector2D posicion_inicial;
	float coeficiente_velx; // coeficiente de velocidad x
	float coef_vel_rapida = 2.0; // coeficiente para velocidad rapida
	float coef_vel_lenta = 1.0 / 3.0; // coeficiente para velocidad lenta
	float acel_inicial = -30.0f;
	float impulso = 30.0f; //impulso vertical inicial del salto
	bool tocandosuelo;
	int numbonus;
	bool astra_activo,pfizer_activo,janssen_activo;
	time_t horaInicioAstra, horaInicioPfizer, horaInicioJanssen;

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
	float getVelocidadRebote() { return velocidad_rebote; }
	void setAltura(float nalt) { altura = nalt; }
	void setCoefVelx(float coef_vel) { coeficiente_velx = coef_vel; }
	bool getAstraActivo() { return astra_activo; }
	bool getPfizerActivo() { return pfizer_activo; }
	bool getJanssenActivo() { return janssen_activo; }
	void setAstraActivo(bool act) { astra_activo = act; }
	void setPfizerActivo(bool act) { pfizer_activo = act; }
	void setJanssenActivo(bool act) { janssen_activo = act; }
	void sethInicioAstra(time_t tiempo) { horaInicioAstra = tiempo; }
	void sethInicioPfizer(time_t tiempo) { horaInicioPfizer = tiempo; }
	void sethInicioJanssen(time_t tiempo) { horaInicioJanssen = tiempo; }
	//void IncrementaNumBonus();
	void setNumBonus(int num) { numbonus = num; }
	int GetNumBonus() { return numbonus; }
	void setImpulso(float imp) { impulso = imp; }
	void subirEscalera();
	void bajarEscalera();
	bool suelo();
	void volverSalto();
	void volverVelocidadPfizer();
	void volverVelocidadJanssen();

	friend class Interaccion;
};

