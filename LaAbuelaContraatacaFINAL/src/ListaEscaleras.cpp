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
		eliminar(i);
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
Escalera* ListaEscaleras:: operator[] (int i) //Funcion que ajusta el simbolo [] para nuestro caso
{
	if (i >= numero)//Si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //Si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
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
void ListaEscaleras::eliminar(Escalera* e)
{
	for (int i = 0; i < numero; i++)
		if (lista[i] == e)
		{
			eliminar(i);
			return;
		}
}