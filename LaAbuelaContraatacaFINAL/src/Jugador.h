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
	SpriteSequence spritemasc{ "imagenes/abuela_mascarilla.png", 6 };
	SpriteSequence spriteffp2{ "imagenes/abuela_ffp2.png", 6 };

	int numbonus;
	Vector2D posicion_inicial;
	float altura;
	float vel_normal = 5.0f;
	float velocidad_rebote = 15.0f; // intensidad del rebote cuando pisa a un enemigo
	float coeficiente_velx; // coeficiente de velocidad x
	float coef_vel_rapida = 2.0; // coeficiente para velocidad rapida
	float coef_vel_lenta = 1.0 / 3.0; // coeficiente para velocidad lenta
	float acel_inicial = -30.0f;
	float impulso = 15.0f; //impulso vertical inicial del salto
	bool tocandosuelo,escalera;
	bool astra_activo,pfizer_activo,janssen_activo;
	time_t horaInicioAstra, horaInicioPfizer, horaInicioJanssen;
	int numLlaves;
	int altura_max_caida = 15;
	bool daño_caida = false;
	int puntuacion; // puntuacion de cada partida

public:
	Jugador();
	virtual ~Jugador();
	void dibuja();
	void mueve(float t);
	void salto();
	void morir();
	void dañocaida();
	void volverSalto();
	void volverVelocidadPfizer();
	void volverVelocidadJanssen();
	void subirEscalera();
	void bajarEscalera();
	bool suelo();
	// gets
	float getAltura() { return altura; }
	float getVelNormal() { return vel_normal; }
	float getVelRapida() { return coef_vel_rapida; }
	float getVelLenta() { return coef_vel_lenta; }
	float getCoefVelx() { return coeficiente_velx; }
	float getVelocidadRebote() { return velocidad_rebote; }
	bool getDañoCaida() { return daño_caida; }
	bool getAstraActivo() { return astra_activo; }
	bool getPfizerActivo() { return pfizer_activo; }
	bool getJanssenActivo() { return janssen_activo; }
	int getNumBonus() { return numbonus; }
	int getNumLlaves() { return numLlaves; }
	bool getEscalera() { return escalera; }
	int getPuntuacion() { return puntuacion; }
	// sets
	void setDañoCaida(bool shik) { daño_caida = shik; }
	void setAltura(float nalt) { altura = nalt; }
	void setAcely(float gravedad) { aceleracion.y = gravedad; }
	void setCoefVelx(float coef_vel) { coeficiente_velx = coef_vel; }
	void setAstraActivo(bool act) { astra_activo = act; }
	void setPfizerActivo(bool act) { pfizer_activo = act; }
	void setJanssenActivo(bool act) { janssen_activo = act; }
	void sethInicioAstra(time_t tiempo) { horaInicioAstra = tiempo; }
	void sethInicioPfizer(time_t tiempo) { horaInicioPfizer = tiempo; }
	void sethInicioJanssen(time_t tiempo) { horaInicioJanssen = tiempo; }
	void setNumBonus(int num) { numbonus = num; }
	void setNumLlaves(int num) { numLlaves = num; }
	void setImpulso(float imp) { impulso = imp; }
	void setEscalera(int i);
	void setPuntuacion(int punt) { puntuacion += punt; }

	friend class Interaccion;
};