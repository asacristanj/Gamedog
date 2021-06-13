#include "Jugador.h"
#include "freeglut.h"
#include <iostream>
using namespace std;
using namespace ETSIDI;
Jugador::Jugador()
{
	altura = 1.2f;
	posicion_inicial = (0.0f, 2.0f);

	//TAMAÑO Y CENTRO SPRITE PERSONAJE:
	sprite.setCenter(altura/2.0f, altura);
	sprite.setSize(altura, altura * 2.0f);
	spritemasc.setCenter(altura / 2.0f, altura);
	spritemasc.setSize(altura, altura * 2.0f);
	spriteffp2.setCenter(altura / 2.0f, altura);
	spriteffp2.setSize(altura, altura * 2.0f);

	tocandosuelo = false;
	escalera = false;
	coeficiente_velx = 1.0f;
	aceleracion.y = acel_inicial;
	posicion.x = posicion_inicial.x;
	posicion.y = posicion_inicial.y;
	//condiciones iniciales de velocidad
	velocidad.y = 0;
	velocidad.x = 0;
	numbonus = 0;
	astra_activo = pfizer_activo = janssen_activo = false;
	horaInicioAstra = horaInicioPfizer = horaInicioJanssen = time(NULL);
	numLlaves = 0;
	puntuacion = 0; // empieza con 0 puntos
}
void Jugador::dibuja()
{
	
	glPushMatrix();
	glTranslatef(posicion.x, posicion.y-0.1f, 0);
	glColor3f(1.0f, 0.0f, 0.0f);

	//glutSolidSphere(altura, 15, 15);
	//ANIMACION DEL SPRITE DEL PERSONAJE:
	if (getNumBonus() == 0) { //SI NO TIENE BONUS, SKIN DEFAULT
	if (velocidad.x > 0.01)sprite.flip(false, false);
	if (velocidad.x < -0.01)sprite.flip(true, false);
	if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
		sprite.setState(0);
	else if (sprite.getState() == 0)
		sprite.setState(1, false);
	sprite.draw();
	glPopMatrix();
	}
	if (getNumBonus() == 1) { //SI TIENE BONUS, SKIN MASCARILLA
		if (velocidad.x > 0.01)spritemasc.flip(false, false);
		if (velocidad.x < -0.01)spritemasc.flip(true, false);
		if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
			spritemasc.setState(0);
		else if (spritemasc.getState() == 0)
			spritemasc.setState(1, false);
		spritemasc.draw();
		glPopMatrix();
	}
	if (getNumBonus() == 2) { //SI TIENE DOS BONUS, SKIN FFP2
		if (velocidad.x > 0.01)spriteffp2.flip(false, false);
		if (velocidad.x < -0.01)spriteffp2.flip(true, false);
		if ((velocidad.x < 0.01) && (velocidad.x > -0.01))
			spriteffp2.setState(0);
		else if (spriteffp2.getState() == 0)
			spriteffp2.setState(1, false);
		spriteffp2.draw();
		glPopMatrix();
	}
	
}
void Jugador::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5f * t * t);
	velocidad = velocidad + aceleracion * t;
	Jugador::sonidos();
	Jugador::dañocaida();
	sprite.loop();
	spritemasc.loop();
	spriteffp2.loop();
}
void Jugador::salto()
{
	play("sonidos/salto.wav");
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
void Jugador::volverSalto()
{
	time_t horaActual = time(NULL);
	if (astra_activo == true && (horaActual - horaInicioAstra) > 10)
	{
		astra_activo = false;
		setImpulso(15.0f);
	}
}
void Jugador::volverVelocidadPfizer()
{
	time_t horaActual = time(NULL);
	if (pfizer_activo == true && (horaActual - horaInicioPfizer) > 10)
	{
		pfizer_activo = false;
		setCoefVelx(1);
	}
}
void Jugador::volverVelocidadJanssen()
{
	time_t horaActual = time(NULL);
	if (janssen_activo == true && (horaActual - horaInicioJanssen) > 10)
	{
		janssen_activo = false;
		setCoefVelx(1);
	}
}
void Jugador::subirEscalera() 
{
	this->setVely(0.0f);
}
void Jugador::bajarEscalera() 
{
	this->setVely(0.0f);
}
bool Jugador::suelo()
{
	return tocandosuelo;
}
void Jugador::setEscalera(int i) 
{
	if (i == 1)
		escalera = true;
	else
		escalera = false;
}
/*void Jugador::incrementaLlaves() {
	numLlaves++;
}*/

void Jugador::dañocaida() {

	float distmax = 0.0f;
	float aux2;
	aux2 = aux1;
	aux1 = posicion.y;
	//Aproximación de la distancia máxima entre frame y frame para que 
	//la velocidad sea demasiado negativa como para que la abuela
	//pueda soportarla cuando toque el suelo o una plataforma
	if (altura_max_caida <= 5) //ok
		distmax = 0.39f;
	if (altura_max_caida == 6) //ok
		distmax = 0.44f;
	if (altura_max_caida == 7) //ok
		distmax = 0.45f;
	if (altura_max_caida == 8) //ok
		distmax = 0.50f;
	if (altura_max_caida == 9) //ok
		distmax = 0.57f;
	if (altura_max_caida == 10) //ok
		distmax = 0.59f;
	if (altura_max_caida == 11) //ok
		distmax = 0.62f;
	if (altura_max_caida == 12) //ok
		distmax = 0.66f;
	if (altura_max_caida == 13) //ok
		distmax = 0.68f;
	if (altura_max_caida == 14) //ok
		distmax = 0.70f;
	if (altura_max_caida == 15) //ok
		distmax = 0.74f;
	//A partir de aqui se puede aproximar a una linea recta
	if (altura_max_caida >= 16)
		distmax = 0.76f + 0.02f * (altura_max_caida - 16);
	cout << velocidad.y << endl;
	if ((aux2 - aux1) > distmax) { //la velocidad en y ha sido durante un momeneto demasiado negativa, se activa el bool
		daño_caida = true;
	}
	if ((daño_caida) && (aux2 - aux1) < 0.1f){ //se espera hasta que se vuelva a tocar el suelo para inflingir el daño
		play("sonidos/caida.mp3");
		//numbonus--; //sufre daño por caida
		daño_caida = false; //se resetea el bool
	}
}
void Jugador::sonidos() {
	bool playing = false;
	//if (sprite.getState())
		//play("sonidos/correr.mp3");
	//if (spritemasc.getState())
		//play("sonidos/correr.mp3");
	//play("sonidos/caida.mp3");

}

Jugador :: ~Jugador()
{

}
