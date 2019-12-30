/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacją osi 
//  układu współrzędnych dla rzutowania perspektywicznego

/*************************************************************************************/
#include "pch.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>


typedef float point3[3];

static GLfloat viewer1[] = { 0.0, 0.0, 10.0 };
static GLfloat viewer2[] = { 10.0, 0.0, 15.0 };
static GLfloat viewer3[] = { 0.0, 15.0, 10.0 };
// inicjalizacja położenia obserwatora
static GLfloat theta_x = 0.0;   // kąt obrotu obiektu
static GLfloat theta_y = 0.0;
static GLfloat theta_z = 0.0;
static GLfloat pix2angle;     // przelicznik pikseli na stopnie

static GLint lmb_status = 0;       // stan klawiszy myszy
static GLint rmb_status = 0;
static GLint q_status = 0;
static GLint w_status = 0;
static GLint e_status = 0;// 0 - nie naciśnięto żadnego klawisza
							   // 1 - naciśnięty zostać lewy klawisz
static float zoom = 1;

static int x_pos_old = 0;       // poprzednia pozycja kursora myszy

static int y_pos_old = 0;

static int delta_x = 0;        // różnica pomiędzy pozycją bieżącą
									  // i poprzednią kursora myszy
static int delta_y = 0;

/*************************************************************************************/

// Funkcja rysująca osie układu wspó?rz?dnych



void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz?tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz?tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz?tek i koniec obrazu osi y
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

/*************************************************************************************/

/*************************************************************************************/
// Funkcja "bada" stan myszy i ustawia wartości odpowiednich zmiennych globalnych

void Mouse(int btn, int state, int x, int y)
{


	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora
							 // jako pozycji poprzedniej
		y_pos_old = y;
		lmb_status = 1;          // wcięnięty został lewy klawisz myszy
	}
	else
		lmb_status = 0;          // nie został wcięnięty żaden klawisz

	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		x_pos_old = x;         // przypisanie aktualnie odczytanej pozycji kursora
							 // jako pozycji poprzedniej
		y_pos_old = y;
		rmb_status = 1;          // wcięnięty został lewy klawisz myszy
	}
	else
		rmb_status = 0;          // nie został wcięnięty żaden klawisz
}

void Keyboard(unsigned char Key, int x, int y) {
	if (Key == 'q') {
		q_status = 1;
	}
	else 	q_status = 0;
	if (Key == 'w') {
		w_status = 1;
	} else 	w_status = 0;
	if (Key == 'e') {
		e_status = 1;
	}
	else 	e_status = 0;
	glutPostRedisplay();
}

/*************************************************************************************/
// Funkcja "monitoruje" położenie kursora myszy i ustawia wartości odpowiednich
// zmiennych globalnych

void Motion(GLsizei x, GLsizei y)
{

	delta_x = x - x_pos_old;     // obliczenie różnicy położenia kursora myszy

	delta_y = y - y_pos_old;

	x_pos_old = x;            // podstawienie bieżącego położenia jako poprzednie

	y_pos_old = y;

	glutPostRedisplay();     // przerysowanie obrazu sceny
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

void egg(int N) {
	myPoint3D square3d[100][100];
	myPoint3D colours[100][100];
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < N - 1; j++) {
			myPoint3D colour;
			colour.x = 120;
			colour.y = 120;
			colour.z = 120;
			colours[i][j] = colour;
		}
	}
	//myPoint3D** square3d = new myPoint3D*[N];
	//for (int i = 0; i < N; i++)
	//	square3d[i] = new myPoint3D[N];
	glRotated(60.0, 1.0, 1.0, 1.0);  // Obr�t o 60 stopni

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			myPoint2D point2d;
			point2d.x = (float)j / (float)(N - 1);
			point2d.y = (float)i / (float)(N - 1);

			float x = ((-90 * pow(point2d.x, 5))
				+ 225 * pow(point2d.x, 4) +
				(-270 * pow(point2d.x, 3))
				+ 180 * pow(point2d.x, 2) +
				(-45 * point2d.x)) * cos(3.14159265358979323846 * point2d.y);
			float y = (160 * pow(point2d.x, 4) +
				(-320 * pow(point2d.x, 3))
				+ 160 * pow(point2d.x, 2));
			float z = ((-90 * pow(point2d.x, 5))
				+ 225 * pow(point2d.x, 4) +
				(-270 * pow(point2d.x, 3))
				+ 180 * pow(point2d.x, 2) +
				(-45 * point2d.x)) * sin(3.14159265358979323846 * point2d.y);

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

