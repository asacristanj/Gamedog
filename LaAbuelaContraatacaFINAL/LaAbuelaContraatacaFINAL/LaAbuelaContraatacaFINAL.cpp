#include "freeglut.h"
void OnDraw(void);
void OnTimer(int value);
void OnKeyboardDown(unsigned char key, int x, int y);
int main(int argc, char* argv[])
{
	//Inicializar el gestor de ventanas FREEGLUT
	//y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutCreateWindow("MiJuego");
//habilitar luces y definir perspectiva
glEnable(GL_LIGHT0);
glEnable(GL_LIGHTING);
glEnable(GL_DEPTH_TEST);
glEnable(GL_COLOR_MATERIAL);
glMatrixMode(GL_PROJECTION);
gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
//Registrar los callbacks
glutDisplayFunc(OnDraw);
glutTimerFunc(25, OnTimer, 0);//25 ms
glutKeyboardFunc(OnKeyboardDown);
//pasarle el control a FREEGLUT,que llamara a los callbacks
glutMainLoop();
return 0;
}
void OnDraw(void)
{
	//Borrado de la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10, 20, // posicion del ojo
		0.0, 0, 0.0, // hacia que punto mira (0,0,0) 
0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
//en este caso dibujamos solo un cubo de alambre
//aqui es donde hay que poner el código de dibujo
glutWireCube(2);
//Al final, cambiar el buffer (redibujar)
//no borrar esta linea ni poner nada despues
glutSwapBuffers();
}
void OnTimer(int value)
{
}
void OnKeyboardDown(unsigned char key, int x_t, int y_t)
{
}