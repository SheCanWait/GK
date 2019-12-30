
#include "pch.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <vector>

#define _USE_MATH_DEFINES
using namespace std;


typedef float point3[3];
static GLfloat theta[] = { 0.0, 0.0, 0.0 };


void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz¹tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();

}

void whiteTeapotRotated() {
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia³y
	glRotated(60.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni

	glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty
}

void RenderSceneTeapot(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();

	Axes();
	whiteTeapotRotated();

	glFlush();



	glutSwapBuffers();
	//
}

struct myPoint2D {
	float x;
	float y;
};

struct myPoint3D {
	float x;
	float y;
	float z;
};

void spinEgg()
{

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}

void egg(int N) {
	myPoint3D square3d[100][100];
	myPoint3D colours[100][100];
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1; j++) {
			myPoint3D colour;
			colour.x = (float)(rand() % 255) / (float)255;
			colour.y = (float)(rand() % 255) / (float)255;
			colour.z = (float)(rand() % 255) / (float)255;
			colours[i][j] = colour;
		}
	}
	//myPoint3D** square3d = new myPoint3D*[N];
	//for (int i = 0; i < N; i++)
	//	square3d[i] = new myPoint3D[N];
	glRotated(60.0, 1.0, 1.0, 1.0);  // Obrót o 60 stopni
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			myPoint2D point2d;
			point2d.x = (float)j / (float)(N - 1);
			point2d.y = (float)i / (float)(N - 1);

			float x = ((- 90 * pow(point2d.x, 5))
				+ 225 * pow(point2d.x, 4) +
				(- 270 * pow(point2d.x, 3))
				+ 180 * pow(point2d.x, 2) +
				(- 45 * point2d.x)) * cos(3.14159265358979323846 * point2d.y);
			float y = (160 * pow(point2d.x, 4) +
				(- 320 * pow(point2d.x, 3))
				+ 160 * pow(point2d.x, 2));
			float z = ((- 90 * pow(point2d.x, 5))
				+ 225 * pow(point2d.x, 4) +
				(- 270 * pow(point2d.x, 3))
				+ 180 * pow(point2d.x, 2) +
				(- 45 * point2d.x)) * sin(3.14159265358979323846 * point2d.y);

			myPoint3D point3d;
			point3d.x = x;
			point3d.y = y;
			point3d.z = z;

			square3d[i][j] = point3d;
		}
	}

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1; j++) {
			if (square3d[i][j].y < 0.5) {
				glColor3f(colours[i][j].x, colours[i][j].y, colours[i][j].z);
			}
			else {
				glColor3f(colours[N - 1 - i][N - 1 - j].x, colours[N - 1 - i][N - 1 - j].y, colours[N - 1 - i][N - 1 - j].z);
			}
				glVertex3f(square3d[i][j].x, square3d[i][j].y - 5, square3d[i][j].z);
				glVertex3f(square3d[i][j + 1].x, square3d[i][j + 1].y - 5, square3d[i][j + 1].z);
				glVertex3f(square3d[i + 1][j + 1].x, square3d[i + 1][j + 1].y - 5, square3d[i + 1][j + 1].z);

				glVertex3f(square3d[i][j].x, square3d[i][j].y - 5, square3d[i][j].z);
				glVertex3f(square3d[i + 1][j].x, square3d[i + 1][j].y - 5, square3d[i + 1][j].z);
				glVertex3f(square3d[i + 1][j + 1].x, square3d[i + 1][j + 1].y - 5, square3d[i + 1][j + 1].z);
		}
	}

	//glBegin(GL_TRIANGLE_STRIP);
	//for (int i = 0; i < N - 1; i++) {
	//	for (int j = 0; j < N - 1; j++) {
	//		glColor3f(colours[i][j].x, colours[i][j].y, colours[i][j].z);
	//		glVertex3f(square3d[i][j].x, square3d[i][j].y - 5, square3d[i][j].z);
	//		glVertex3f(square3d[i + 1][j].x, square3d[i + 1][j].y - 5, square3d[i + 1][j].z);
	//		glVertex3f(square3d[i + 1][j + 1].x, square3d[i + 1][j + 1].y - 5, square3d[i + 1][j + 1].z);

	//		glVertex3f(square3d[i][j].x, square3d[i][j].y - 5, square3d[i][j].z);
	//		glVertex3f(square3d[i][j + 1].x, square3d[i][j + 1].y - 5, square3d[i][j + 1].z);
	//	}
	//}

	glEnd();
}

void RenderSceneEgg(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	Axes();
	egg(100);

	glFlush();
	glutSwapBuffers();
}

void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

int main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Teapot");

	glutDisplayFunc(RenderSceneTeapot);

	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych
	glutCreateWindow("Egg");
	glRotatef(theta[0], 1.0, 0.0, 0.0);

glRotatef(theta[1], 0.0, 1.0, 0.0);

glRotatef(theta[2], 0.0, 0.0, 1.0);
	glutDisplayFunc(RenderSceneEgg);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(spinEgg);

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT


}

