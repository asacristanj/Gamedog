#include "Coordinador.h"
Coordinador::Coordinador() {
	estado=INICIO;
}
Coordinador::~Coordinador() {

}

void Coordinador::teclaEspecial(unsigned char key) {
	if (estado == JUEGO) {
		juego.teclaEspecial(key);
	}
}
void Coordinador::tecla(unsigned char key) {
	if (estado == INICIO) {
		if (key == 'e') {
			juego.inicializa();
			estado = JUEGO;
		}
		if (key == 's') {
			exit(0);
		}
	}
	else if (estado == JUEGO) {
		juego.tecla(key);
	}
	else if (estado == GAMEOVER) {
		if (key == 'c') {
			estado = INICIO;
		}
	}
	else if (estado == FIN) {
		if (key == 'c') {
			estado = INICIO;
		}
	}
}
void Coordinador::mueve() {
	if (estado == JUEGO) {
		juego.mueve();
	}
}
void Coordinador::dibuja() {
	if (estado == INICIO) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		/*ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("LA ABUELA CONTRATACA", -5, 8);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 12);
		ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -5, 7);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -5, 6);
		ETSIDI::printxy("MACCABI DE LEVANTAR CHICO", 2, 1);*/
	}
	else if (estado == JUEGO) {
		juego.dibuja();
	}
	else if (estado == GAMEOVER) {
		juego.dibuja();
		/*ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		ETSIDI::printxy("GAME OVER: chupaste", -5, 10);
		ETSIDI::printxy("Pulsa -C- para continuar", -5, 5);*/
	}
	else if (estado == FIN) {
		juego.dibuja();
		//ETSIDI::setFont("fuentes/Bitwise.ttf", 16);
		//ETSIDI::printxy("Chico estas mas dentro", -5, 10);
		//ETSIDI::printxy("Pulsa -C- para continuar", -5, 10);
	}
}