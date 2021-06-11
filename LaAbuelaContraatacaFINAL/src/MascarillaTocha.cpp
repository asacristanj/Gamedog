#include "MascarillaTocha.h"
MascarillaTocha::MascarillaTocha() {//constructor
	tipo = MATOCHA;
	color.r = color.b = color.g = 250;
	lado = 3.0f;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
}
MascarillaTocha::~MascarillaTocha() {//destructor 

}
MascarillaTocha::MascarillaTocha(float l, float x, float y, float vx, float vy)
{
	tipo = MATOCHA;
	lado = l;
	sprite.setCenter(lado / 2.0f, lado / 2.0f);
	sprite.setSize(lado, lado);
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = color.b = color.g=250;
	aceleracion.y = -9.8;
}
void MascarillaTocha::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(250.0f, 250.0f, 250.0f);
	//glutSolidCube(lado);
	sprite.draw();
	glPopMatrix();
}