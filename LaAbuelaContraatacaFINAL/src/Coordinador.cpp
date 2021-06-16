#include "Coordinador.h"
Coordinador::Coordinador() {
	estado = INICIO;
	contHist = 1;
	contInstr = 1;
	playMusica("sonidos/musica_inicio.mp3", true);
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

		if (key == GLUT_KEY_RIGHT && contInstr != 3)
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
			juego.setReinicioJuego(true);
			playMusica("sonidos/musica_juego.mp3",true);
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
			playMusica("sonidos/musica_pausa.mp3",true);
			estado = PAUSA;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == PAUSA) {
		if (key == 'c' || key == 'C') {
			playMusica("sonidos/musica_juego.mp3",true);
			estado = JUEGO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
		if (key == 's' || key == 'S') {
			playMusica("sonidos/musica_inicio.mp3", true);
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == GAMEOVER) {
		if (key == 'c' || key == 'C') {
			playMusica("sonidos/musica_inicio.mp3", true);
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == FIN) {
		if (key == 'c' || key == 'C') {
			playMusica("sonidos/musica_inicio.mp3", true);
			estado = INICIO;
			key = 'Q';			//LIMPIAR BUFFER TECLADO
		}
	}
	else if (estado == INSTRUCCIONES) {
		if (contInstr == 3)
		{
			switch (key) {
			case 'E': //empezar el juego
			case 'e':
				playMusica("sonidos/musica_juego.mp3", true);
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
		if (contInstr >= 1)
		{
			switch (key) {
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
					playMusica("sonidos/musica_juego.mp3", true);
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
			if (contHist >=1)
			{
				switch (key) {
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
		//juego.setPuntuacionJugador(0);
		juego.mueve();
		//condicion de ganar
		if (juego.getLlaves() == 3) {
			if (!juego.cargarNivel()) {
				estado = FIN;
				playMusica("sonidos/ganaste.mp3");
			}
		}
		if (juego.getChances() < 0) // no tengo bonus y muero
		{
			juego.setVidas(-1);// se descuenta una vida
			if (juego.getVidas() < 1) // si no quedan vidas
				estado = GAMEOVER;

			playMusica("sonidos/chupaste.mp3");
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
		ETSIDI::printxy("LA ABUELA CONTRAATACA", -12, 10);
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
		ETSIDI::printxy("SE ACABO EL CONTRAATAQUE", -7, 4);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 25);
		ETSIDI::setTextColor(1, 0, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 16);
		ETSIDI::printxy("PULSA -C- PARA IR AL MENU DE INICIO", -6, 0);
		glPopMatrix();
	}
	else if (estado == FIN) {
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
		ETSIDI::printxy("REGLAS BASICAS:", -5, 16);
		ETSIDI::setTextColor(0, 1, 0);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 12);
		ETSIDI::printxy("EL OBJETIVO ES ELMINAR EL TEMIBLE MURCIELAGO QUE TE ESPERA EN", -14, 13);
		ETSIDI::printxy("EL EL ULTIMO NIVEL.", -14, 12);
		ETSIDI::printxy("PARA LLEGAR HASTA EL, TENDRÁS QUE SUPERAR TODOS LOS NIVELES ANTERIORES", -14, 10);
		ETSIDI::printxy("EN CADA UNO DE ESTOS, ENCONTRARAS TRES LLAVES QUE TIENES QUE COGER.", -14, 9);
		ETSIDI::printxy("EL MOVIMIENTO DE IZQUIERDA A DERECHA SE REALIZA CON LAS FLECHAS,Y EL DE SALTAR", -14, 7);
		ETSIDI::printxy("CON EL ESPACIO. PUEDES SUBIR Y BAJAR ESCALERAS CON LAS FLCEHAS ARRIBA Y ABAJO", -14, 6);
		ETSIDI::printxy("PUEDES ELIMINAR LAS CEPAS PISANDOLAS O DISPARANDO GEL HISROALCOHOLICO.", -14, 3);
		ETSIDI::printxy("PUEDES PAUSAR EL JUEGO EN CUALQUIER MOMENTO, PULSANDO LA P.", -14, -1);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LAS INSTRUCCIONES", 3, -2);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", 3, -3);
		ETSIDI::printxy("PULSA I PARA VOLVER AL INICIO", 3, -4);
		glPopMatrix();
	}
	else if (estado == INSTRUCCIONES && contInstr == 2) {
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
		ETSIDI::printxy("LOS MURCIELAGOS TE LANZARÁN CEPAS CHINAS. ¡TEN CUIDADO!", -9, 13);
		ETSIDI::printxy("EL ENEMIGO FINAL SERA UN MURCIALAGO GIGANTE.", -9, 12);
		ETSIDI::printxy("CEPA BRITANICA: NO TE ACERQUES MUCHO A ELLAS, PODRIAN EXPLOTAR.", -9, 10);
		ETSIDI::printxy("CEPA INDIA: SE MUEVEN DE LADO A LADO SOBRE LAS PLATAFORMAS.", -9, 7);
		ETSIDI::printxy("CEPA CHINA: SON LANZADAS POR MURCIELAGOS, INTENTA ESQUIVARLAS..", -9, 3);
		ETSIDI::printxy("CEPA BRASILEÑA: CUIDADO CON SUS REBOTES IMPREDECIBLES.", -9, -1);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 8);
		ETSIDI::printxy("PARA AVANZAR Y VOLVER EN LAS INSTRUCCIONES", 3, -2);
		ETSIDI::printxy("PULSE LAS FLECHAS IZQUIERDA Y DERECHA", 3, -3);
		ETSIDI::printxy("PULSA I PARA VOLVER AL INICIO", 3, -4);
		glPopMatrix();
	}
	else if (estado == INSTRUCCIONES && contInstr == 3) {
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
		ETSIDI::printxy(" Y LA CAPACIDAD DE DISPARAR CON W,A,S,D.", -9, 12);
		ETSIDI::printxy("MASCARILLA QUIRURGICA: PROPORCIONA UNA OPORTUNIDAD EXTRA.", -9, 10);
		ETSIDI::printxy("SI COGES 2 ES IGUAL QUE UNA FFP2", -9, 9);
		ETSIDI::printxy("PFIZER: ABUELA BOLT. AUMENTA SU VELOCIDAD.", -9, 7);
		ETSIDI::printxy("ASTRAZENECA: AUMENTA EL SALTO DE LA ABUELA.", -9, 3);
		ETSIDI::printxy("JANSSEN: PUEDE PASAR CUALQUIER COSA, MAS VELOCIDAD,", -9, 0);
		ETSIDI::printxy("MENOS VELOCIDAD O NADA", -9, -1);
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/abuela (6).png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3d(-8, 8, -0.1f);
		glTexCoord2d(1, 1); glVertex3d(-3, 8, -0.1f);
		glTexCoord2d(1, 0); glVertex3d(-3, 16, -0.1f);
		glTexCoord2d(0, 0); glVertex3d(-8, 16, -0.1f );
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
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
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 10);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::printxy("NARRADOR: Esta es Dolores. Dolores ha pasado todo el confinamiento completamente ", -13, 5);
		ETSIDI::printxy("sola, respetando la normativa impuesta por el gobierno.Pero su paciencia esta llegando a su limite", -13, 4);
		ETSIDI::printxy("(ring ring ring) Espera parece que le estan llamando", -13, 3);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 10);

		glPopMatrix();
	}
	else if (estado == HISTORIA && contHist == 2) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/abuela (6).png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3d(-8, 8, -0.1f);
		glTexCoord2d(1, 1); glVertex3d(-3, 8, -0.1f);
		glTexCoord2d(1, 0); glVertex3d(-3, 16, -0.1f);
		glTexCoord2d(0, 0); glVertex3d(-8, 16, -0.1f);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
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
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 10);
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::printxy("DOLORES: Hola David, ay madre mia que primor que estás hecho llamando a la abuela con tus dos añitos", -13, 5);
		ETSIDI::printxy("Si, cariño la abuela tambien te echa mucho de menos.  Si, si ya mismo voy a ir a veros a todos, muy pronto", -13, 4);

	}
	else if (estado == HISTORIA && contHist == 3) {
		gluLookAt(0, 7.5, 30,  // posicion del ojo
			0.0, 7.5, 0.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);		// definimos hacia arriba (eje Y) 
		glPushMatrix();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/abuela (6).png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1); glVertex3d(-8, 8, -0.1f);
		glTexCoord2d(1, 1); glVertex3d(-3, 8, -0.1f);
		glTexCoord2d(1, 0); glVertex3d(-3, 16, -0.1f);
		glTexCoord2d(0, 0); glVertex3d(-8, 16, -0.1f);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
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
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto-Bold.TTF", 10);
		ETSIDI::printxy("NARRADOR: Y así fue, con la idea de ver a su familia en mente, que Dolores empezo a plantearse  ", -13, 6);
		ETSIDI::printxy("salir de casa y combatir el virus.Para poder hacerlo se preparo en casa entrenando ", -13, 5);
		ETSIDI::printxy("con los videos de Patry Jordan durante el confinamiento.", -13, 4);
		ETSIDI::printxy("Ahora al fin comienza su venganza...", -13, 3);
	}

}