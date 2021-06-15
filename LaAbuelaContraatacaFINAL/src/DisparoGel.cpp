#include "DisparoGel.h"
#include "freeglut.h" 
DisparoGel::DisparoGel()
{
	radio = 1.0f;
	aceleracion.x = aceleracion.y = 0.0f;
	sprite.setCenter(radio*1.2f/ 2.0f, radio/2.0f);
	sprite.setSize(radio*1.2f, radio);
}
void DisparoGel::dibuja()
{

	glColor3f(0.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
	{
		sprite.setAngle(90.0f);
		sprite.flip(false, false);
	}
	sprite.draw();
	glPopMatrix();
}
void DisparoGel::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}
void DisparoGel::setPos(float ix, float iy)
{
	origen.x=posicion.x = ix;
	origen.y=posicion.y = iy;
}
DisparoGel :: ~DisparoGel()
{

}
