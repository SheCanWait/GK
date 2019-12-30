#include "pch.h"
#include <iostream>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>


void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokoœæ i wysokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem, gdy zmieni siê rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio okreœlaj¹cej proporcjê wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna urz¹dzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Okreœlenie uk³adu wspó³rzêdnych obserwatora

	glLoadIdentity();
	// Okreœlenie przestrzeni ograniczaj¹cej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// okreœlenie okna obserwatora.
	// Pozwala to zachowaæ w³aœciwe proporcje rysowanego obiektu
	// Do okreœlenia okna obserwatora s³u¿y funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0*AspectRatio, 100.0*AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Okreœlenie uk³adu wspó³rzêdnych    

	glLoadIdentity();

}

void createTriangle(float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y) {
	glBegin(GL_TRIANGLES);
	glVertex2f(p1_x, p1_y);
	glVertex2f(p2_x, p2_y);
	glVertex2f(p3_x, p3_y);
	glEnd();
}

void RenderSceneSquare(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glColor3f(1.0f, 0.0f, 0.0f);
	//createTriangle(0, 0, 0, 50, 50, 0);
	createTriangle(0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 0.0f);
	createTriangle(0.0f, 50.0f, 50.0f, 0.0f, 50.0f, 50.0f);


	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

void RenderSceneTriangleWithTwoColors(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glColor3f(1.0f, 0.0f, 0.0f);
	createTriangle(-50.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	createTriangle(0.0f, 50.0f, 0.0f, 0.0f, 50.0f, 0.0f);

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

void RenderSceneTriangleGradient(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-50.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 50.0f);
	glEnd();
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

void createSquare(float mid_x, float mid_y, float a, int iterationsLeft) {
	iterationsLeft--;
	if (iterationsLeft <= 0) {
		return;
	}
	glColor3ub(rand() % 255, rand() % 255, rand() % 255);
	glBegin(GL_TRIANGLES);
	glVertex2f(mid_x - a / 2, mid_y + a / 2);
	glVertex2f(mid_x + a / 2, mid_y - a / 2);
	glVertex2f(mid_x + a / 2, mid_y + a / 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(mid_x - a / 2, mid_y + a / 2);
	glVertex2f(mid_x + a / 2, mid_y - a / 2);
	glVertex2f(mid_x - a / 2, mid_y - a / 2);
	glEnd();



	createSquare(mid_x, mid_y, a / 2, iterationsLeft); //srodek
	createSquare(mid_x - a, mid_y + a, a / 2, iterationsLeft); //lewo gora
	createSquare(mid_x, mid_y + a, a / 2, iterationsLeft); //gora
	createSquare(mid_x + a, mid_y + a, a / 2, iterationsLeft); //prawo gora
	createSquare(mid_x - a, mid_y, a / 2, iterationsLeft); //lewo 
	createSquare(mid_x + a, mid_y, a / 2, iterationsLeft); //prawo
	createSquare(mid_x - a, mid_y - a, a / 2, iterationsLeft); //lewo dol
	createSquare(mid_x, mid_y - a, a / 2, iterationsLeft); //dol
	createSquare(mid_x + a, mid_y - a, a / 2, iterationsLeft); //prawo dol
}

void RenderSceneSierpinski(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	float initialLength = 100;
	createSquare(0, 0, initialLength, 5);
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania
}

void MyInit(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// Kolor okna wnêtrza okna - ustawiono na szary
}

void createSolutions() {
	glutCreateWindow("Pierwszy program w OpenGL");
	glutDisplayFunc(RenderSceneSquare);
	glutReshapeFunc(ChangeSize);
	MyInit();

	glutCreateWindow("Drugi program w OpenGL");
	glutDisplayFunc(RenderSceneTriangleWithTwoColors);
	glutReshapeFunc(ChangeSize);
	MyInit();

	glutCreateWindow("Trzeci program w OpenGL");
	glutDisplayFunc(RenderSceneTriangleGradient);
	glutReshapeFunc(ChangeSize);
	MyInit();

	glutCreateWindow("Czwarty program w OpenGL");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderSceneSierpinski);

	MyInit();
}

int main(void) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	createSolutions();
	glutMainLoop();

	return 0;
}