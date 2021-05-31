#include "Factoria.h"
Factoria::Factoria() {
	
}
void Factoria::CogerQuirurgica(Jugador j) {
	j.setNumBonus(j.GetNumBonus() + 1);
	if (j.GetNumBonus() == 1) {
		j.setAltura(j.getAltura() * 2);
	}
	if (j.GetNumBonus() > 2) {
		j.setNumBonus(2);
	}
}
void Factoria::CogerMascarillaTocha(Jugador j) {
	if (j.GetNumBonus() == 0) {
		j.setAltura(j.getAltura() * 2);
	}
	j.setNumBonus(2);
}
DisparoGel* Factoria::CrearDisparo(Jugador j) {
	DisparoGel* d = 0;
	//if (j.GetNumBonus() == 2) {
	d = new DisparoGel;
	//}
	Vector2D pos = j.getPos();
	d->setPos(pos.x, pos.y);
	return d;
}
void Factoria::ModificarSalto(Jugador j, Bonus b) {
	
}
Factoria::~Factoria() {

}