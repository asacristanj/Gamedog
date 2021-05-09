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

	float y = e.suelo.limite1.y;
	if ((enem.posicion.y - enem.altura) < y) enem.posicion.y = y + enem.altura;
}
void Interaccion::rebote(Jugador& j, Plataforma p)
{
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y= p.limite1.y;
	if (Interaccion::colisionEncima(j, p))
		j.posicion.y = y + j.altura;
	if (Interaccion::colisionDebajo(j, p))
		j.posicion.y = y - (j.altura*2);
}
void Interaccion::rebote(Enemigo& enem, Plataforma p)
{
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (enem.posicion.x > xmax)
	{
		enem.posicion.x = xmax;
		enem.velocidad.x = -4.0f;
	}
	if (enem.posicion.x < xmin)
	{
		enem.posicion.x = xmin;
		enem.velocidad.x = 4.0f;
	}

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
bool Interaccion::colisionDebajo(Jugador j, Plataforma p)
{
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.y += (j.altura);
	float distancia = p.distancia(pos);
	if (distancia <= j.getAltura()) {
		return true;
		//al chocar desde abajo queda parada y empieza a bajar
		j.velocidad.y =0.0f;
	}
	return false;
}
bool Interaccion::colisionEncima(Jugador j, Plataforma p)
{
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	float distancia = p.distancia(pos);
	if (distancia < j.getAltura())
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Plataforma p)
{
	Vector2D pos = d.getPos(); //la posicion de la base del hombre
	//pos.y += d.getRadio(); //posicion del centro Diego:no estas consiguiendo nada con esto es la posicion del disparo la da el centro, no tiene ningun calculo mas
	float distancia = p.distancia(pos);
	if (distancia <= d.getRadio()) {
		return true;
	}
	return false;
}
bool Interaccion::colision(DisparoGel d, Escenario e)
{
	if (Interaccion::colision(d, e.pared_dcha) || Interaccion::colision(d, e.techo) || Interaccion::colision(d, e.pared_izq)||Interaccion::colision(d,e.suelo))
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Enemigo e) {
	//un vector para la diferencia de posiciones y dos floats para las distancias a comparar
	Vector2D posicionenem=e.getPos(),diferencia = e.posicion-posicionenem;
	float distancia = diferencia.modulo(),radios=e.altura+d.getRadio();
	if (distancia <= radios) {
		return true;
	}
	return false;
	
}
