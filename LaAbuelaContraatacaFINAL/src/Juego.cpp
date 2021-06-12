#include "Juego.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"
#include <time.h>
#include <iostream>
using namespace std;

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
	nivel = 0;//establezco el nivel al principio de cada inicializa
	cargarNivel();//cargo el nivel corrspondiente
	//a partir de aqui todo tendria que estar en el nivel correspondiente
	//enemigos.destruirContenido();//limpio tras game over
	//disparos.destruirContenido();//limpio tras game over
	//jugador.setPos(0.0f, 0.0f);//origen del jugador
	/*plataformas.agregar(new Plataforma(-8.0f, 4.0f, 2.0f, 4.0f));
	plataformas.agregar(new Plataforma(-5.0f, 8.0f, 5.0f, 8.0f));
	escaleras.agregar(new Escalera(3.0f,5.0f,0.0f,4.0f,2.0f));
	escaleras.agregar(new Escalera(-1.0f, 1.0f, 4.0f, 4.0f, 2.0f));*/
	//llaves.agregar(new Llave(1.0f, 7.0f, 2.0f));
	//enemigos.agregar(new Enemigo(1.5f, 0.0f, 10.0f, -1.0f, 0.0f));
	//Agregamos un bonus inicial
	//bonuses.agregar(new Astrazeneca(1.0f, -5.0f, 12.0f));
	//bonuses.agregar(new Janssen(1.5f, -3.0f, 12.0f));
	//bonuses.agregar(new MascarillaTocha(2.0f, -3.0f, 5.0f));
	//enemigos.agregar(new CepaIndia(2.0f, 4.0f, 5.0f, 5.0f, 0.0f));
	//bonuses.agregar(new Pfizer(0.5f, 3.0f, 12.0f, 0,0));
	//bonuses.agregar(new Quirurgica(1.0f, 2.0f, 10.0f, 0.0f, 0.0f));
	//bonuses.agregar(new Quirurgica(1.0f, 5.0f, 12.0f, 0.0f, 0.0f));
	//bonuses.agregar(new Sputnik(0.5f,6.5f,6));
	//enemigos.agregar(new MurcielagoPequeño());
	//enemigos.agregar(new MurcielagoPequeño(1.0f, -2.0f, 10.0f, 4.0f, 4.0f));
	//enemigos.agregar(new MurcielagoBoss(2.0f, 0.0f, 16.0f, 4.0f, 4.0f));
     //enemigos.agregar(new CepaBrasileña(2.0f, -2.0f, 9.0f, 2.0f, 0.0f));
	//enemigos.agregar(new CepaBrasileña(2.0f, 1.0f, 9.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(2.0f, 0.0f, 5.0f, 2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(2.0f, 2.0f, 9.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaChina(2.0f, 0.0f, 15.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaIndia(2.0f, -4.0f, 9.0f, -1.0f, 0.0f));
	//bloques.agregar(new BloqueSorpresa(1.0f, 7.0f, 4.0f));
}

void Juego::moverOjo()
{
	//Se coge la posicion actual del jugador para centrarla en él y se suma una cantidad para ajustarlo al escenario
	Vector2D pos = jugador.getPos();
	y_ojo = pos.y+5.0f;
}

void Juego::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
		0.0, y_ojo, 0.0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)  
	jugador.dibuja();
	enemigos.dibuja();
	bonuses.dibuja();
	disparos.dibuja();
	bloques.dibuja();
	escaleras.dibuja();
	plataformas.dibuja();
	escenario.dibuja();
	llaves.dibuja();
}

