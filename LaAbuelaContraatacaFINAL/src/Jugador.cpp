#include "Jugador.h"
#include "freeglut.h" 
Jugador::Jugador()
{
	altura = 0.9f;
	aceleracion.y = acel_inicial;
	posicion.x = 0.0f;
	posicion.y = 1.8f;
	numbonus = 0;
}
void Jugador::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(altura, 15, 15);
	glPopMatrix();
}
void Jugador::salto()
{
	setVel(velocidad.x, impulso);
	tocandosuelo = false;
}
void Jugador::morir()
{
	altura = 0.0f;
}
void Jugador::crecer(){
	setAltura(2.0 * altura); // el doble de grande
}
//void Jugador::IncrementaNumBonus() {

//}
Jugador :: ~Jugador()
{

}
void Jugador::subirEscalera() {
	this->setVely(0.0f);
}
bool Jugador::suelo() {
	return tocandosuelo;
}