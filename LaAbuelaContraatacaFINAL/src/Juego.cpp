#include "Juego.h"
#include "freeglut.h"
#include <math.h>
#include "ETSIDI.h"
#include <time.h>
using namespace std;

void Juego::inicializa()
{
	x_ojo = 0;
	y_ojo = 7.5;
	z_ojo = 30;
	setRecordSuperado(false);
	setRecord(getRecordFile()); // obtengo el record actual
	//setRecordFile(10);
	jugador.setPuntuacion(0);
	nivel = 0;//establezco el nivel al principio de cada inicializa
	cargarNivel();//cargo el nivel corrspondiente donde se inicializa todo
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
	moverOjo();
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

				if (enemigos[i]->getTipo() != MURCIELAGOBOSS) // EL BOSS SOLO PIERDE VIDA AL SER PISADO
				{
					enemigos[i]->setVidas(-1); // menos 1 vida
					// incremento de puntuaciones 
					switch (enemigos[i]->getTipo())
					{
					case CEPAINDIA:
						jugador.setPuntuacion(20);
						break;
					case CEPABRASILEÑA:
						jugador.setPuntuacion(25);
						break;
					case CEPACHINA:
						jugador.setPuntuacion(15);
						break;
					case CEPABRITANICA:
						jugador.setPuntuacion(20);
						break;
					case MURCIELAGOPEQUEÑO:
						jugador.setPuntuacion(35);
						break;
					default: // MURCIELAGO BOSS no puntua al ser disparado
						break;
					}
				}

				if (enemigos[i]->getVidas() < 1) // si no le quedan vidas muere
					enemigos.eliminar(enemigos[i]);
			}
		}
	}
	bloques.rebote(jugador);
	bloques.CrearBonus(bonuses, jugador);
	setChances(jugador.getNumBonus());//refrescamos las chances que tiene el jugador continuamente
	setllaveJug(jugador.getNumLlaves());//refrescamos las llaves que tiene el jugador
		// puntuacion
	setPuntuacionJugador(jugador.getPuntuacion());
	if (getRecord() < jugador.getPuntuacion()) // si se supera el record anterior
	{
		setRecordSuperado(true); // señal para el coordinador
		setRecord(jugador.getPuntuacion()); // se actualiza el record
		setRecordFile(getRecord());
	}
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
			jugador.setVely(0.0f);
			jugador.setAcely(-30.0f);
			subirescaleras = false;
			break;
		}
		if (plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario) || jugador.suelo())
			jugador.salto();
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

void Juego::setRecordFile(int r)
{
	ofstream fichero("files/Record_puntuacion.txt", ios::out);
	if (fichero.fail())
	{
		cout << endl << "No se pudo abrir el archivo." << endl;
		exit(1);
	}
	else
	{
		fichero << r; // sobreescribo el archivo con el record actual
	}
	fichero.close();
}

int Juego::getRecordFile()
{
	int record;
	string lectura;
	ifstream fichero("files/Record_puntuacion.txt", ios::in);
	if (fichero.fail())
	{
		cout << endl << "No se pudo abrir el archivo." << endl;
		exit(1);
	}
	else
	{
		while (!fichero.eof())
		{
			getline(fichero, lectura);
			cout << endl << lectura;
		}
		record = stoi(lectura); // stoi() convierte el string en un int
		cout << endl << "Record guardado: " << record << endl;
	}
	fichero.close();
	return record;
}

