#include "Jugador.h"
#include "freeglut.h" 
Jugador::Jugador()
{
	altura = 1.8f;
	aceleracion.y = 0;
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
Jugador :: ~Jugador()
{

}