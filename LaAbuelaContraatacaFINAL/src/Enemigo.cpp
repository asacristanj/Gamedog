#include "Enemigo.h"
#include "freeglut.h" 
Enemigo::Enemigo()
{
	altura = 1.8f;
	aceleracion.y = 0;
}
void Enemigo::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(altura, 20, 20);
	glPopMatrix();
}
void Enemigo::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void Enemigo::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
Enemigo :: ~Enemigo()
{

}