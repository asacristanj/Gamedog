#include "Jugador.h"
#include "freeglut.h"
Jugador::Jugador()
{
	altura = 1.0f;
	posicion_inicial = (0.0f, 2.0f);

	//TAMAÑO Y CENTRO SPRITE PERSONAJE:
	sprite.setCenter(altura/2.0f, altura);
	sprite.setSize(altura, altura * 2.0f);

	tocandosuelo = false;
	coeficiente_velx = 1.0f;
	aceleracion.y = acel_inicial;
	posicion.x = posicion_inicial.x;
	posicion.y = posicion_inicial.y;
	numbonus = 0;
}
void Jugador::dibuja()
{
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	//glutSolidSphere(altura, 15, 15);

	
	//ANIMACION DEL SPRITE DEL PERSONAJE:

	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();

	glPopMatrix();
	
}
void Jugador::salto()
{
	setVel(velocidad.x, impulso);
	tocandosuelo = false;
}
void Jugador::morir()
{
	posicion = posicion_inicial; // vuelve a una posición inicial
}

/*void Jugador::crecer(){
	setAltura(2.0 * altura); // el doble de grande
}*/
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


void Jugador::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	sprite.loop();
}

