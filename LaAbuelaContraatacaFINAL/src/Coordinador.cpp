#include "Coordinador.h"
Coordinador::Coordinador() {
	estado = INICIO;
	contHist = 1;
	contInstr = 1;
}
Coordinador::~Coordinador() {

}

void Coordinador::teclaEspecial(unsigned char key) {
	if (estado == HISTORIA)
	{

		if (key == GLUT_KEY_RIGHT && contHist != 3)
		{
			contHist++;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == GLUT_KEY_LEFT && contHist != 1)
		{
			contHist--;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}

	}
	if (estado == INSTRUCCIONES)
	{

		if (key == GLUT_KEY_RIGHT && contInstr != 2)
		{
			contInstr++;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == GLUT_KEY_LEFT && contInstr != 1)
		{
			contInstr--;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}

	}

	if (estado == JUEGO) {
		juego.teclaEspecial(key);
		key = 'Q';			//LIMPIAR BUFFER TECLADO
	}
}
void Coordinador::tecla(unsigned char key) {
	if (estado == INICIO) {
		if (key == 'e' || key == 'E') {
			juego.inicializa();
			estado = JUEGO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == 's' || key == 'S') {
			exit(0);
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == 'i' || key == 'I') {
			estado = INSTRUCCIONES;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == 'h' || key == 'H') {
			estado = HISTORIA;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == JUEGO) {
		juego.tecla(key);
		if (key == 'p' || key == 'P') {
			estado = PAUSA;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == PAUSA) {
		if (key == 'c' || key == 'C') {
			estado = JUEGO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == 's' || key == 'S') {
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == GAMEOVER) {
		if (key == 'c' || key == 'C') {
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == FIN) {
		if (key == 'c' || key == 'C') {
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == INSTRUCCIONES) {
		if (contInstr == 2)
		{
			switch (key) {
			case 'E': //empezar el juego
			case 'e':
				juego.inicializa();
				estado = JUEGO;
				break;
			case 'I':  // volver al menú principal
			case 'i':
				contInstr = 1;
				estado = INICIO;
				break;
			}

			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == HISTORIA) {
		{
			if (key == 's' || key == 'S')
			{
				// saltar toda la historia e ir a la última página
				contHist = 3;
				key = 'Q';			//LIMPIAR BUFFER TECLADO
			}
			if (contHist == 3)
			{
				switch (key) {
				case 'E': //empezar el juego
				case 'e':
					juego.inicializa();
					estado = JUEGO;
					break;
				case 'I':  // volver al menú principal
				case 'i':
					contHist = 1;
					estado = INICIO;
					break;
				}

				key = 'Q';			//LIMPIAR BUFFER TECLADO
			}
		}

	}
}
void Coordinador::teclaEspecialUp(unsigned char key) {
	if (estado == JUEGO) {
		juego.teclaEspecialUp(key);
	}
}
void Coordinador::mueve() {
	if (estado == JUEGO) 
	{
		juego.mueve();
		//condicion de ganar
		if (juego.getLlaves() == 3) {
			if (!juego.cargarNivel()) {
				estado = FIN;
			}
		}
		if (juego.getChances() < 0) // no tengo bonus y muero
		{
			juego.setVidas(-1);// se descuenta una vida
			if(juego.getVidas() < 1) // si no quedan vidas
				estado = GAMEOVER;
		}
	}
}
void Coordinador::dibuja() {
	if (estado == INICIO) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 50);
		ETSIDI::printxy("LA ABUELA CONTRATACA", -12, 10);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		ETSIDI::printxy("PULSE LA TECLA -E- PARA EMPEZAR", -6, 4);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA SALIR", -6, 3);
		ETSIDI::printxy("PULSE LA TECLA -I- PARA INSTRUCCIONES", -6,5 );
		ETSIDI::printxy("PULSE LA TECLA -H- PARA HISTORIA", -6, 6);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		ETSIDI::printxy("CREATED BY: MACCABI DE LEVANTAR", 6, -2);
		glPopMatrix();
	}
	else if (estado == JUEGO) {
		juego.dibuja();
	}
	else if (estado == PAUSA) {
		//juego.dibuja();
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 70);
		ETSIDI::printxy("PAUSA", -5, 7);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		ETSIDI::printxy("PULSE LA TECLA -C- PARA CONTINUAR", -8, 1);
		ETSIDI::printxy("PULSE LA TECLA -S- PARA IR A LA PANTALLA INICIAL", -8, -1);
		glPopMatrix();
	}
	else if (estado == GAMEOVER) {
		//juego.dibuja();
		char puntuacion[10];
		char record[10];
		_itoa_s(juego.getPuntuacionJugador(), puntuacion, 10);
		_itoa_s(juego.getRecord(), record, 10);
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		if (juego.getRecordSuperado())
		{
			ETSIDI::setTextColor(0, 1, 0);
			ETSIDI::printxy("¡HAS SUPERADO EL RECORD! ", -5, 14);
		}
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::printxy("TU PUNTUACION HA SIDO: ", -14, 17);
		ETSIDI::printxy(puntuacion, -4, 17);
		ETSIDI::printxy("RECORD ACTUAL: ", 5, 17);
		ETSIDI::printxy(record, 12, 17);
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 60);
		ETSIDI::printxy("GAME OVER", -7, 9);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 25);
		ETSIDI::printxy("NEUMONIA BILATERAL", -7, 5);
		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		ETSIDI::printxy("PULSA -C- PARA IR AL MENU DE INICIO", -6, 0);
		glPopMatrix();
	}
	else if (estado == FIN) {
		//juego.dibuja();
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 50);
		ETSIDI::printxy("ELIMINASTE EL COVID", -10, 10);
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		ETSIDI::printxy("PULSA C PARA CONTINUAR AL MENU DE INICIO", -8, 1);
		glPopMatrix();
	}
	else if (estado == INSTRUCCIONES && contInstr == 1) {
		gluLookAt(2, 7.5, 37,  // posicion del ojo
			2.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();

		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 30);
		ETSIDI::printxy("ENEMIGOS:", -5, 16);
		ETSIDI::setTextColor(0, 0, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/enemigos.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3d(-14, -2, -0.1f);
		glTexCoord2d(1, 1); glVertex3d(-9, -2, -0.1f);
		glTexCoord2d(1, 0); glVertex3d(-9, 17, -0.1f);
		glTexCoord2d(0, 0); glVertex3d(-14, 17, -0.1f);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 12);
		ETSIDI::printxy("EN EL ULTIMO NIVEL ESTARA EL CULPABLE DEL COVID: EL GRAN MURCIELAGO.", -9, 13);
		ETSIDI::printxy("¡ACABA CON EL Y ACABARA TODO!", -9, 12);
		ETSIDI::printxy("CEPA BRITANICA: CUIDADO CON SUS EXPLOSIONES.", -9, 10);
		ETSIDI::printxy("CEPA INDIA: PARECE INOFENSIVA PERO MATA IGUAL.", -9, 7);
		ETSIDI::printxy("CEPA CHINA: SU HABILIDAD ESPECIAL ES HABER EMPEZADO TODO ESTO.", -9, 3);
		ETSIDI::printxy("CEPA BRASILEÑA: CUIDADO CON SUS SALTOS IMPREDECIBLES.", -9, -0.75f);

		/*
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 10);
		ETSIDI::printxy("PARA MOVER A LA ABUELA, USA LAS FLECHAS IZQUIERDA Y DERECHA", -13, 14);
		ETSIDI::printxy("PARA SALTAR USA LA BARRA ESPACIADORA. PARA SUBIR Y BAJAR ESCALERAS LAS FLECHAS ARRIBA Y ABAJO", -13, 13);
		ETSIDI::printxy("PARA DISPARAR CUANDO LA ABUELA PUEDA HACERLO USA LAS TECLAS A(IZQUIERDA) ,W(ARRIBA), D(DERECHA)", -13, 12);
		ETSIDI::printxy("CUANDO LA ABUELA CONSIGUE LAS 3 LLAVES, AVANZA HACIA EL SIGUIENTE NIVEL", -13, 11);
		ETSIDI::printxy("LAS DISTINTAS CEPAS TIENEN HABILIDADES DIFERENTES, ¡ESQUÍVALAS!", -13, 10);
		ETSIDI::printxy("CEPA INDIA: PARECE INOFENSIVA PERO MATA IGUAL", -11, 9);
		ETSIDI::printxy("CEPA BRITANICA: CUIDADO CON SUS EXPLOSIONES", -11, 8);
		ETSIDI::printxy("CEPA CHINA: SU HABILIDAD ESPECIAL ES HABER EMPEZADO TODO ESTO. SON DISPARADAS POR MURCIELAGOS", -11, 7);
		ETSIDI::printxy("CEPA BRASILEÑA: CUIDADO CON SUS SALTOS IMPREDECIBLES", -11, 6);
		ETSIDI::printxy("AYUDA A LA ABUELA CON LAS MASCARILLAS Y VACUNAS PARA TENER HABILIDADES DIFERENTES", -13, 5);
		ETSIDI::printxy("MASCARILLA QUIRURGICA: PROPORCIONA UNA OPORTUNIDAD EXTRA. SI COGES 2 ES IGUAL QUE UNA FFP2", -11, 4);
		ETSIDI::printxy("MASCARILLA FFP2: PROPORCIONA 2 OPORTUNIDADES EXTRAS Y LA CAPACIDAD DE DISPARAR", -11, 3);
		ETSIDI::printxy("ASTRAZENECA: AUMENTA EL SALTO DE LA ABUELA", -11, 2);
		ETSIDI::printxy("PFIZER: ABUELA BOLT. AUMENTA SU VELOCIDAD", -11, 1);
		ETSIDI::printxy("JANSSEN: PUEDE PASAR CUALQUIER COSA, MAS VELOCIDAD, MENOS VELOCIDAD O NADA", -11, 0);
		ETSIDI::printxy("EN EL ULTIMO NIVEL ESTARA EL CULPABLE DEL COVID: EL GRAN MURCIELAGO. ¡ACABA CON EL Y ACABARA TODO!", -13, -1);
		*/
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LAS INSTRUCCIONES", 3, -2);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", 3, -3);
		ETSIDI::printxy("PULSA I PARA VOLVER AL INICIO", 3, -4);
		glPopMatrix();
	}
	else if (estado == INSTRUCCIONES && contInstr == 2) {
		//INSTRUCCIONES BONUSES
		gluLookAt(2, 7.5, 37,  // posicion del ojo
			2.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 30);
		ETSIDI::printxy("BONUSES:", -5, 16);
		ETSIDI::setTextColor(0, 0, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/bonuses.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3d(-14, -2, -0.1f);
		glTexCoord2d(1, 1); glVertex3d(-9, -2, -0.1f);
		glTexCoord2d(1, 0); glVertex3d(-9, 17, -0.1f);
		glTexCoord2d(0, 0); glVertex3d(-14, 17, -0.1f);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 12);
		ETSIDI::printxy("MASCARILLA FFP2: PROPORCIONA 2 OPORTUNIDADES EXTRAS", -9, 13);
		ETSIDI::printxy(" Y LA CAPACIDAD DE DISPARAR", -9, 12);
		ETSIDI::printxy("MASCARILLA QUIRURGICA: PROPORCIONA UNA OPORTUNIDAD EXTRA.", -9, 10);
		ETSIDI::printxy("SI COGES 2 ES IGUAL QUE UNA FFP2", -9, 9);
		ETSIDI::printxy("PFIZER: ABUELA BOLT. AUMENTA SU VELOCIDAD.", -9, 7);
		ETSIDI::printxy("ASTRAZENECA: AUMENTA EL SALTO DE LA ABUELA.", -9, 3);
		ETSIDI::printxy("JANSSEN: PUEDE PASAR CUALQUIER COSA, MAS VELOCIDAD,", -9, -0.5f);
		ETSIDI::printxy("MENOS VELOCIDAD O NADA", -9, -1.5f);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LAS INSTRUCCIONES", 3, -2);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", 3, -3);
		ETSIDI::printxy("PULSA E PARA JUGAR, PULSA I PARA VOLVER AL INICIO", 3, -4);
		glPopMatrix();
	}
	else if (estado == HISTORIA && contHist == 1) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 40);
		ETSIDI::printxy("ESCENA 1", -4, 17);
		ETSIDI::setTextColor(0, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		//aqui se pondrian las cosas de la historia
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LA HISTORIA", -13, 1);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", -13, 0);
		ETSIDI::printxy("PARA OMITIR LA HISTORIA PULSE LA TECLA S", -13, -1);
		ETSIDI::printxy("PARA VOLVER AL MENÚ DE INICIO PULSE LA TECLA I", -13, -2);

		glPopMatrix();
	}
	else if (estado == HISTORIA && contHist == 2) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 40);
		ETSIDI::printxy("ESCENA 2", -4, 17);
		ETSIDI::setTextColor(0, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		//aqui se pondrian las cosas de la historia
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LA HISTORIA", -13, 1);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", -13, 0);
		ETSIDI::printxy("PARA OMITIR LA HISTORIA PULSE LA TECLA S", -13, -1);
		ETSIDI::printxy("PARA VOLVER AL MENÚ DE INICIO PULSE LA TECLA I", -13, -2);
	}
	else if (estado == HISTORIA && contHist == 3) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		ETSIDI::setTextColor(1, 0, 0);
		ETSIDI::setFont("fuentes/HUSKYSTA.TTF", 40);
		ETSIDI::printxy("ESCENA 3", -4, 17);
		ETSIDI::setTextColor(0, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		//aqui se pondrian las cosas de la historia
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LA HISTORIA", -13, 2);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", -13, 1);
		ETSIDI::printxy("PARA OMITIR LA HISTORIA PULSE LA TECLA S", -13, 0);
		ETSIDI::printxy("PARA VOLVER AL MENÚ DE INICIO PULSE LA TECLA I", -13, -1);
		ETSIDI::printxy("PARA JUGAR PULSE LA TECLA E", -13, -2);
	}
}