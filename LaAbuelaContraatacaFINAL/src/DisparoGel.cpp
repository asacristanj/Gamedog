#include "DisparoGel.h"
#include "freeglut.h" 
DisparoGel::DisparoGel()
{
	radio = 0.25f;
	aceleracion.x = aceleracion.y = 0.0f;
}
void DisparoGel::dibuja()
{
	glColor3f(0.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glutSolidSphere(radio, 20, 20);
	glPopMatrix();
}
void DisparoGel::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
}
void DisparoGel::setPos(float ix, float iy)
{
	origen.x=posicion.x = ix;
	origen.y=posicion.y = iy;
}
void DisparoGel::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
DisparoGel :: ~DisparoGel()
{

}
