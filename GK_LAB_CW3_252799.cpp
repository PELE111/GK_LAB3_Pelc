/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi 
//  uk�adu wsp�rzednych

/*************************************************************************************/

#define _USE_MATH_DEFINES

#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

typedef float point3[3];

/*************************************************************************************/

const int N = 20; //rozmiar tablicy wiercho�k�w NxN
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu
int model = 2;  // 1- punkty, 2- siatka, 3 - wype�nione tr�jk�ty

//tablice wsp�rz�dnych wierzcho�k�w
float x[N][N];
float y[N][N];
float z[N][N];

//tablice warto�ci RGB wierzcho�k�w
int R[N][N];
int G[N][N];
int B[N][N];

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych
void Axes(void)
{

	point3  x_min = { -5, 0.0, 0.0 };
	point3  x_max = { 5, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5, 0.0 };
	point3  y_max = { 0.0,  5, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5 };
	point3  z_max = { 0.0, 0.0,  5 };
	//  pocz�tek i koniec obrazu osi y
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

//Funkcja losuj�ca kolor dla ka�dego wierzcho�ka
void Colors() {
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			//dla warto�ci RGB losuje 0 lub 1
			if (x[i][k]==0 && z[i][k] == 0) {
				R[i][k] = 1;
				G[i][k] = 1;
				B[i][k] = 1;
			}
			else {
				R[i][k] = rand() % 2;
				G[i][k] = rand() % 2;
				B[i][k] = rand() % 2;
			}
		}
	}
}

void initEgg() {
	float u = 0, v = 0; //zminne u i v wykorzystywane w funkcjach okre�laj�cych wierzcho�ki jajka;
	float fN = N; //warto�� sta�ej N jako float
	for (int i = 0; i < N; i++) {
		u = float(i / (fN)); //zmienna zmniejszana proporcjonalnie do sta�ej N, aby znajadowa�a si� w zakresie u�ytej funkcji [0,1]
		for (int k = 0; k < N; k++) {
			v = float(k / (fN)); //zmienna jest zmniejszana proporcjonalnie do sta�ej N, aby znajadowa�a si� w zakresie u�ytej funkcji [0,1]
			//na podstawie u�ytej funkcji wyzaczane s� wierzcho�ki 
			x[i][k] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
			y[i][k] = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
			z[i][k] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
		}
	}
	Colors();
	//wyznaczenie kolor�w wierzcho�k�w
}

