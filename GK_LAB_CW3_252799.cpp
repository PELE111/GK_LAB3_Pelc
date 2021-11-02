/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj¹ osi 
//  uk³adu wspó³rzednych

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

const int N = 20; //rozmiar tablicy wiercho³ków NxN
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu
int model = 2;  // 1- punkty, 2- siatka, 3 - wype³nione trójk¹ty

//tablice wspó³rzêdnych wierzcho³ków
float x[N][N];
float y[N][N];
float z[N][N];

//tablice wartoœci RGB wierzcho³ków
int R[N][N];
int G[N][N];
int B[N][N];

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
void Axes(void)
{

	point3  x_min = { -5, 0.0, 0.0 };
	point3  x_max = { 5, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5, 0.0 };
	point3  y_max = { 0.0,  5, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5 };
	point3  z_max = { 0.0, 0.0,  5 };
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

/*************************************************************************************/

//Funkcja losuj¹ca kolor dla ka¿dego wierzcho³ka
void Colors() {
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < N; k++) {
			//dla wartoœci RGB losuje 0 lub 1
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
	float u = 0, v = 0; //zminne u i v wykorzystywane w funkcjach okreœlaj¹cych wierzcho³ki jajka;
	float fN = N; //wartoœæ sta³ej N jako float
	for (int i = 0; i < N; i++) {
		u = float(i / (fN)); //zmienna zmniejszana proporcjonalnie do sta³ej N, aby znajadowa³a siê w zakresie u¿ytej funkcji [0,1]
		for (int k = 0; k < N; k++) {
			v = float(k / (fN)); //zmienna jest zmniejszana proporcjonalnie do sta³ej N, aby znajadowa³a siê w zakresie u¿ytej funkcji [0,1]
			//na podstawie u¿ytej funkcji wyzaczane s¹ wierzcho³ki 
			x[i][k] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(M_PI * v);
			y[i][k] = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2) - 5;
			z[i][k] = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(M_PI * v);
		}
	}
	Colors();
	//wyznaczenie kolorów wierzcho³ków
}

//Funkcja rysuj¹ca jajko na 3 rózne sposoby
void Egg(void) {
	
	if (model == 1) { //punkty
		glColor3f(1, 1, 0); //kolor ryswoania jest ¿ó³ty
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				glBegin(GL_POINTS);
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glEnd();
			}
		}
	}

	else if (model == 2) { //siatka
		glColor3f(1, 1, 0); //kolor ryswoania jest ¿ó³ty
		
		//rysowane s¹ pionowe linie siatki jajka
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N; k++) {
				glBegin(GL_LINES); //funkcja rysuje linie
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glVertex3f(x[(i + 1) % N][k], y[(i + 1) % N][k], z[(i + 1) % N][k]);
				glEnd();

			}
		}
		
		//rysowane s¹ ukoœne linie siatki jajka
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
		
		//rysowane s¹ ukoœne linie ³¹cz¹ce krawêdzie siatki v=0 i v=N-1
		//kierunek skoœnych lini jest zamieniany w po³owie wspó³rzêdnej "u" tablicy wierzcho³ków,
		//aby kiernek wszystkich ukoœnych lini na jajku by³ taki sam
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
		
		//rysowane s¹ poziome linie siatki jajka
		for (int i = 0; i < N; i++) {
			for (int k = 0; k < N-1; k++) {
				glBegin(GL_LINES);
				glVertex3f(x[i][k], y[i][k], z[i][k]);
				glVertex3f(x[i][k + 1], y[i][k + 1], z[i][k + 1]);
				glEnd();
			}
		}

		//rysowane s¹ poziome linie ³¹cz¹ce krawêdzie siatki v=0 i v=N-1
		for (int i = 0; i < N-1; i++) {
			glBegin(GL_LINES);
			glVertex3f(x[i + 1][N - 1], y[i + 1][N - 1], z[i + 1][N - 1]);
			glVertex3f(x[N - 1 - i][0], y[N - 1 - i][0], z[N - 1 - i][0]);
			glEnd();
		}
		
	}
	
	else if (model == 3) { //wype³nione trójk¹ty

		for (int i = 0; i < N-1 ; i++) {
			for (int k = 0; k < N- 1; k++) {
				//rysowane s¹ 2 trójk¹ty o wspólnym boku pomiêdzy 4 s¹siaduj¹cymi w tablicy wiercho³kami
				glBegin(GL_POLYGON);  //funkcja rysuje wielok¹t
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

		//Rysowane s¹ trójk¹ty pomiêdzy krawêdziami u=0 i u=N-1
		for (int i = 0; i < N - 1; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok¹t
			glColor3f(R[0][i], G[0][i], B[0][i]);
			glVertex3f(x[0][i], y[0][i], z[0][i]);

			glColor3f(R[N - 1][i + 1], G[N - 1][i + 1], B[N - 1][i+1]);
			glVertex3f(x[N - 1][i + 1], y[N - 1][i + 1], z[N - 1][i+1]);

			glColor3f(R[N - 1][i], G[N - 1][i], B[N - 1][i]);
			glVertex3f(x[N - 1][i], y[N - 1][i], z[N - 1][i]);
			glEnd();
		}

		// rysowane s¹ trójk¹ty miêdzy krawêdziami v=0 i v=N-1
		for (int i = 0; i < N-1 ; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok¹t
			glColor3f(R[i][N - 1], G[i][N - 1], B[i][N - 1]);
			glVertex3f(x[i][N - 1], y[i][N - 1], z[i][N - 1]);

			glColor3f(R[i + 1][N - 1], G[i + 1][N - 1], B[i + 1][N - 1]);
			glVertex3f(x[i + 1][N - 1], y[i + 1][N - 1], z[i + 1][N - 1]);

			glColor3f(R[N - 1 - i][0], G[N - 1 - i][0], B[N - 1 - i][0]);
			glVertex3f(x[N - 1 - i][0], y[N - 1 - i][0], z[N - 1 - i][0]);
			glEnd();
		}
		for (int i = 0; i < N - 1; i++) {
			glBegin(GL_POLYGON);  //funkcja rysuje wielok¹t
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


// funkcja okreœla k¹ty obrotu jajka
void spinEgg()
{
	theta[0] -= 0.5; //wartoœæ o jak¹ zmieniany jest k¹t obrotu przy ka¿dym wywo³aniu funkcji
	if (theta[0] > 360.0) theta[0] -= 360.0; //k¹t obrotu to mod[360]

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}


// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba
// przerysowaæ scenê)
void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy¿ej
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);
	//funkcje obracaj¹ obraz o wybrany k¹t, wokó³ wybranych osi

	Egg();
	//funkcja rysuje jajko
	
	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

	glutSwapBuffers();
}

/*************************************************************************************/

// Funkcja ustalaj¹ca stan renderowania
void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny, nieprzezroczysty
	initEgg();

}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.
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
	glRotated(30, 1, 1, 1);
	glMatrixMode(GL_MODELVIEW);
	
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                   
	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

//fynkcja zwortna wyznaczaj¹ model rysowania jajka
void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1; //punkty
	if (key == 's') model = 2; //siatka
	if (key == 'w') model = 3; //wypoe³nione trójk¹ty
	RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
void main(void)
{

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(600, 600);
	//wyznaczenie wstepnej wielkoœci okna w pikselach

	glutCreateWindow("Uk³ad wspó³rzêdnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych
	glutKeyboardFunc(keys);
	glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/