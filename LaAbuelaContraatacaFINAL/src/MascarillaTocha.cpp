#include "MascarillaTocha.h"
MascarillaTocha::MascarillaTocha() {//constructor
	tipo = MATOCHA;
	color.r = color.b = color.g = 250;
	lado = 3.0f;
}
MascarillaTocha::~MascarillaTocha() {//destructor 

}
MascarillaTocha::MascarillaTocha(float l, float x, float y, float vx, float vy)
{
	tipo = MATOCHA;
	lado = l;
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
	sprite1.draw();
	glPopMatrix();
}