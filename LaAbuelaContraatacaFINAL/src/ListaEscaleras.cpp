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
	numero = 0;
}
bool ListaEscaleras::subirEscalera(Jugador j) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colisionEscalerasubir(*(lista[i]), j)) {
			return true;
			break;
		}
	}
	return false;
}
bool ListaEscaleras::bajarEscalera(Jugador j) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colisionEscalerabajar(*(lista[i]), j)) {
			return true;
			break;
		}
	}
	return false;
}
void ListaEscaleras::eliminar(int index)//Funcion para eliminar enemigos correctamente del vector de enemigos
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++)
		lista[i] = lista[i + 1];
}