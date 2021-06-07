#include "CepaBrasileņa.h"
CepaBrasileņa::CepaBrasileņa()
{
	tipo = CEPABRASILEŅA;
	altura = 0.4f;
	color.r = color.g = 100;
	color.b = 0;
	aceleracion.y = -9.8f;
	origenSalto = getPos();
}
CepaBrasileņa::CepaBrasileņa(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRASILEŅA;
	altura = alt;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = -9.8f;
	origenSalto = getPos();
}
void CepaBrasileņa::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	
	//glutSolidSphere(altura, 15, 15);
	//ANIMACION DEL SPRITE DEL PERSONAJE:

	if (velocidad.x > 0.01)spritebras.flip(false, false);
	if (velocidad.x < -0.01)spritebras.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		spritebras.setState(0);
	else if (spritebras.getState() == 0)
		spritebras.setState(1, false);
	spritebras.draw();


	glPopMatrix();
}
void CepaBrasileņa::saltar(float alto)
{
	setVel(velocidad.x, alto);
}