//Funkcja rysuj�ca jajko na 3 r�zne sposoby
void Egg(void) {
	
	if (model == 1) { //punkty
		glColor3f(1, 1, 0); //kolor ryswoania jest ��ty
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				glBegin(GL_POINTS);
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glEnd();
			}
		}
	}

	else if (model == 2) { //siatka
		glColor3f(1, 1, 0); //kolor ryswoania jest ��ty
		
		//rysowane s� pionowe linie siatki jajka
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				glBegin(GL_LINES); //funkcja rysuje linie
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glVertex3f(x[(i + 1) % N][k], y[(i + 1) % N][k], z[(i + 1) % N][k]);
				glEnd();

			}
		}
		
		//rysowane s� uko�ne linie siatki jajka
		for (int k = 0; k < N - 1; k++) {
			int i;
			for (i = 0; i < (N - 1) / 2; i++) {
				glBegin(GL_LINES);
				glVertex3f(x[i + 1][k], y[i + 1][k], z[i + 1][k]);
				glVertex3f(x[i][k + 1], y[i][k + 1], z[i][k + 1]);
				glEnd();
			}
			for (; i < N - 1; i++) {
				glBegin(GL_LINES);
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glVertex3f(x[i + 1][k + 1], y[i + 1][k + 1], z[i + 1][k + 1]);
				glEnd();
			}
		}
		
		//rysowane s� uko�ne linie ��cz�ce kraw�dzie siatki v=0 i v=N-1
		//kierunek sko�nych lini jest zamieniany w po�owie wsp�rz�dnej "u" tablicy wierzcho�k�w,
		//aby kiernek wszystkich uko�nych lini na jajku by� taki sam
		int i;
		for (i = 0; i < N / 2; i++) {
			glBegin(GL_LINES);
			glVertex3f(x[i + 2][N - 1], y[i + 2][N - 1], z[i + 2][N - 1]);
			glVertex3f(x[N - 1 - i][0], y[N - 1 - i][0], z[N - 1 - i][0]);
			glEnd();
		}
		for (i; i < N; i++) {
			glBegin(GL_LINES);
			glVertex3f(x[i + 1][N - 1], y[i + 1][N - 1], z[i + 1][N - 1]);
			glVertex3f(x[N - 2 - i][0], y[N - 2 - i][0], z[N - 2 - i][0]);
			glEnd();
		}
		
		//rysowane s� poziome linie siatki jajka
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N-1; k++) {
				glBegin(GL_LINES);
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glVertex3f(x[i][k + 1], y[i][k + 1], z[i][k + 1]);
				glEnd();
			}
		}

		//rysowane s� poziome linie ��cz�ce kraw�dzie siatki v=0 i v=N-1
		for (int i = 0; i < N-1; i++) {
			glBegin(GL_LINES);
			glVertex3f(x[i + 1][N - 1], y[i + 1][N - 1], z[i + 1][N - 1]);
			glVertex3f(x[N - 1 - i][0], y[N - 1 - i][0], z[N - 1 - i][0]);
			glEnd();
		}
		
	}
	
	else if (model == 3) { //wype�nione tr�jk�ty

		for (int i = 0; i < N-1 ; i++) {
			for (int k = 0; k < N- 1; k++) {
				//rysowane s� 2 tr�jk�ty o wsp�lnym boku pomi�dzy 4 s�siaduj�cymi w tablicy wiercho�kami
				glBegin(GL_POLYGON);  //funkcja rysuje wielok�t
				glColor3f(R[i][k],G[i][k],B[i][k]);
				glVertex3f(x[i][k], y[i][k], z[i][k]);

				glColor3f(R[i + 1][k], G[i + 1][k], B[i + 1][k]);
				glVertex3f(x[i + 1][k], y[i + 1][k], z[i + 1][k]);

				glColor3f(R[i][k + 1], G[i][k + 1], B[i][k + 1]);
				glVertex3f(x[i][k + 1], y[i][k + 1], z[i][k + 1]);
				glEnd();

				glBegin(GL_POLYGON);
				glColor3f(R[i + 1][k + 1], G[i + 1][k + 1], B[i + 1][k + 1]);
				glVertex3f(x[i + 1][k + 1], y[i + 1][k + 1], z[i + 1][k + 1]);

				glColor3f(R[i + 1][k], G[i + 1][k], B[i + 1][k]);
				glVertex3f(x[i + 1][k], y[i + 1][k], z[i + 1][k]);

				glColor3f(R[i][k + 1], G[i][k + 1], B[i][k + 1]);
				glVertex3f(x[i][k + 1], y[i][k + 1], z[i][k + 1]);
				glEnd();
			}
		}

		//Rysowane s� tr�jk�ty pomi�dzy kraw�dziami u=0 i u=N-1
		for (int i = 0; i < N - 1; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok�t
			glColor3f(R[0][i], G[0][i], B[0][i]);
			glVertex3f(x[0][i], y[0][i], z[0][i]);

			glColor3f(R[N - 1][i + 1], G[N - 1][i + 1], B[N - 1][i+1]);
			glVertex3f(x[N - 1][i + 1], y[N - 1][i + 1], z[N - 1][i+1]);

			glColor3f(R[N - 1][i], G[N - 1][i], B[N - 1][i]);
			glVertex3f(x[N - 1][i], y[N - 1][i], z[N - 1][i]);
			glEnd();
		}

		// rysowane s� tr�jk�ty mi�dzy kraw�dziami v=0 i v=N-1
		for (int i = 0; i < N-1 ; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok�t
			glColor3f(R[i][N - 1], G[i][N - 1], B[i][N - 1]);
			glVertex3f(x[i][N - 1], y[i][N - 1], z[i][N - 1]);

			glColor3f(R[i + 1][N - 1], G[i + 1][N - 1], B[i + 1][N - 1]);
			glVertex3f(x[i + 1][N - 1], y[i + 1][N - 1], z[i + 1][N - 1]);

			glColor3f(R[N - 1 - i][0], G[N - 1 - i][0], B[N - 1 - i][0]);
			glVertex3f(x[N - 1 - i][0], y[N - 1 - i][0], z[N - 1 - i][0]);
			glEnd();
		}
		for (int i = 0; i < N - 1; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok�t
			glColor3f(R[i+1][N - 1], G[i+1][N - 1], B[i+1][N - 1]);
			glVertex3f(x[i+1][N - 1], y[i+1][N - 1], z[i+1][N - 1]);

			glColor3f(R[N  -1- i][0], G[N  -1- i][0], B[N  -1- i][0]);
			glVertex3f(x[N  -1- i][0], y[N  -1- i][0], z[N  -1- i][0]);

			glColor3f(R[N - 2 - i][0], G[N - 2 - i][0], B[N - 2 - i][0]);
			glVertex3f(x[N - 2 - i][0], y[N - 2 - i][0], z[N - 2 - i][0]);
			glEnd();
		}
	}
}


// funkcja okre�la k�ty obrotu jajka
void spinEgg()
{
	theta[0] -= 0.5; //warto�� o jak� zmieniany jest k�t obrotu przy ka�dym wywo�aniu funkcji
	if (theta[0] > 360.0) theta[0] -= 360.0; //k�t obrotu to mod[360]

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}


// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba
// przerysowa� scen�)
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	//funkcje obracaj� obraz o wybrany k�t, wok� wybranych osi

	Egg();
	//funkcja rysuje jajko
	
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania

	glutSwapBuffers();
}

/*************************************************************************************/

// Funkcja ustalaj�ca stan renderowania
void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny, nieprzezroczysty
	initEgg();

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s�
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glRotated(30, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   
	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}

//fynkcja zwortna wyznaczaj� model rysowania jajka
void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1; //punkty
	if (key == 's') model = 2; //siatka
	if (key == 'w') model = 3; //wypoe�nione tr�jk�ty
	RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli
void main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 600);
	//wyznaczenie wstepnej wielko�ci okna w pikselach

	glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych
	glutKeyboardFunc(keys);
	glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/