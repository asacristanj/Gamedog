#include "CepaBritanica.h"
CepaBritanica::CepaBritanica()
{
	tipo = CEPABRITANICA;
	altura = 1.9f;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	color.b = 200;
	color.r = color.g = 0;
	posicion.x = 1.0f;
	posicion.y = 5.0f;
	velocidad.x = 3.0f;
	aceleracion.y = 0.0f;
	vidas = 1;
	inicializar_hora_inicio = false;
}
CepaBritanica::CepaBritanica(float alt, float x, float y, float vx, float vy)
{
	tipo = CEPABRITANICA;
	altura = alt;
	sprite.setCenter(altura / 2.0f, altura / 2.0f);
	sprite.setSize(altura, altura);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = 0;
	color.g = 100;
	aceleracion.y = 0.0f;
	inicializar_hora_inicio = false;
}
void CepaBritanica::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(0.0f, 0.0f, 255.0f);
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
void CepaBritanica::explotar()
{
	altura = 0.0f;
}
void CepaBritanica::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}