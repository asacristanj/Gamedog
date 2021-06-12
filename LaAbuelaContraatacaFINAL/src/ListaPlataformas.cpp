#include "ListaPlataformas.h"
ListaPlataformas::ListaPlataformas() {
	numero = 0;
	for (int i = 0; i < MAXNUM; i++)
		lista[i] = 0;
}
ListaPlataformas::~ListaPlataformas() {

}
void ListaPlataformas::destruirContenido() {
	for (int i = 0; i < numero; i++)
		delete lista[i];
	numero = 0;
}
void ListaPlataformas::eliminar(int index) {
		if ((index < 0) || (index >= numero))
			return;
		delete lista[index];
		numero--;
		for (int i = index; i < numero; i++)
			lista[i] = lista[i + 1];
}
bool ListaPlataformas::agregar(Plataforma* p) {
	for (int i = 0; i < numero; i++) {
		if (p == lista[i])
			return false;
	}
	if (numero < MAX_NUM)
		lista[numero++] = p;
	else
		return false;
	return true;
}
void ListaPlataformas::dibuja() {
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
void ListaPlataformas::rebote(Jugador& j)
{
	for (int i = 0; i <numero; i++)
		Interaccion::rebote(j, *(lista[i]));
}

bool ListaPlataformas::colisionEncima(Jugador j) {
	for (int i = 0; i <numero; i++) {
		if (Interaccion::colisionEncima(j, *(lista[i])))
			return true;
	}
	return false;
}
Plataforma* ListaPlataformas:: operator[] (int i) //Funcion que ajusta el simbolo [] para nuestro caso
{
	if (i >= numero)//Si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //Si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}