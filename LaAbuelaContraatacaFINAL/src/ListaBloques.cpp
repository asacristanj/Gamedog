#include "ListaBloques.h"
ListaBloques::ListaBloques() {
	numero = 0;
	for (int i = 0; i < MAXNUMBER; i++) {
		lista[i] = 0;
	}
}
ListaBloques::~ListaBloques() {

}
void ListaBloques::dibuja() {
	for (int i = 0; i < numero; i++)
		lista[i]->dibuja();
}
bool ListaBloques::agregar(BloqueSorpresa *b){
	for (int i = 0; i < numero; i++) {
		if (b == lista[i])
			return false;
	}
	if (numero < MAXNUMBER)
		lista[numero++] = b;
	else
		return false;
	return true;
}
void ListaBloques::destruirContenido() {
	for (int i = 0; i <numero; i++)
		delete lista[i];
}
void ListaBloques::rebote(Jugador& j) {
	for (int i = 0; i <numero; i++) {
		Interaccion::rebote(j, *(lista[i]));
	}
}