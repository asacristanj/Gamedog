#include "ListaLlaves.h"
ListaLlaves::ListaLlaves() {
	for (int i = 0; i < MAX_ELEM; i++)
		lista[i] = 0;
	numero = 0;
}
ListaLlaves::~ListaLlaves(){

}
void ListaLlaves::dibuja() {
	for (int i = 0; i < numero; i++)
        lista[i]->dibuja();
}
void ListaLlaves::mueve(float t) {
	for (int i = 0; i < numero; i++)
		lista[i]->mueve(t);
}
bool ListaLlaves::agregar(Llave* l) {
	for (int i = 0; i < numero; i++) {
		if (lista[i] == l)
			return false;
	}
	if (numero < MAX_ELEM)
		lista[numero++] = l;
	else
		return false;
	return true;
}
void ListaLlaves::destruirContenido() {
	for (int i = 0; i < numero; i++) {
		delete lista[i];
	}
	numero = 0;
}
Llave* ListaLlaves::operator[](int i) {
	if (i >= numero)//si me paso, devuelvo la ultima
		i = numero - 1;
	if (i < 0) //si el indice es negativo, devuelvo la primera
		i = 0;
	return lista[i];
}
void ListaLlaves::eliminar(int index) {
	if (index >= numero || index < 0)
		return;
	delete lista[index];
	numero--;
	for (int i = index; i < numero; i++) {
		lista[i] = lista[i + 1];
	}
}
void ListaLlaves::eliminar(Llave* l) {
	for(int i=0;i<numero;i++)
		if (lista[i] == l) {
			eliminar(i);
			return;
		}
}
//Funcion que gestiona lo que sucede cuando el jugador colisiona con una de las llaves, se elimina la llave y se incrementa el numero de llaves que ha recogido el jugador
void ListaLlaves::colision(Jugador& j) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colision(*(lista[i]), j)) {
			play("sonidos/llave.wav");
			eliminar(i);
			j.setNumLlaves(j.getNumLlaves()+1);
		}
	}
}