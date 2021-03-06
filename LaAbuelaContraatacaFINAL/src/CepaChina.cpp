#include "CepaChina.h"

CepaChina::CepaChina()
{
	tipo = CEPACHINA;
	altura = 1.5f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f); 
	sprite.setSize(altura, altura); //DIMENSIONES DE UNA CEPA GENERICA
	aceleracion = (0.0f, 0.0f);
	vidas = 1;
}

CepaChina::CepaChina(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPACHINA;
	altura = alt;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	aceleracion.y = -9.8f;
}
void CepaChina::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(255.0f, 0.0f, 0.0f);
	
	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	
	
	glPopMatrix();
}
void CepaChina::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}