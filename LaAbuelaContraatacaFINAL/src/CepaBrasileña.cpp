#include "CepaBrasile�a.h"
CepaBrasile�a::CepaBrasile�a()
{
	tipo = CEPABRASILE�A;
	altura = 0.4f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	aceleracion.y = -9.8f;
	origenSalto = getPos();
	vidas = 1;
}
CepaBrasile�a::CepaBrasile�a(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRASILE�A;
	altura = alt;
	sprite.setCenter(altura/2.0f, altura/2.0f);
	sprite.setSize(altura, altura);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = -9.8f;
	origenSalto = getPos();
}
void CepaBrasile�a::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 200.0f, 200.0f);
	
	//ANIMACION DEL SPRITE DEL PERSONAJE:

	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	glPopMatrix();
}
void CepaBrasile�a::saltar(float alto)
{
	setVel(velocidad.x, alto);
}
void CepaBrasile�a::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}