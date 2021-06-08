#include "ListaEscaleras.h"
ListaEscaleras::ListaEscaleras() {
	numero = 0;
	for (int i = 0; i < MAX_NUM; i++)
		lista[i] = 0;
}
ListaEscaleras::~ListaEscaleras() {

}
void ListaEscaleras::dibuja() {
	for (int i = 0; i < numero; i++)
		lista[i]->dibujar();
}
bool ListaEscaleras::agregar(Escalera* e) {
	for (int i = 0; i < numero; i++) {
		if (e == lista[i])
			return false;
	}
	if (numero < MAX_NUM)
		lista[numero++] = e;
	else
		return false;
	return true;
}
void ListaEscaleras::destruirContenido() {
	for (int i = 0; i < numero; i++)
		delete lista[i];
}
void ListaEscaleras::rebote(Jugador& j) {
	for (int i = 0; i < numero; i++) {
		
	}
}