void Juego::mueve()
{
	//cout << endl << "Posicion del jugador: " << jugador.getPos().x << ", " << jugador.getPos().y;
	jugador.volverSalto();
	jugador.volverVelocidadPfizer();
	jugador.volverVelocidadJanssen();
	jugador.mueve(0.025f);
	bonuses.mueve(0.025f);
	enemigos.mueve(0.025f);
	disparos.mueve(0.025f);
	enemigos.rebote(escenario);
	if ((subirescaleras == false) && bajarescaleras == false)
		plataformas.rebote(jugador);
	enemigos.rebote(jugador);
	enemigos.reboteBoss(escenario, jugador);
	disparos.colision(escenario);
	bonuses.rebote(escenario);
	bonuses.rebote(jugador);
	llaves.mueve(0.025f);
	llaves.colision(jugador);
	Interaccion::rebote(jugador, escenario);
	//Interaccion::rebote(jugador, plataforma);
	for (int i = 0; i < plataformas.getNumero(); i++)
	{
		enemigos.rebote(*plataformas[i]);
	}
	for (int i = 0; i < plataformas.getNumero(); i++)
	{
		bonuses.rebote(*plataformas[i]);
	}
	for (int i = 0; i < plataformas.getNumero(); i++)
	{
		for (int j = 0; j < disparos.getNumero(); j++)
		{
			if (Interaccion::colision(*disparos[i], *plataformas[i]))
			{
				disparos.eliminar(disparos[i]);
			}
		}
	}
	for (int i = 0; i < enemigos.getNumero(); i++)
	{
		for (int j = 0; j < disparos.getNumero(); j++)
		{
			if (Interaccion::colision(*disparos[j], *enemigos[i]))
			{
				disparos.eliminar(disparos[j]);
				enemigos[i]->setDisparoRecibido(true); // disparo recibido
				cout << endl << "disparo recibido: " << enemigos[i]->getDisparoRecibido() << endl;

				if(enemigos[i]->getTipo() != MURCIELAGOBOSS) // EL BOSS SOLO PIERDE VIDA AL SER PISADO
					enemigos[i]->setVidas(-1); // menos 1 vida

				if (enemigos[i]->getVidas() < 1) // si no le quedan vidas muere
					enemigos.eliminar(enemigos[i]);
			}
		}
	}
	bloques.rebote(jugador);
	bloques.CrearBonus(bonuses, jugador);
	setChances(jugador.getNumBonus());//refrescamos las chances que tiene el jugador continuamente
	setllaveJug(jugador.getNumLlaves());//refrescamos las llaves que tiene el jugador
}
void Juego::teclaEspecial(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		jugador.setVelx(-(jugador.getVelNormal() * jugador.getCoefVelx())); // velocidad normal * coeficiente de velocidad
		break;
	case GLUT_KEY_RIGHT:
		jugador.setVelx((jugador.getVelNormal() * jugador.getCoefVelx()));
		break;
	case GLUT_KEY_UP:
		//Para que no pueda saltar en el aire
		if (escaleras.subirEscalera(jugador))
		{
			subirescaleras = true;
			jugador.setVely(7.0f);
			jugador.setAcely(0.0f);
			if (escaleras.bajarEscalera(jugador)) {
				subirescaleras = false;
			}
			break;
		}
		break;
	case GLUT_KEY_DOWN:
		if (escaleras.bajarEscalera(jugador)) //ponia bajar
		{
			jugador.setAcely(0.0f);
			jugador.setVely(-5.0f);//-(jugador.getVelNormal() * jugador.getCoefVelx())
			jugador.setVelx(0.0f);
			bajarescaleras = true;
			if (escaleras.subirEscalera(jugador)) {
				bajarescaleras = false;
			}
			break;
		}
		break;
	}
}
void Juego::teclaEspecialUp(unsigned char key) //al dejar de pulsar la tecla
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		jugador.setVelx(0.0f); // ESTO NO FUNCIONA!!???
		break;
	case GLUT_KEY_RIGHT:
		jugador.setVelx(0.0f);
		break;
	case GLUT_KEY_UP:
	{
		//Para que no pueda saltar en el aire
		if (escaleras.subirEscalera(jugador))
		{
			jugador.setVely(0.0f);
			jugador.setVelx(0.0f);
			jugador.setAcely(0.0f);
			subirescaleras = false;
		}
		if (escaleras.subirEscalera(jugador) == 0)
		{
			//jugador.setVely(0.0f);
			jugador.setAcely(-30.0f);
			subirescaleras = false;
			break;
		}
		/*if (plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario) || jugador.suelo())
			jugador.salto();*/
	}
	case GLUT_KEY_DOWN:
	{
		if (escaleras.bajarEscalera(jugador) || escaleras.subirEscalera(jugador) == 1) //ponia bajar
		{
			jugador.setVely(0.0f);
			jugador.setVelx(0.0f);
			jugador.setAcely(0.0f);
			bajarescaleras = false;
			break;
		}
	}
	}
}

