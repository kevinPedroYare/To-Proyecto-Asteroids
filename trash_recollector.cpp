//Librerias utilizadas
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <mmsystem.h>
#include <thread>  // Se agrega la librería para gestionar el tiempo de espera

#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80

using namespace std;

int num_vidas = 3;
int corazones = 3;
int ix = 35; // x inicial
int iy = 19; // y inicial
int i,v;
int score = 0;
int repeticion = 0, nivel = 1;
bool condicion = false;
const int dimx=78, dimy=23;


void ubicar(int x, int y) {
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon, dwPos);
}

void showConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void vidas(int vi)
{
	ubicar(2,1); printf("VIDAS %d", vi);
}

void score_view(int s)
{
	ubicar(2,25); printf("SCORE %d", s);
}

void barra_salud(int n)
{
	ubicar(72,1); printf(" ");
	ubicar(73,1); printf(" ");
	ubicar(74,1); printf(" ");
	
	for(v = 0; v < n; v++){
		ubicar(72+v,1); 
		printf("%c", 3);
	}
}

void dibujar_borde()
{
	//lineas horizontales
	for(int i = 2; i < dimx; i++)
	{
		ubicar(i,3); printf_s("%c", 205);
		ubicar(i,23); printf_s("%c", 205);
	}
	//lineas verticales
	for(int i = 4; i < dimy; i++)
	{
		ubicar(2,i); printf_s("%c", 186);
		ubicar(77,i); printf_s("%c", 186);
	}
	//esquinas
	ubicar(2,3); printf_s("%c", 201);
	ubicar(2,23); printf_s("%c", 200);
	ubicar(77,3); printf_s("%c", 187);
	ubicar(77,23); printf_s("%c", 188);
}

class Elemento {
public:
    int x, y;
	int velocidad;
    char aspecto[8];

    Elemento(int x, int y, const char* _aspecto, int _velocidad)
        : x(x), y(y), velocidad(_velocidad) {
        strcpy(aspecto, _aspecto);
    }

    void dibujar() {
        ubicar(x, y);
        printf("%s", aspecto);
    }

    void borrar() {
        ubicar(x, y);
        printf("     ");
    }
};

class Nave : public Elemento {
public:

    Nave(int x, int y, int _velocidad) : Elemento(x, y, "\\____/", _velocidad) {}

    void mover(int direccion) {
        borrar();

        switch (direccion) {
            case IZQUIERDA:
                if (x > 4) x -= 2;
                break;
            case DERECHA:
                if (x < 70) x += 2;  // Se ajusta el límite para que la nave no desaparezca en el borde derecho
                break;
            case ARRIBA:
                if (y > 4) y--;
                break;
            case ABAJO:
                if (y < 19) y++;
                break;
        }
        dibujar();
    }

};
class Obstaculo : public Elemento {
public:
    Obstaculo(int x, int y, int _velocidad) : Elemento(x, y, "P", _velocidad) {}

    void mover() {
        borrar();

        if (y > 20) {
            y = 4;
            x = (rand() % 67) + 6;
        }

        y++;
        dibujar();
    }
};

class Basura : public Elemento {
public:
    Basura(int x, int y,int _velocidad) : Elemento(x, y, "T", _velocidad) {}

    void mover() {
        borrar();

        if (y > 20) {
            y = 4;
            x = (rand() % 67) + 6;
        }

        y++;
        dibujar();
    }
};

void jugar(Nave& nave, Obstaculo& obs1, Obstaculo& obs2, Obstaculo& obs3, Obstaculo& obs4, Basura& bas1, Basura& bas2, Basura& bas3, Basura& bas4) {
    //rutina asteroides
	obs1.mover();
	obs2.mover();
	obs3.mover();
	obs4.mover();

	//rutina basura
	bas1.mover();
	bas2.mover();
	bas3.mover();
	bas4.mover();

	nave.dibujar();

    if (kbhit()) {
        unsigned char tecla = getch();
        switch (tecla) {
            case IZQUIERDA:
            case DERECHA:
            case ARRIBA:
            case ABAJO:
                nave.mover(tecla);
                break;
        }
    }

    if ((obs1.x > nave.x && obs1.x < nave.x + 6 && obs1.y == nave.y - 1) ||
        (obs2.x > nave.x && obs2.x < nave.x + 6 && obs2.y == nave.y - 1) ||
        (obs3.x > nave.x && obs3.x < nave.x + 6 && obs3.y == nave.y - 1) ||
        (obs4.x > nave.x && obs4.x < nave.x + 6 && obs4.y == nave.y - 1)) {  
    }{
		corazones--;
		barra_salud(corazones);
		printf("\a"); // sonido de impacto
	}

    if ((bas1.x > nave.x && bas1.x < nave.x + 6 && bas1.y == nave.y - 1) ||
        (bas2.x > nave.x && bas2.x < nave.x + 6 && bas2.y == nave.y - 1) ||
        (bas3.x > nave.x && bas3.x < nave.x + 6 && bas3.y == nave.y - 1) ||
        (bas4.x > nave.x && bas4.x < nave.x + 6 && bas4.y == nave.y - 1)) {
        printf("\a");
    }{
		score++;
		score_view(score);
	}

	if(corazones == 0){
		num_vidas--;
		vidas(num_vidas);
		corazones = 3;
		barra_salud(corazones);
	}
}

int main() {
    showConsoleCursor(false);
    dibujar_borde();
	vidas(num_vidas);
	score_view(score);
	barra_salud(corazones);

    Nave nave(35, 19,50);
	Obstaculo obs1(10, 4,150), obs2(20, 4,160), obs3(58, 6,170), obs4(70, 9,180);
    Basura bas1(10, 6,120), bas2(14, 11,130), bas3(45, 7,140), bas4(65, 10,150);
    int velocidadNave = 60; // Ajuste la velocidad a su preferencia (menos es más rápido)
	int velocidadObstaculos = 300;  // Ajuste la velocidad a su preferencia (menos es más rápido)	

    while (num_vidas > 0) {
        jugar(nave, obs1, obs2, obs3, obs4, bas1, bas2, bas3, bas4);
        this_thread::sleep_for(chrono::milliseconds(velocidadNave));  // Añadida pausa para controlar la velocidad
		this_thread::sleep_for(chrono::milliseconds(velocidadObstaculos));  // Añadida pausa para controlar la velocidad
    }

    ubicar(34, 12);
    printf("GAME OVER");

    getch();
    return 0;
}