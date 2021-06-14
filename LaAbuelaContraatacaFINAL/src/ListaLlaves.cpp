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
void ListaLlaves::eliminar(int i) {
	if (i >= numero || i < 0)
		return;
	delete lista[i];
	numero--;
	for (int i = 0; i < numero; i++) {
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
/* bool ListaLlaves::colision(Jugador j) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colision(*(lista[i]), j))
			return true;
	}
	return false;
}*/
void ListaLlaves::colision(Jugador& j) {
	for (int i = 0; i < numero; i++) {
		if (Interaccion::colision(*(lista[i]), j)) {
			play("sonidos/llave.wav");
			eliminar(i);
			j.setNumLlaves(j.getNumLlaves()+1);
			//j.incrementaLlaves();
		}
	}
}