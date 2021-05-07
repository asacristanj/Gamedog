#include "Enemigo.h"
#include "freeglut.h" 
Enemigo::Enemigo()
{
	altura = 0.8f;
	aceleracion.y = -9.8f;
	color.r = color.b = 0;
	color.g = 100;
}
Enemigo::Enemigo(float alt, float x, float y, float vx, float vy)
{
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
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
void Enemigo::setColor(Byte r, Byte v, Byte a)
{
	color.r = r;
	color.g = v;
	color.b = a;
}
void Enemigo::setAltura(float alt)
{
	if (alt < 0.1f)alt = 0.1f;
	altura = alt;
}
void Enemigo::setPos(float ix, float iy)
{
	posicion.x = ix;
	posicion.y = iy;
}
void Enemigo::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
Enemigo :: ~Enemigo()
{

}