void Juego::tecla(unsigned char key)
{
	switch (key)
	{
	case ' ':
	{
		if ((plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario) || jugador.suelo()))
		{
			jugador.salto();
		}
		break;
	}
	if (jugador.getNumBonus() == 2) {//solo existen disparos cuando el jugador tiene 2 bonus que es la mascarilla tocha
	case 'w':
	{/*
		//incorporo disparos dependiendo del bonus hacia arriba
		if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus() == 2)){
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(0.0f, 6.0f);
			disparos.agregar(d);
		}

		break;
	*/
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(0, 6.0f);
		disparos.agregar(d);
		break;
	}
	case 'a':
	{/*
		//incorporo disparos dependiendo del bonus hacia izquierda
		if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus() == 2)) {
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(-6.0f, 0);
			disparos.agregar(d);
		}
		break;
		*/
		//Se crea un nuevo disparo y se dispara en la posición actual del jugador, para hacer la animación que la dispara él
		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(-6.0f, 0);
		disparos.agregar(d);
		break;

	}
	case 'd':
	{
		//incorporo disparos dependiendo del bonus hacia derecha
		/*if (disparos.getNumero() < MAX_DISPAROS && (jugador.GetNumBonus()==2)) {
			DisparoGel* d = Factoria::CrearDisparo(jugador);
			//Vector2D pos = jugador.getPos();
			//d->setPos(pos.x, pos.y);
			d->setVel(6.0f, 0);
			disparos.agregar(d);
		}
		break;
		*/

		DisparoGel* d = new DisparoGel();
		Vector2D pos = jugador.getPos();
		d->setPos(pos.x, pos.y);
		d->setVel(6.0f, 0);
		disparos.agregar(d);
		break;
	}
	}
	}
}

bool Juego::cargarNivel() {
	nivel++;
	jugador.setPos(0, 0);
	jugador.setNumBonus(0);//cada vez que empieza el juego, el jugador tiene 0 bonus
	jugador.setNumLlaves(0);//cada vez que empieza el nivel, el jugador tiene 0 llaves
	setVidas(1);//se establecen las vidas de nueva partida
	bajarescaleras = subirescaleras = false;
	primeravez = true;
	impacto = false;//inicializo otra vez el impacto
	enemigos.destruirContenido();
	disparos.destruirContenido();
	bonuses.destruirContenido();
	bloques.destruirContenido();
	escaleras.destruirContenido();
	if (nivel == 1) {
		//aqui se ponen con agregar lo que quereis que haya en dicho nivel
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(-2.0f, 1.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-5.0f, 4.0f, 7.0f, 8.0f));*/
		enemigos.agregar(new CepaIndia(2.0f, -4.0f, 10.0f, -1.0f, 0.0f));
		enemigos.agregar(new CepaIndia(2.0f, 10.0f, 8.0f, -1.0f, 0.0f));
		plataformas.agregar(new Plataforma(2.0f, 4.0f, 10.0f, 4.0f));
		plataformas.agregar(new Plataforma(-4.0f, 6.0f, 0.0f, 6.0f));
		plataformas.agregar(new Plataforma(-10.0f, 9.0f, -6.0f, 9.0f));
		escaleras.agregar(new Escalera(-9.0f, -7.0f, 9.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 13.0f, -6.0f, 13.0f));
		plataformas.agregar(new Plataforma(-1.0f, 16.0f, 6.0f, 16.0f));
		bonuses.agregar(new MascarillaTocha(2.0f, -3.0f, 8.0f));
		llaves.agregar(new Llave(1.0f, 2.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 4.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 7.0f, 2.0f));

	}
	if (nivel == 2) {
		//aqui se ponen con agregar lo que querais que haya en dicho nivel
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(4.0f, 8.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-4.0f, 2.0f, 5.0f, 4.0f));
		enemigos.agregar(new CepaBrasileña(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));*/
		llaves.agregar(new Llave(1.0f, 2.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 4.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 7.0f, 2.0f));
	}
	if (nivel == 3) {
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(-2.0f, 1.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-5.0f, 4.0f, 7.0f, 8.0f));*/
		llaves.agregar(new Llave(1.0f, 2.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 4.0f, 2.0f));
		llaves.agregar(new Llave(1.0f, 7.0f, 2.0f));
		//nivel del boss
	}
	if (nivel <= 3) {
		return true;
	}
	return false;
}
Juego::~Juego()
{
	enemigos.destruirContenido();
	disparos.destruirContenido();
	bonuses.destruirContenido();//destruyo correctamente los bonus
}