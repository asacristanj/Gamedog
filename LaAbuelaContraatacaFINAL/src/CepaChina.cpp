#include "CepaChina.h"
CepaChina::CepaChina()
{
	tipo = CEPACHINA;
	altura = 0.4f;
	color.g = color.b = 0;
	color.r = 100;
	aceleracion = (0.0f, 0.0f);
}
CepaChina::CepaChina(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPACHINA;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
}
void CepaChina::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(255.0f, 0.0f, 0.0f);
	//glutSolidSphere(altura, 15, 15);
	if (velocidad.x > 0.01)spritechin.flip(false, false);
	if (velocidad.x < -0.01)spritechin.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		spritechin.setState(0);
	else if (spritechin.getState() == 0)
		spritechin.setState(1, false);
	spritechin.draw();
	glPopMatrix();
}