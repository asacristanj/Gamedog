#include "Juego.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
	nivel = 0;//establezco el nivel al principio de cada inicializa
	jugador.setNumBonus(0);//cada vez que empieza el juego, el jugador tiene 0 bonus
	setVidas(1);//se establecen las vidas de nueva partida
	cargarNivel();//cargo el nivel corrspondiente
	impacto = false;//inicializo otra vez el impacto
	//a partir de aqui todo tendria que estar en el nivel correspondiente


	enemigos.destruirContenido();//limpio tras game over
	disparos.destruirContenido();//limpio tras game over
	jugador.setPos(0.0f, 0.0f);//origen del jugador
	plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
	escaleras.agregar(new Escalera(3.0f,5.0f,0.0f,4.0f,2.0f));
	//enemigos.agregar(new Enemigo(1.5f, 0.0f, 10.0f, -1.0f, 0.0f));
	//Agregamos un bonus inicial
	//bonuses.agregar(new Astrazeneca(1.0f, -5.0f, 8));
	//bonuses.agregar(new Janssen(1.5f,-4.0f,5));
	bonuses.agregar(new MascarillaTocha(2.0f, 0.0f, 9));
	//bonuses.agregar(new Pfizer(0.5f,3.0f,6,0,0));
	bonuses.agregar(new Quirurgica(1.0f, 4.0f, 10.0f, 0.0f, 0.0f));
	//bonuses.agregar(new Quirurgica(1.0f, 2.0f, 10.0f, 0.0f, 0.0f));
	//bonuses.agregar(new Sputnik(0.5f,8.5f,6));
	//enemigos.agregar(new MurcielagoPequeño());
	//enemigos.agregar(new MurcielagoPequeño(1.0f, -2.0f, 10.0f, 4.0f, 4.0f));
	//enemigos.agregar(new MurcielagoBoss(1.0f, 0.0f, 10.0f, 4.0f, 4.0f));
	//enemigos.agregar(new CepaBrasileña(1.0f, -2.0f, 5.0f, 2.0f, 0.0f));
	//enemigos.agregar(new CepaBrasileña(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(1.0f, -2.0f, 5.0f, 2.0f, 0.0f));
	//enemigos.agregar(new CepaBritanica(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));
	//enemigos.agregar(new CepaChina(1.0f, 0.0f, 15.0f, -8.0f, 0.0f));
	//enemigos.agregar(new CepaIndia(1.5f, -4.0f, 10.0f, -1.0f, 0.0f));
	//enemigos.agregar(new CepaIndia(2.0f, -4.0f, 10.0f, -1.0f, 0.0f));
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

	
	escaleras.dibuja();
	jugador.dibuja();
	enemigos.dibuja();
	disparos.dibuja();
	bloques.dibuja();
	bonuses.dibuja();
	plataformas.dibuja();
	escenario.dibuja();
}

void Juego::mueve()
{
	jugador.volverSalto();
	jugador.volverVelocidadPfizer();
	jugador.volverVelocidadJanssen();
	jugador.mueve(0.025f);
	bonuses.mueve(0.025f);
	enemigos.mueve(0.025f);
	disparos.mueve(0.025f);
	enemigos.rebote(escenario);
	if((escaleras.subirEscalera(jugador)==false)&&(escaleras.bajarEscalera(jugador)==false))
		plataformas.rebote(jugador);
	enemigos.rebote(jugador);
	enemigos.reboteBoss(escenario, jugador);
	disparos.colision(escenario);
	bonuses.rebote(escenario);
	bonuses.rebote(jugador);
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
			if (Interaccion::colision(*disparos[i], *enemigos[i]))
			{
				if (enemigos[i]->getTipo() == MURCIELAGOBOSS)
				{
					enemigos[i]->setDisparoRecibido(true);
					if (enemigos[i]->getVidas() < 0) // si no le quedan vidas muere
					{
						disparos.eliminar(disparos[i]);
						enemigos.eliminar(enemigos[i]);
					}
				}
				else
				{
					disparos.eliminar(disparos[i]);
					enemigos.eliminar(enemigos[i]);
				}
			}
		}
	}
	bloques.rebote(jugador);
	bloques.CrearBonus(bonuses, jugador);
	setChances(jugador.GetNumBonus());//refrescamos las chances que tiene el jugador continuamente
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
		   if (escaleras.subirEscalera(jugador)) {
			   jugador.setVely(5.0f);
			   break;
		   }
		   if (plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario) || jugador.suelo()) {
					jugador.salto();
		   }
		   break;
	   case GLUT_KEY_DOWN:
	   {
		   if (escaleras.bajarEscalera(jugador))
			   jugador.setVely(-(jugador.getVelNormal() * jugador.getCoefVelx()));
		   break;
	   }
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
				jugador.setVely(0.0f);
			if (plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario)||jugador.suelo())
				jugador.salto();
			break;
		}
		case GLUT_KEY_DOWN:
		{
			if (escaleras.bajarEscalera(jugador))
				jugador.setVely(0.0f);
			break;
		}
	}
}

void Juego::tecla(unsigned char key)
{
	if (jugador.GetNumBonus() == 2) {//solo existen disparos cuando el jugador tiene 2 bonus que es la mascarilla tocha
		switch (key)
		{
		case 'm':
		{
			enemigos.agregar(new CepaBritanica(1.5f, -2.0f, 10.0f, -5.0f, 0.0f));
			break;
		}
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
	enemigos.destruirContenido();
	disparos.destruirContenido();
	if (nivel == 1) {
		//aqui se ponen con agregar lo que quereis que haya en dicho nivel
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(-2.0f, 1.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-5.0f, 4.0f, 7.0f, 8.0f));*/
	}
	if (nivel == 2) {
		//aqui se ponen con agregar lo que querais que haya en dicho nivel
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(4.0f, 8.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-4.0f, 2.0f, 5.0f, 4.0f));
		enemigos.agregar(new CepaBrasileña(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));*/
	}
	if (nivel == 3) {
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(-2.0f, 1.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-5.0f, 4.0f, 7.0f, 8.0f));*/
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