void Juego::tecla(unsigned char key)
{
	switch (key)
	{
	case ' ':
	{
		if ((plataformas.colisionEncima(jugador) || Interaccion::colisionSuelo(jugador, escenario) || jugador.suelo()))
		{
			//cout << endl << "salta"<<jugador.getPos().y;
			jugador.salto();
		}
		break;
	}
	//solo existen disparos cuando el jugador tiene 2 bonus que es la mascarilla tocha
	case 'w':
	{
		if (jugador.getNumBonus() == 2) {
			DisparoGel* d = new DisparoGel();
			Vector2D pos = jugador.getPos();
			d->setPos(pos.x, pos.y);
			d->setVel(0, 6.0f);
			disparos.agregar(d);
		}
		break;
	}
	case 'a':
	{
		//Se crea un nuevo disparo y se dispara en la posición actual del jugador, para hacer la animación que la dispara él
		if (jugador.getNumBonus() == 2) {
			DisparoGel* d = new DisparoGel();
			Vector2D pos = jugador.getPos();
			d->setPos(pos.x, pos.y);
			d->setVel(-6.0f, 0);
			disparos.agregar(d);
		}
		break;

	}
	case 'd':
	{
		if (jugador.getNumBonus() == 2) {
			DisparoGel* d = new DisparoGel();
			Vector2D pos = jugador.getPos();
			d->setPos(pos.x, pos.y);
			d->setVel(6.0f, 0);
			disparos.agregar(d);
		}
		break;
	}
	}
}

