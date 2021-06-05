#include "Interaccion.h"
#include "freeglut.h" 
#include <math.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>
//#include <stdio.h>
#define PI 3.141592
void Interaccion::rebote(Jugador& j, Escenario e)
{
	//Funci�n para que el jugador no se pueda salir del escenario. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde del escenario
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (j.posicion.x+j.altura > xmax)j.posicion.x = xmax-j.altura;
	if (j.posicion.x-j.altura< xmin)j.posicion.x = xmin+j.altura;

	float ymin = e.suelo.limite1.y;
	if ((j.posicion.y - j.altura) < ymin) j.posicion.y = ymin+j.altura;
}
void Interaccion::rebote(Jugador& j, Plataforma p)
{
	//Funci�n para que el jugador no pueda atravesar las plataformas.Coge sus l�mites y dice que si choca por encima se quede arriba y se choca por debajo que se queda abajo fren�ndose debido al choque.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y= p.limite1.y;
	if (Interaccion::colisionEncima(j, p))
	{
		// freno al personaje
		j.velocidad.y = 0.0f;
		j.aceleracion.y = 0.0f;
		j.posicion.y = y + j.altura;
	}
	else
		j.aceleracion.y = j.acel_inicial; // vuelvo a recuperar la aceleracion inicial

	if (Interaccion::colisionDebajo(j, p))
		j.velocidad.y = -5.0f; // el jugador rebota ligeramente al tocar la plataforma
	/*if (Interaccion::colisionLadoDer(j, p))
		j.velocidad.x = 0.0f; // el jugador rebota ligeramente al tocar la plataforma
	if (Interaccion::colisionLadoIzq(j, p))
		j.velocidad.x = 0.0f; // el jugador rebota ligeramente al tocar la plataforma*/
}
bool Interaccion::colision(Bonus b, Jugador j) {//Funcion que manda true si el jugador entra en contacto con un bonus general
	Vector2D pos = j.getPos();
	float distancia = (b.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Quirurgica q, Jugador j) {//Funcion que manda true si el jugador entra en contacto con la quirurgica
	Vector2D pos = j.getPos();
	float distancia = (q.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(MascarillaTocha m, Jugador j) {//Funcion que manda true si el jugador entra en contacto con la mascarilla tocha
	Vector2D pos = j.getPos();
	float distancia = (m.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Astrazeneca a, Jugador j) {//Funcion que manda true si el jugador entra en contacto con Astrazeneca
	Vector2D pos = j.getPos();
	float distancia = (a.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Janssen jan, Jugador j) {//Funcion que manda true si el jugador entra en contacto con Janssen
	Vector2D pos = j.getPos();
	float distancia = (jan.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Pfizer pfi, Jugador j) {//Funcion que manda true si el jugador entra en contacto con Pfizer
	Vector2D pos = j.getPos();
	float distancia = (pfi.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Sputnik sp , Jugador j) {//Funcion que manda true si el jugador entra en contacto con Sputnik
	Vector2D pos = j.getPos();
	float distancia = (sp.getPos() - pos).modulo();
	if ((distancia <= ((j.altura)))) {
		return true;
	}
	return false;
}
//funcion que hace que el bonus no se vaya del escenario y choque en las plataformas:
void Interaccion::rebote(Bonus& b, Plataforma p) {//meto el esceneario para que haya aceleracion de plataforma a escenario y no haya en el escenario
	/*float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float y = p.limite1.y;
	*/
	if (Interaccion::colision(b, p)) {
		b.velocidad.y = 0.0f;
		b.aceleracion.y = 0.0f;
	}
	else {
		b.aceleracion.y = -2.0f;
	}
}
void Interaccion::rebote(Bonus& b, Escenario e) {
	if (Interaccion::colision(b, e.suelo)) {
		b.velocidad.y = 0;
		b.aceleracion.y = 0;
	}
	float ymin = e.suelo.limite1.y;
	if ((b.posicion.y - b.lado) < ymin) b.posicion.y = ymin + b.lado/2;
}
void Interaccion::rebote(Quirurgica& qui, Escenario e) {
	//Funcion que hace el bonus de quirurgica circule por el escenario y si choca con una pared rebote como seta de mario bros
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	float smax = e.suelo.limite2.x;
	float smin = e.suelo.limite1.x;
	float ymin = e.suelo.limite1.y;
	if ((qui.posicion.y - qui.lado / 2) < ymin) {
		qui.posicion.y = ymin + qui.lado / 2;
	}
	if (qui.posicion.x > xmax)
	{
		qui.posicion.x = xmax;
		qui.velocidad.x = -3.0f;
	}
	if (qui.posicion.x < xmin)
	{
		qui.posicion.x = xmin;
		qui.velocidad.x = 3.0f;
	}
}
bool Interaccion::colision(Bonus b, Plataforma p) {//Funcion que manda true si hay colision entre el bonus y una plataforma. Mide distancia entre ellas y compara
	Vector2D pos = b.getPos();
	pos.y += b.getlado() / 2;//se le resta el lado para que se apoye en la superficie de abajo
	float distancia = p.distancia(pos);
	if (distancia <= 0.1f + b.getlado()) {
		return true;
	}
	return false;
}
bool Interaccion::colision(Bonus& b, Escenario e) {//Funcion que manda true si hay colision entre bonus y escenario. Mide distancia entre ellas y compara
	float xmax = e.suelo.limite2.x;
	float xmin = e.suelo.limite1.x;
	if (b.posicion.x + b.lado > xmax) {
		b.posicion.x = xmax - b.lado;
		b.velocidad.x = -4.0f;
	}
	if (b.posicion.x - b.lado < xmin) {
		b.posicion.x = xmin + b.lado;
		b.velocidad.x = 4.0f;
	}
	Vector2D pos = b.getPos();
	pos.y -= b.getlado() / 2;//se le resta el lado para que quede apoyado en a superficie de abajo
	float distancia = e.suelo.distancia(pos);
	if (distancia <= 0.1f) {
		return true;
	}
	return false;
}

/*void Interaccion::rebote(Enemigo& enem, Plataforma p)
{
	//Funci�n para que los enemgios no se puedan salir de las plataformas. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (enem.posicion.x > xmax)
	{
		enem.posicion.x = xmax;
		enem.velocidad.x = -4.0f;
	}
	if (enem.posicion.x < xmin)
	{
		enem.posicion.x = xmin;
		enem.velocidad.x = 4.0f;
	}

	float ymin = p.limite1.y;
	if ((enem.posicion.y - enem.altura) < ymin) enem.posicion.y = ymin + enem.altura;
}*/
void Interaccion::rebote(CepaIndia& ind, Plataforma p)
{
	//Funci�n para que los enemgios no se puedan salir de las plataformas. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (ind.posicion.x > xmax)
	{
		ind.posicion.x = xmax;
		ind.velocidad.x = -5.0f;
	}
	if (ind.posicion.x < xmin)
	{
		ind.posicion.x = xmin;
		ind.velocidad.x = 5.0f;
	}

	float ymin = p.limite1.y;
	if ((ind.posicion.y - ind.altura) < ymin) ind.posicion.y = ymin + ind.altura;
}
void Interaccion::rebote(CepaBritanica& brit, Plataforma p)
{
	//Funci�n para que los enemgios no se puedan salir de las plataformas. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	if (brit.posicion.x > xmax)
	{
		brit.posicion.x = xmax;
		brit.velocidad.x = -3.0f;
	}
	if (brit.posicion.x < xmin)
	{
		brit.posicion.x = xmin;
		brit.velocidad.x = 3.0f;
	}

	float ymin = p.limite1.y;
	if ((brit.posicion.y - brit.altura) < ymin) brit.posicion.y = ymin + brit.altura;
}
void Interaccion::rebote(CepaBrasile�a& bra, Plataforma p)
{
	//Funci�n para que los enemgios no se puedan salir de las plataformas. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float ymin = p.limite1.y;
	/*Vector2D deltax = bra.getPos();
	float recorrido = deltax.x - bra.origenSalto.x;
	if (recorrido < 0)
		recorrido = -recorrido;
	if (recorrido >= 2.1f && (bra.posicion.y - bra.altura) < ymin)
	{
		bra.saltar();
		bra.origenSalto = bra.getPos();
	}*/
	if (bra.posicion.x > xmax)
	{
		bra.posicion.x = xmax;
		bra.velocidad.x = -2.0f;
	}
	if (bra.posicion.x < xmin)
	{
		bra.posicion.x = xmin;
		bra.velocidad.x = 2.0f;
	}
	if ((bra.posicion.y - bra.altura) < ymin && bra.posicion.x >= xmin && bra.posicion.x <= xmax)
	{
		bra.posicion.y = ymin + bra.altura;
		int SemillaAl= rand();
		srand(time(NULL) * SemillaAl);
		int i, n, aleatorio, DESDE = 5, HASTA = 10;
		aleatorio = rand() % (HASTA - DESDE + 1) + DESDE;
		bra.saltar(aleatorio);
	}
}
bool Interaccion::rebote(Enemigo enem, Plataforma p)
{
	//Funci�n para que los enemgios no se puedan salir de las plataformas. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = p.limite2.x;
	float xmin = p.limite1.x;
	float ymin = p.limite1.y;
	if (((enem.posicion.y - enem.altura) < ymin) && enem.posicion.x>=xmin && enem.posicion.x <= xmax)
		return true;
	return false;
}
/*bool Interaccion::rebote(CepaIndia& ind, Jugador j)
{
	if (Interaccion::colision(ind, j))
	{
		j.morir();
		return false;
	}
	else if (Interaccion::colisionEncima(ind, j))
		return true;
}
void Interaccion::rebote(CepaChina& chin, Jugador j)
{
	if (Interaccion::colision(chin, j) || Interaccion::colisionEncima(chin, j))
		j.morir();
}*/
void Interaccion::rebote(CepaIndia& ind, Escenario e)
{
	//Funci�n para que los enemgios no se puedan salir del escenario. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	if (ind.posicion.x > xmax)
	{
		ind.posicion.x = xmax;
		ind.velocidad.x = -5.0f;
	}
	if (ind.posicion.x < xmin)
	{
		ind.posicion.x = xmin;
		ind.velocidad.x = 5.0f;
	}
}
void Interaccion::rebote(CepaBritanica& brit, Escenario e)
{
	//Funci�n para que los enemgios no se puedan salir del escenario. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	if (brit.posicion.x > xmax)
	{
		brit.posicion.x = xmax;
		brit.velocidad.x = -3.0f;
	}
	if (brit.posicion.x < xmin)
	{
		brit.posicion.x = xmin;
		brit.velocidad.x = 3.0f;
	}
}

bool Interaccion::rebote(Enemigo enem, Escenario e)
{
	//Funci�n para que los enemgios no se puedan salir del escenario. Coge sus l�mites y dice que si sobrepasa estos se quede en el borde y adem�s que vayan al sentido contrario.
	float xmax = e.pared_dcha.limite2.x;
	float xmin = e.pared_izq.limite2.x;
	if (enem.posicion.x <= xmin && enem.posicion.x >= xmax)
		return true;
	return false;
}
bool Interaccion::colision(Enemigo enem, Jugador j)
{
	//Funci�n que manda un booleano si ha habido contacto entre un enemigo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo();
	if ((distancia <= (enem.altura + (j.altura/2))) && (enem.posicion.y  >= j.posicion.y))
		return true;
	return false;
}
bool Interaccion::colisionEncima(Enemigo enem, Jugador j)
{
	//Funci�n que manda un booleano si ha habido contacto entre un enemigo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del hombre
	float distancia = (enem.getPos() - pos).modulo();
	if ((distancia <= (enem.altura + (j.altura / 2))) && (enem.posicion.y < j.posicion.y))
		return true;
	return false;
}
bool Interaccion::colisionDebajo(Jugador j, Plataforma p)
{
	//Funci�n que manda un booleano si ha habido contacto entre la plataforma y la cabeza del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.y += (j.getAltura());
	float distancia = p.distancia(pos);
	if (distancia <= 0.2f)//compara la distancia de la plataforma al jugador con un valor peque�o
		return true;
	return false;
}
bool Interaccion::colisionEncima(Jugador j, Plataforma p)
{
	//Funci�n que manda un booleano si ha habido contacto entre la plataforma y los pies del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.y -= (j.getAltura() / 2.0f);
	float distancia = p.distancia(pos);
	if (distancia <= j.getAltura())
		return true;
	return false;
}
bool Interaccion::colisionLadoDer(Jugador j, Plataforma p)
{
	//Funci�n que manda un booleano si ha habido contacto entre la plataforma y el lado izquierdo del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.x += (j.getAltura());
	float distancia = p.distancia(pos);
	if (distancia <= 0.2f)
		return true;
	return false;
}
bool Interaccion::colisionLadoIzq(Jugador j, Plataforma p)
{
	//Funci�n que manda un booleano si ha habido contacto entre la plataforma y el lado derecho del jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	pos.x -= (j.getAltura());
	float distancia = p.distancia(pos);
	if (distancia <= 0.2f)
		return true;
	return false;
}
bool Interaccion::colisionSuelo(Jugador j, Escenario e)
{
	//Funci�n que manda un booleano si ha habido contacto entre el suelo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = j.getPos(); //la posicion de la base del jugador
	float distancia = e.suelo.distancia(pos);
	if (distancia <= j.getAltura())
		return true;
	return false;
}

bool Interaccion::colision(DisparoGel d, Plataforma p)
{
	//Funci�n que manda un booleano si ha habido contacto entre un disparo y una plataforma. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D pos = d.getPos(); //la posicion de la base del disparo
	pos.y += d.getRadio(); //posicion del centro 
	float distancia = p.distancia(pos);
	if (distancia <= d.getRadio()) 
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Escenario e)
{
	//Funci�n que manda un booleano si ha habido contacto entre un disparo y el escenario. 
	if (Interaccion::colision(d, e.pared_dcha) || Interaccion::colision(d, e.techo) || Interaccion::colision(d, e.pared_izq)||Interaccion::colision(d,e.suelo))
		return true;
	return false;
}
bool Interaccion::colision(DisparoGel d, Enemigo enem) 
{
	//Funci�n que manda un booleano si ha habido contacto entre un disparo y un enemigo. Coge ambas posiciones y mide la distancia entre ellas.
	//un vector para la diferencia de posiciones y dos floats para las distancias a comparar
	Plataforma aux; //Creamos una pared auxiliar
	Vector2D p1 = d.posicion;
	Vector2D p2 = d.origen;
	aux.setPos(p1.x, p1.y, p2.x, p2.y); //Que coincida con el disparo.
	float dist = aux.distancia(enem.posicion); //para calcular su distancia 
	if (dist < (enem.altura/2.0f))
		return true;
	return false;
}
bool Interaccion::colision(CepaChina c, Plataforma p)
{
	Vector2D pos = c.getPos(); //la posicion del centro de la cepa
	float distancia = p.distancia(pos);
	if (distancia <= c.getRadio())
		return true;
	return false;
}
bool Interaccion::colision(CepaChina c, Escenario e)
{
	if (Interaccion::colision(c, e.pared_dcha) || Interaccion::colision(c, e.pared_izq) || Interaccion::colision(c, e.suelo))
		return true;
	return false;
}
bool Interaccion::colision(CepaChina c, Enemigo enem)
{
	Plataforma aux; //Creamos una pared auxiliar
	Vector2D p1 = c.posicion;
	Vector2D p2 = c.origen;
	aux.setPos(p1.x, p1.y, p2.x, p2.y); //Que coincida con el disparo.
	float dist = aux.distancia(enem.posicion); //para calcular su distancia 
	if (dist < (enem.altura / 2.0f))
		return true;
	return false;
}
bool Interaccion::ratio(CepaBritanica brit, Jugador j)
{
	//Funci�n que manda un booleano si ha habido contacto entre un enemigo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D posjugador = j.getPos(); //la posicion de la base del hombre
	posjugador.y -= j.getAltura();
	Vector2D posenemigo = brit.getPos();
	posenemigo.y -= brit.getAltura();
	//((posjugador.y+0.1f>=posenemigo.y) || (posenemigo.y + 0.1f >= posjugador.y))
	float distancia = (brit.getPos() - j.getPos()).modulo();
	if ((posjugador.y + 0.1f >= posenemigo.y) && distancia <= ((brit.getAltura() / 2.0f) + (j.getAltura() / 2.0f)+2.0f))
		return true;
	return false;
}
bool Interaccion::ratioExplosion(CepaBritanica brit, Jugador j)
{
	//Funci�n que manda un booleano si ha habido contacto entre un enemigo y el jugador. Coge ambas posiciones y mide la distancia entre ellas.
	Vector2D posjugador = j.getPos(); //la posicion de la base del hombre
	posjugador.y -= j.getAltura();
	Vector2D posenemigo = brit.getPos();
	posenemigo.y -= brit.getAltura();
	//((posjugador.y+0.1f>=posenemigo.y) || (posenemigo.y + 0.1f >= posjugador.y))
	float distancia = (brit.getPos() - j.getPos()).modulo();
	if ((posjugador.y + 0.1f >= posenemigo.y) && distancia <= ((brit.getAltura() / 2.0f) + (j.getAltura() / 2.0f) + 3.0f))
		return true;
	return false;
}
bool Interaccion::colisionDebajo(Jugador j, BloqueSorpresa b) {
	//Calculamos la distancia entre el bloque y el jugador para detectar si hay colision;
	Vector2D aux,bloque=b.posicion,jugador=j.getPos();
	float radio = j.getAltura(), l = b.lado * 0.5f;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio + l)&& (jugador.y<=bloque.y)) {
		return true;

	}
	else 
		return false;
}
bool Interaccion::colisionEncima(Jugador j, BloqueSorpresa b) {
	Vector2D aux, bloque = b.posicion, jugador = j.getPos();
	float radio = j.getAltura(), l = b.lado * 0.5f;
	aux = bloque - jugador;
	float distancia = aux.modulo();
	if ((distancia <= radio + l) && (jugador.y >= bloque.y))
		return true;
	return false;
}
void Interaccion::rebote(Jugador& j,BloqueSorpresa b) {
	//Si el choque se produce desde abajo
	if (Interaccion::colisionDebajo(j, b)) {
		j.velocidad.y = -5.0f;
		j.tocandosuelo = true;
	}
	if (Interaccion::colisionEncima(j, b)) {
		float y = b.posicion.y+b.getlado()*0.5f;
		j.velocidad.y = 0.0f;
		j.aceleracion.y = 0.0f;
		j.posicion.y =y+ j.altura;
	}
}
bool Interaccion::colisionEscalera(Escalera e, Jugador j) {
	//Comprobamos que la posicion del jugador esta entre los limites de la escalera
	Vector2D limites = e.limenx();
	Vector2D pos = j.getPos();
	if (limites.y <= pos.x <= limites.x)
		return true;
	return false;
}