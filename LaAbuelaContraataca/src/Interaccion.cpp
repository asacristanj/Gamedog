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
}

/*bool Interaccion::rebote(Esfera& e, Pared p)
{
	Vector2D dir;
	float dif = p.distancia(e.posicion, &dir) - e.radio;
	if (dif <= 0.0f)
	{
		Vector2D v_inicial = e.velocidad;
		e.velocidad = v_inicial - dir * 2.0 * (v_inicial * dir);
		e.posicion = e.posicion - dir * dif;
		return true;
	}
	return false;
}

void Interaccion::rebote(Esfera& e, Caja c)
{
	Interaccion::rebote(e, c.suelo);
	Interaccion::rebote(e, c.techo);
	Interaccion::rebote(e, c.pared_izq);
	Interaccion::rebote(e, c.pared_dcha);
}

void Interaccion::rebote(Esfera& e1, Esfera& e2)
{
	Esfera i, j;
	float a1 = PI * e1.radio * e1.radio;
	float a2 = PI * e2.radio * e2.radio;
	float dist = (e1.posicion - e2.posicion).modulo();
	if ((e1.radio + e2.radio) >= dist)
	{
		Vector2D dist1 = e1.posicion - e2.posicion, dist2 = e2.posicion - e1.posicion;
		i.velocidad = e1.velocidad - dist1 * ((2 * a2) / (a1 + a2)) * ((e1.velocidad - e2.velocidad) * dist1) * (1 / (dist * dist));
		j.velocidad = e2.velocidad - dist2 * ((2 * a1) / (a2 + a1)) * ((e2.velocidad - e1.velocidad) * dist2) * (1 / (dist * dist));
		e1.velocidad = i.velocidad;
		e2.velocidad = j.velocidad;
	}
}*/