bool Juego::cargarNivel() {
	nivel++;
	jugador.setPuntuacion(0);
	setVidas(1);//se establecen las vidas de nueva partida
	bajarescaleras = subirescaleras = false;
	jugador.setDañoCaida(false);
	primeravez = true;
	impacto = false;//inicializo otra vez el impacto
	enemigos.destruirContenido();
	disparos.destruirContenido();
	bonuses.destruirContenido();
	bloques.destruirContenido();
	escaleras.destruirContenido();
	plataformas.destruirContenido();
	llaves.destruirContenido();
	if (nivel == 1) 
	{
		jugador.setPos(0, 0);
		jugador.setNumBonus(0);//cada vez que empieza el juego, el jugador tiene 0 bonus
		jugador.setNumLlaves(0);//cada vez que empieza el nivel, el jugador tiene 0 llaves
		//aqui se ponen con agregar lo que quereis que haya en dicho nivel
		//llaves.agregar(new Llave(1.0f, 5.0f, 17.0f));
		//llaves.agregar(new Llave(1.0f, 4.0f, 17.0f));
		//llaves.agregar(new Llave(1.0f, 3.0f, 17.0f));
		bonuses.agregar(new Astrazeneca(1.0f, 2.0f, 6.0f, 0.0f, 0.0f));
		plataformas.agregar(new Plataforma(2.0f, 4.0f, 10.0f, 4.0f));
		enemigos.agregar(new CepaBritanica(2.0f, 5.0f, 5.0f, -6.0f, 0.0f)); //
		bloques.agregar(new BloqueSorpresa(1.0f, 5.0f, 7.0f));
		plataformas.agregar(new Plataforma(-4.0f, 6.0f, 0.0f, 6.0f));
		plataformas.agregar(new Plataforma(-10.0f, 9.0f, -6.0f, 9.0f));
		enemigos.agregar(new CepaIndia(2.0f, -8.0f, 10.0f, -5.0f, 0.0f));
		escaleras.agregar(new Escalera(-9.0f, -7.0f, 9.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 13.0f, -6.0f, 13.0f));
		bonuses.agregar(new Quirurgica(2.0f, -8.0f, 15.0f));
		//bloques.agregar(new BloqueSorpresa(1.0f, -1.0f, 15.0f));
		plataformas.agregar(new Plataforma(-1.0f, 15.0f, 10.0f, 15.0f));
		enemigos.agregar(new CepaIndia(2.0f, 2.0f, 7.0f, 2.0f, 0.0f));
		enemigos.agregar(new CepaBritanica(2.0f, 7.0f, 15.0f, 2.0f, 0.0f)); //
		//bonuses.agregar(new Astrazeneca(1.0f, 2.0f, 18.0f, 0.0f, 0.0f));
		//bonuses.agregar(new MascarillaTocha(2.0f, -3.0f, 8.0f));
		llaves.agregar(new Llave(1.0f, 6.0f, 17.0f));
		escaleras.agregar(new Escalera(8.0f, 10.0f, 15.0f, 4.0f, 0.0f));
		//plataformas.agregar(new Plataforma(6.0f, 17.0f, 10.0f, 17.0f));
		plataformas.agregar(new Plataforma(6.0f, 19.0f, 10.0f, 19.0f));
		plataformas.agregar(new Plataforma(-4.0f, 21.0f, 2.0f, 21.0f));
		escaleras.agregar(new Escalera(-3.0f, -1.0f, 21.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 25.0f, 10.0f, 25.0f));
		enemigos.agregar(new CepaIndia(2.0f, 6.0f, 26.0f, -3.0f, 0.0f));
		enemigos.agregar(new CepaIndia(2.0f, -6.0f, 26.0f, -3.0f, 0.0f));
		enemigos.agregar(new CepaBrasileña(1.5f, -5.0f, 26.0f, -6.0f, 0.0f));
		enemigos.agregar(new CepaBrasileña(1.5f, 5.0f, 27.0f, 6.0f, 0.0f));
		enemigos.agregar(new CepaBrasileña(2.0f, 0.0f, 27.0f, 6.0f, 0.0f));
		escaleras.agregar(new Escalera(-8.0f, -6.0f, 25.0f, 4.0f, 0.0f));
		//plataformas y rama llave derecha
		escaleras.agregar(new Escalera(6.0f, 8.0f, 25.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(3.0f, 29.0f, 10.0f, 29.0f));
		bonuses.agregar(new Janssen(1.0f, -6.0f, 30.0f));
		escaleras.agregar(new Escalera(7.0f, 9.0f, 29.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 29.0f, -3.0f, 29.0f));
		bonuses.agregar(new Pfizer(1.0f, 6.0f, 30.0f));
		plataformas.agregar(new Plataforma(7.0f, 33.0f, 10.0f, 33.0f));
		llaves.agregar(new Llave(1.0f, 9.0f, 35.0f));
		//plataforma final de nivel
		escaleras.agregar(new Escalera(-8.0f, -6.0f, 29.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 33.0f, 2.0f, 33.0f));
		//enemigos.agregar(new CepaBritanica(2.0f, -7.0f, 34.0f, 2.0f, 0.0f));
		bloques.agregar(new BloqueSorpresa(1.0f, -8.0f, 36.0f));
		//parkour
		plataformas.agregar(new Plataforma(0.0f, 36.0f, 3.0f, 36.0f));
		plataformas.agregar(new Plataforma(5.0f, 39.0f, 10.0f, 39.0f));
		plataformas.agregar(new Plataforma(-6.0f, 42.0f, 2.0f, 42.0f));
		enemigos.agregar(new CepaIndia(2.0f, 0.0f, 43.0f, 2.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 45.0f, -8.0f, 45.0f));
		plataformas.agregar(new Plataforma(-5.0f, 49.0f, 10.0f, 49.0f));
		//enemigos.agregar(new CepaBritanica(2.0f, 4.0f, 50.0f, -1.0f, 0.0f));
		escaleras.agregar(new Escalera(5.0f, 7.0f, 49.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 53.0f, 10.0f, 53.0f));
		enemigos.agregar(new CepaBrasileña(2.0f, -5.0f, 54.0f, 6.0f, 0.0f));
		enemigos.agregar(new CepaIndia(2.0f, -5.0f, 54.0f, -3.0f, 0.0f));
		bonuses.agregar(new Quirurgica(1.0f, 0.0f, 54.0f));
		plataformas.agregar(new Plataforma(-8.0f, 57.0f, -6.0f, 57.0f));
		plataformas.agregar(new Plataforma(6.0f, 57.0f, 8.0f, 57.0f));
		plataformas.agregar(new Plataforma(-10.0f, 61.0f, -9.0f, 61.0f));
		plataformas.agregar(new Plataforma(9.0f, 61.0f, 10.0f, 61.0f));
		plataformas.agregar(new Plataforma(-8.0f, 65.0f, -6.0f, 65.0f));
		plataformas.agregar(new Plataforma(6.0f, 65.0f, 8.0f, 65.0f));
		enemigos.agregar(new MurcielagoPequeño(1.5f, -1.0f, 67.5f, -3.0f, 3.0f));
		enemigos.agregar(new MurcielagoPequeño(1.5f, 1.0f, 67.5f, 3.0f, 3.0f));
		plataformas.agregar(new Plataforma(-5.0f, 70.0f, 5.0f, 70.0f));
		enemigos.agregar(new CepaIndia(2.0f, 2.0f, 71.0f, 3.0f, 0.0f));
		enemigos.agregar(new CepaBritanica(2.0f, 0.0f, 71.0f, -3.0f, 0.0f));
		enemigos.agregar(new CepaIndia(2.0f, 4.0f, 71.0f, -3.0f, 0.0f));
		llaves.agregar(new Llave(1.0f, 0.0f, 75.0f, 0.0f, 0.0f));
	}
	if (nivel == 2) {
		jugador.setPos(0, 0);
		jugador.setNumBonus(0);//cada vez que empieza el juego, el jugador tiene 0 bonus
		jugador.setNumLlaves(0);//cada vez que empieza el nivel, el jugador tiene 0 llaves
		//aqui se ponen con agregar lo que querais que haya en dicho nivel
		/*plataformas.agregar(new Plataforma(-5.0f, 4.0f, 5.0f, 4.0f));
		plataformas.agregar(new Plataforma(4.0f, 8.0f, 2.0f, 1.0f));
		plataformas.agregar(new Plataforma(-4.0f, 2.0f, 5.0f, 4.0f));
		enemigos.agregar(new CepaBrasileña(1.0f, 2.0f, 5.0f, -2.0f, 0.0f));*/
		plataformas.agregar(new Plataforma(-2.0f, 3.0f, 0.0f, 3.0f));
		plataformas.agregar(new Plataforma(3.0f, 6.0f, 10.0f, 6.0f));
		bloques.agregar(new BloqueSorpresa(1.0f, 8.0f, 9.0f));
		//enemigos.agregar(new CepaIndia(2.0f, 6.0f, 7.0f, 2.0f, 0.0f));
		//enemigos.agregar(new CepaBritanica(2.0f, 6.0f, 7.0f, -3.0f, 0.0f));
		plataformas.agregar(new Plataforma(-5.0f, 9.0f, 0.0f, 9.0f));
		escaleras.agregar(new Escalera(-5.0f, -3.0f, 9.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 13.0f, -3.0f, 13.0f));
		//enemigos.agregar(new CepaBrasileña(2.0f, -7.0f, 15.0f, -2.0f, 0.0f));
		//enemigos.agregar(new CepaIndia(2.0f, -7.0f, 15.0f, 2.0f, 0.0f));
		escaleras.agregar(new Escalera(-10.0f, -8.0f, 13.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-10.0f, 17.0f, -8.0f, 17.0f));
		llaves.agregar(new Llave(1.0f, -9.0f, 19.0f));
		plataformas.agregar(new Plataforma(1.0f, 16.0f, 3.0f, 16.0f));
		plataformas.agregar(new Plataforma(7.0f, 19.0f, 10.0f, 19.0f));
		plataformas.agregar(new Plataforma(2.0f, 23.0f, 3.0f, 23.0f));
		plataformas.agregar(new Plataforma(-10.0f, 26.0f, 0.0f, 26.0f));
		enemigos.agregar(new CepaBritanica(2.0f, -8.0f, 27.0f, 4.0f));
		bloques.agregar(new BloqueSorpresa(1.0f, -3.0f, 29.0f));
		plataformas.agregar(new Plataforma(-8.0f, 30.0f, -7.0f, 30.0f));
		plataformas.agregar(new Plataforma(-10.0f, 34.0f, -9.0f, 34.0f));
		plataformas.agregar(new Plataforma(-7.0f, 37.0f, -4.0f, 37.0f));
		llaves.agregar(new Llave(1.0f, -5.0f, 39.0f));
		plataformas.agregar(new Plataforma(3.0f, 29.0f, 6.0f, 29.0f));
		plataformas.agregar(new Plataforma(8.0f, 33.0f, 10.0f, 33.0f));
		escaleras.agregar(new Escalera(8.0f, 10.0f, 33.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(1.0f, 37.0f, 10.0f, 37.0f));
		enemigos.agregar(new CepaIndia(2.0f, 8.0f, 38.0f, -2.0f));
		enemigos.agregar(new CepaBrasileña(2.0f, 7.0f, 38.0f, 2.0f));
		bloques.agregar(new BloqueSorpresa(1.0f, 7.0f, 40.0f));
		plataformas.agregar(new Plataforma(-4.0f, 40.0f, -1.0f, 40.0f));
		escaleras.agregar(new Escalera(-4.0f, -2.0f, 40.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(-7.0f, 44.0f, 6.0f, 44.0f));
		enemigos.agregar(new CepaIndia(2.0f, -5.0f, 45.0f, 2.0f));
		enemigos.agregar(new CepaBritanica(2.0f, -6.0f, 45.0f, -3.0f));
		plataformas.agregar(new Plataforma(8.0f, 47.0f, 10.0f, 47.0f));
		escaleras.agregar(new Escalera(8.0f, 10.0f, 47.0f, 4.0f, 0.0f));
		plataformas.agregar(new Plataforma(2.0f, 51.0f, 10.0f, 51.0f));
		enemigos.agregar(new CepaIndia(2.0f, 5.0f, 53.0f, 3.0f));
		plataformas.agregar(new Plataforma(-4.0f, 54.0f, -1.0f, 54.0f));
		plataformas.agregar(new Plataforma(-10.0f, 57.0f, -7.0f, 57.0f));
		enemigos.agregar(new CepaBrasileña(2.0f, -9.0f, 58.0f, 2.0f));
		plataformas.agregar(new Plataforma(-5.0f, 61.0f, 10.0f, 61.0f));
		enemigos.agregar(new CepaBritanica(2.0f, 6.0f, 63.0f, 2.0f));
		enemigos.agregar(new CepaIndia(2.0f, 6.0f, 63.0f, -5.0f));
		plataformas.agregar(new Plataforma(8.0f, 67.0f, 10.0f, 67.0f));
		llaves.agregar(new Llave(1.0f, 9.0f, 69.0f));
	}
	if (nivel == 3) {
		jugador.setPos(0, 0);
		jugador.setNumBonus(0);//cada vez que empieza el juego, el jugador tiene 0 bonus
		jugador.setNumLlaves(0);//cada vez que empieza el nivel, el jugador tiene 0 llaves
		//nivel del boss
		escaleras.agregar(new Escalera(-1.0f, 1.0f, 0.0f, 4.0f, 2.0f));
		plataformas.agregar(new Plataforma(-10.0f, 4.0f, 10.0f, 4.0f));
		plataformas.agregar(new Plataforma(-6.0f, 8.0f, 6.0f, 8.0f));
		plataformas.agregar(new Plataforma(-10.0f, 12.0f, -8.0f, 12.0f));
		plataformas.agregar(new Plataforma(8.0f, 12.0f, 10.0f, 12.0f));
		plataformas.agregar(new Plataforma(-4.0f, 15.0f, 4.0f, 15.0f));
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
	plataformas.destruirContenido();
	escaleras.destruirContenido();
	bloques.destruirContenido();
	llaves.destruirContenido();
}