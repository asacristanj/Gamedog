#include "Enemigo.h"
#include "freeglut.h" 
Enemigo::Enemigo()
{
	tipo = NINGUNO;
	altura = 0.8f;
	aceleracion.y = -9.8f;
	color.r = color.b = 0;
	color.g = 100;

	//TAMAÑO Y CENTRO SPRITE:
	spritebras.setCenter(1, 1);
	spritebras.setSize(2, 2);
	spritechin.setCenter(1, 1);
	spritechin.setSize(2, 2);
	spriteindi.setCenter(1, 1);
	spriteindi.setSize(2, 2);
	spritebrit.setCenter(1, 1);
	spritebrit.setSize(2, 2);

}
Enemigo::Enemigo(float alt, float x, float y, float vx, float vy)
{
	tipo = NINGUNO;
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
	//glutSolidSphere(altura, 15, 15);

	//ANIMACION DEL SPRITE DEL PERSONAJE:
/*
	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	*/
	glPopMatrix();
}
void Enemigo::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	spritebras.loop();
	spritechin.loop();
	spritebrit.loop();
	spriteindi.loop();

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
Enemigo :: ~Enemigo()
{

}
