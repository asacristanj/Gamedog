#include "Quirurgica.h"
Quirurgica::Quirurgica() {//constructor
	tipo = QUIRURGICA;
	color.b = 100;
	color.g = color.r = 0;
	sprite.setCenter(lado/1.5f, lado / 2.0f);
	sprite.setSize(lado*1.5f, lado);
}
Quirurgica::~Quirurgica(){//destructor

}
Quirurgica::Quirurgica(float l, float x, float y, float vx, float vy)
{
	tipo = QUIRURGICA;
	sprite.setCenter(lado / 1.5f, lado / 2.0f);
	sprite.setSize(lado * 1.5f, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.b = 100;
	color.g = color.r = 0;
	aceleracion.y = -9.8;
}
void Quirurgica::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	//glColor3f(0.0f, 0.0f, 100.0f);
	//glutSolidCube(lado);
	sprite.draw();
	glPopMatrix();
}