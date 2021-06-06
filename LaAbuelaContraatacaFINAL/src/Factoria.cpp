#include "Factoria.h"
Factoria::Factoria() {
	
}
void Factoria::CogerQuirurgica(Jugador& j) {
	j.setNumBonus(j.GetNumBonus() + 1);
	if (j.GetNumBonus() == 1) {
		j.setAltura(j.getAltura() * 2);
		//j.crecer();
	}
	if (j.GetNumBonus() > 2) {
		j.setNumBonus(2);
	}
}

void Factoria::CogerMascarillaTocha(Jugador& j) {
	if (j.GetNumBonus() == 0) {
		j.setAltura(j.getAltura() * 2);
	}
	j.setNumBonus(2);
}
/*DisparoGel* Factoria::CrearDisparo(Jugador j) {
	DisparoGel* d = 0;
	if (j.GetNumBonus() == 2) {
	d = new DisparoGel;
	}
	Vector2D pos = j.getPos();
	d->setPos(pos.x, pos.y);
	return d;
}*/
void Factoria::CogerAstrazeneca(Jugador& j) {
	j.setImpulso(25.0f);
}
void Factoria::CogerPfizer(Jugador& j) {
	//invencible y mas rapido
	j.setCoefVelx(j.getVelRapida()); // modifico el coeficiente de la velocidad para hacerla más rapida
}
void Factoria::CogerJanssen(Jugador& j) {
	int azar = rand() % 4;
	switch (azar) {
	case 0:
		j.setCoefVelx(j.getVelLenta()); //mas lento
		break;
	case 1:
		j.setCoefVelx(j.getVelRapida()); //mas rapido
		break;
	case 2:
		j.setCoefVelx(j.getVelRapida()); //mas rapido
		break;
	case 3:
		//no pasa na
		break;
	}
}
void Factoria::CogerSputnik(Jugador& j, ListaEnemigos& e) {
	//mata a enemigos estrellita mario bros
}
/*void Factoria::ModificarSalto(Jugador j, Bonus b) {
	
}
*/
Factoria::~Factoria() {

}
/*void Factoria::accionbonus(Jugador j, Bonus b) {//accion que recoge lo que pasa con el jugador al interactuar con los diferentes bonus
	static time_t horaInicioBonus = time(NULL);
	const int SEGUNDOS = 10; //Tiempo que dura el bonus
	time_t horaActualBonus = time(NULL);
	for (int i = numero - 1; i >= 0; i--) {
		int tipo = lista[i]->getTipo();
		if (tipo == ASTRAZENECA && Interaccion::colision(b, j)) {//salto el doble
			j.salto(38.0f);
		}
		if (tipo == JANSSEN && Interaccion::colision(b, j)) {//25% mitad velocidad , 25% nada y 50% doble velocidad
			int azar = rand() / (float)RAND_MAX;
			if (azar <= 25) {
				j.setVelx(j.getVel().x / 2);
			}
			if (azar >= 50) {
				j.setVelx(j.getVel().x * 2);
			}
		}
		if (tipo == SPUTNIK && Interaccion::colision(b, j)) {//eres invencible y pegas con un baston

		}
		if (tipo == PFIZER && Interaccion::colision(b, j)) {//aumenta el doble de la velocidad del jugador y eres invencible x tiempo
			j.setVelx(j.getVel().x * 2);
		}
	}
}
*/