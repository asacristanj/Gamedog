#include "Factoria.h"
Factoria::Factoria() {
	
}
void Factoria::CogerQuirurgica(Jugador& j) {
	j.setNumBonus(j.getNumBonus() + 1);//aumento el estado de bonus
	if (j.getNumBonus() >= 2) {//cambio a aspecto de mascarilla tocha
		j.setNumBonus(2);
	}
}

void Factoria::CogerMascarillaTocha(Jugador& j) {
	j.setNumBonus(2);
}
void Factoria::CogerAstrazeneca(Jugador& j) {//acciones sobre el jugador si coge astrazeneca
	j.setImpulso(22.0f);
}
void Factoria::CogerPfizer(Jugador& j) {//acciones sobre el jugador si coge pfizer
	j.setCoefVelx(j.getVelRapida());// modifico el coeficiente de la velocidad para hacerla m?s rapida
}
void Factoria::CogerJanssen(Jugador& j) {//acciones sobre el jugador si coge janssen
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
		
		break;
	}
}
Factoria::~Factoria() {

}