#include "Jugador.h"
#include "freeglut.h" 
Jugador::Jugador()
{
	altura = 0.9f;
	aceleracion.y = acel_inicial;
	posicion.x = 0.0f;
	posicion.y = 1.8f;
}
void Jugador::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void Jugador::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void Jugador::setPos(float ix, float iy)
{
	posicion.x += ix;
	posicion.y += iy;
}
void Jugador::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
void Jugador::setAcel(float ax)
{
	aceleracion.x = ax;
}
void Jugador::salto(float imp)
{
	setVel(velocidad.x, imp);
}
/*
void Jugador::movLateral(float ix)
{
	posicion.x += ix;
}
*/

Jugador :: ~Jugador()
{

}