void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszczącym

	glLoadIdentity();
	// Czyszczenie macierzy bie??cej

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewer1[0], viewer1[1], viewer1[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// Zdefiniowanie położenia obserwatora
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powyżej

	if (lmb_status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		theta_x += delta_x * pix2angle;    // modyfikacja kąta obrotu o kat proporcjonalny
		theta_y += delta_y * pix2angle;
	}
	if (rmb_status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		zoom += delta_y * pix2angle;
		//theta_z += delta_y * pix2angle;
	}
	if (q_status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		glLoadIdentity();
		gluLookAt(viewer1[0], viewer1[1], viewer1[2], 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
	}
	if (w_status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		glLoadIdentity();
		gluLookAt(viewer2[0], viewer2[1], viewer2[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	if (e_status == 1)                     // jeśli lewy klawisz myszy wcięnięty
	{
		glLoadIdentity();
		gluLookAt(viewer3[0], viewer3[1], viewer3[2], 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	}
	glRotatef(theta_x, 0.0, 1.0, 0.0);
	glRotatef(theta_y, 1.0, 0.0, 0.0);
	//glRotatef(theta_z, 0.0, 0.0, 0.0);
	glScalef(zoom, zoom, zoom);

	glColor3f(1.0f, 1.0f, 1.0f);
	// Ustawienie koloru rysowania na biały

	glutSolidTeapot(3.0);

	//Axes();
	//egg(100);
	// Narysowanie czajnika
	glFlush();
	// Przekazanie poleceń rysujących do wykonania
	glutSwapBuffers();
}

void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszczący (wypełnienia okna) ustawiono na czarny
	/*************************************************************************************/

//  Definicja materiału z jakiego zrobiony jest czajnik
//  i definicja źródła światła

/*************************************************************************************/


/*************************************************************************************/
// Definicja materiału z jakiego zrobiony jest czajnik

	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki ka =[kar,kag,kab] dla światła otoczenia

	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// współczynniki ks =[ksr,ksg,ksb] dla światła odbitego               

	GLfloat mat_shininess = { 20.0 };
	// współczynnik n opisujący połysk powierzchni


/*************************************************************************************/
// Definicja źródła światła


	GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
	// położenie źródła


	GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	// składowe intensywności świecenia źródła światła otoczenia
	// Ia = [Iar,Iag,Iab]

	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie dyfuzyjne Id = [Idr,Idg,Idb]

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	// składowe intensywności świecenia źródła światła powodującego
	// odbicie kierunkowe Is = [Isr,Isg,Isb]

	GLfloat att_constant = { 1.0 };
	// składowa stała ds dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_linear = { 0.05 };
	// składowa liniowa dl dla modelu zmian oświetlenia w funkcji
	// odległości od źródła

	GLfloat att_quadratic = { 0.001 };
	// składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
	// odległości od źródła
														//L = att_constant, att_linear, att_quadratic  V = 1.0, 1.0, 30.0   N = niepotrzebny
	//GLfloat I_R = mat_ambient[0] * light_ambient[0] + (1 / (a + b * d_l + c * pow(d_l, 2))) * (mat_diffuse[0] * light_diffuse[0] * (N * L) + mat_specular[0] * light_specular[0] * pow((R * V), mat_shininess));
	//GLfloat I_G = mat_ambient[1] * light_ambient[1] + (1 / (a + b * d_l + c * pow(d_l, 2))) * (mat_diffuse[1] * light_diffuse[1] * (N * L) + mat_specular[1] * light_specular[1] * pow((R * V), mat_shininess));
	//GLfloat I_B = mat_ambient[2] * light_ambient[2] + (1 / (a + b * d_l + c * pow(d_l, 2))) * (mat_diffuse[2] * light_diffuse[2] * (N * L) + mat_specular[2] * light_specular[2] * pow((R * V), mat_shininess));

/*************************************************************************************/
// Ustawienie parametrów materiału i źródła światła

/*************************************************************************************/
// Ustawienie patrametrów materiału


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


	/*************************************************************************************/
	// Ustawienie parametrów źródła

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);


	/*************************************************************************************/
	// Ustawienie opcji systemu oświetlania sceny

	glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
	glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
	glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
	glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

/*************************************************************************************/

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są 
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	pix2angle = 360.0 / (float)horizontal;  // przeliczenie pikseli na stopnie

	glMatrixMode(GL_PROJECTION);
	// Przełączenie macierzy bieżącej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bieżącej

	gluPerspective(70, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego


	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);

	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkości okna okna widoku (viewport) w zależności
	// relacji pomiędzy wysokością i szerokością okna

	glMatrixMode(GL_MODELVIEW);
	// Przełączenie macierzy bieżącej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bieżącej

}

/*************************************************************************************/

// Główny punkt wejścia programu. Program działa w trybie konsoli



int main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Rzutowanie perspektywiczne");

	glutDisplayFunc(RenderScene);
	// Określenie, że funkcja RenderScene będzie funkcją zwrotną
	// (callback function).  Będzie ona wywoływana za każdym razem
	// gdy zajdzie potrzeba przerysowania okna


	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
	// za zmiany rozmiaru okna  
	glutKeyboardFunc(Keyboard);

	glutMouseFunc(Mouse);
	// Ustala funkcję zwrotną odpowiedzialną za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcję zwrotną odpowiedzialną za badanie ruchu myszy

	MyInit();
	// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przystąpieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// Włączenie mechanizmu usuwania niewidocznych elementów sceny

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/