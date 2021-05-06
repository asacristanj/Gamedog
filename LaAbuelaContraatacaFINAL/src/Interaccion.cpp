#include "Interaccion.h"
#include "freeglut.h" 
#include <math.h>
#define PI 3.141592
void Interaccion::rebote(Jugador& j, Escenario e)
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (j.posicion.x > xmax)j.posicion.x = xmax;
	if (j.posicion.x < xmin)j.posicion.x = xmin;

	float ymin = e.suelo.limite1.y;
	if ((j.posicion.y - j.altura) < ymin) j.posicion.y = ymin + j.altura;
}
void Interaccion::rebote(Enemigo& enem, Escenario e)
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (enem.posicion.x > xmax)enem.posicion.x = xmax;
	if (enem.posicion.x < xmin)enem.posicion.x = xmin;

	float ymin = e.suelo.limite1.y;
	if ((enem.posicion.y - enem.altura) < ymin) enem.posicion.y = ymin + enem.altura;
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	pos.y += j.getAltura() / 2.0f; //posicion del centro
	float distancia = (enem.posicion - pos).modulo();
	if (distancia < (enem.altura/2))
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Plataforma p)
{
	Vector2D pos = d.getPos(); //la posicion de la base del hombre
	pos.y += d.getRadio(); //posicion del centro
	float distancia = p.distancia(pos);
	if (distancia < d.getRadio())
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Escenario e)
{
	return Interaccion::colision(d, e.techo);
}

