#include "BloqueSorpresa.h"

BloqueSorpresa::BloqueSorpresa() {
	color.b= 0;
	color.g = color.b = 255;
	posicion.x = posicion.y = 0;
	lado = 1.0f;
	usado = false;
}
BloqueSorpresa::BloqueSorpresa(float l, float x, float y, unsigned char r,unsigned char g,unsigned char b){
	posicion.x = x;
	posicion.y = y;
	lado = l;
	color.r = r;
	color.g = g;
	color.b = b;
	usado = false;
}
BloqueSorpresa::~BloqueSorpresa() {

}
void BloqueSorpresa::dibuja() {
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glRotatef(30, 1, 1, 1);
	glColor3f(color.r,color.b,color.g);//color aleatorio 
	glutSolidCube(lado);
	glPopMatrix();
}
float BloqueSorpresa::getlado() {
	return lado;
}
void BloqueSorpresa::setPos(float x, float y) {
	posicion.x = x;
	posicion.y = y;
}
void BloqueSorpresa::setColor(unsigned char r, unsigned char g, unsigned char b) {
	color.r = r;
	color.g = g;
	color.b = b;
}
bool BloqueSorpresa::getuso() {
	return usado;
}