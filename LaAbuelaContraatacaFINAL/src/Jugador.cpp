#include "Jugador.h"
#include "freeglut.h" 
Jugador::Jugador()
{
	altura = 1.8f;
	aceleracion.y = -20.0f;
	posicion.x = 0.0f;
	posicion.y = 1.8f;
}
void Jugador::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(altura, 20, 20);
	glPopMatrix();
}
void Jugador::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void Jugador::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
void Jugador::salto()
{
	setVel(velocidad.x, impulso);
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