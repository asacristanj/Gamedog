#include "Llave.h"
Llave::Llave() {
	color.r = 233;
	color.g = 233;
	color.b = 0;
	lado = 1.0f;
}
Llave::Llave(float l, float x, float y, float vx, float vy) {
	lado = l;
	posicion.x = x;
	posicion.y = y;
	velocidad.x = vx;
	velocidad.y = vy;
	color.r = 233;
	color.g = 233;
	color.b = 233;
}
Llave::~Llave() {

}
void Llave::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(250.0f, 250.0f, 250.0f);
	glutSolidCube(lado);
	//sprite6.draw();
	glPopMatrix();
}
float Llave::getLado() {
	return lado;
}