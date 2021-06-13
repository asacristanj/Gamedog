#pragma once
#include "Enemigo.h"
class CepaBritanica: public Enemigo
{
private:
	SpriteSequence sprite{ "imagenes/sprite_britanica.png", 5 };
	bool inicializar_hora_inicio; //Variable que guarda si se ha usado el temporizador de la CepaBritanica
public:
	CepaBritanica();
	CepaBritanica(float alt, float x = 0.0f, float y = 0.0f, float vx = 0.0f, float vy = 0.0f);
	void explotar();
	void dibuja();
	void mueve(float t);
	bool getInicializarHora() {return inicializar_hora_inicio; }
	void setInicializarHora(bool horaIn) { inicializar_hora_inicio = horaIn; }
	friend class Interaccion;
};