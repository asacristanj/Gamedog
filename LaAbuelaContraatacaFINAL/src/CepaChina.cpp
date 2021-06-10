#include "CepaChina.h"

CepaChina::CepaChina()
{
	tipo = CEPACHINA;
	altura = 1.0f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f); 
	sprite.setSize(altura, altura); //DIMENSIONES DE UNA CEPA GENERICA
	color.g = color.b = 0;
	color.r = 100;
	aceleracion = (0.0f, 0.0f);
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