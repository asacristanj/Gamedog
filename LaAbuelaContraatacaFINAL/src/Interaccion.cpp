#include "Interaccion.h"
#include "freeglut.h" 
#include <math.h>
#define PI 3.141592
void Interaccion::rebote(Jugador& j, Escenario e)
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (j.posicion.x+j.altura > xmax)j.posicion.x = xmax-j.altura;
	if (j.posicion.x-j.altura< xmin)j.posicion.x = xmin+j.altura;

	float ymin = e.suelo.limite1.y;
	if ((j.posicion.y - j.altura) < ymin) j.posicion.y = ymin+j.altura;
}
void Interaccion::rebote(Enemigo& enem, Escenario e)
{
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (enem.posicion.x - enem.altura > xmax)enem.posicion.x = xmax + enem.altura;
	if (enem.posicion.x - enem.altura < xmin)enem.posicion.x = xmin + enem.altura;

	float ymin = e.suelo.limite1.y;
	if ((enem.posicion.y - enem.altura) < ymin) enem.posicion.y = ymin + enem.altura;
}
void Interaccion::rebote(Jugador& j, Plataforma p)
{
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y= p.limite1.y;
	if (xmin < j.posicion.x && j.posicion.x < xmax && y<(j.posicion.y + j.altura) && Interaccion::colision(j, p))
		j.posicion.y = y + j.altura;
	//if (xmin < j.posicion.x && j.posicion.x < xmax && (j.posicion.y - j.altura)<y && Interaccion::colision(j, p))
		//j.posicion.y = y - j.altura;
}
void Interaccion::rebote(Enemigo& enem, Plataforma p)
{
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (enem.posicion.x > xmax)enem.posicion.x = xmax;
	if (enem.posicion.x < xmin)enem.posicion.x = xmin;

	float ymin = p.limite1.y;
	if ((enem.posicion.y - enem.altura) < ymin) enem.posicion.y = ymin + enem.altura;
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	pos.y += j.getAltura() / 2.0f; //posicion del centro
	float distancia = ((enem.posicion+enem.altura/2.0f) - pos).modulo();
	if (distancia < ((enem.altura/2.0f)+(j.altura/2.0f)))
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
bool Interaccion::colision(Jugador j, Plataforma p)
{
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	pos.y += j.getAltura(); //posicion del centro
	float distancia = p.distancia(pos);
	if (distancia < j.getAltura())
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Escenario e)
{
	if (Interaccion::colision(d, e.pared_dcha) || Interaccion::colision(d, e.techo) || Interaccion::colision(d, e.pared_izq))
		return true;
	return false;
}

