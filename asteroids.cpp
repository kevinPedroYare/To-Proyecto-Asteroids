// LIBRERÍAS NECESARIAS
#include <windows.h>
#include <iostream>
#include <conio.h>

#define IZQUIERDA 75
#define DERECHA 77

using namespace std;

//Avion y Explosiones
char avion_l1[] = {' ',' ',' ', '*',' ',' ',' ',0};
char avion_l2[] = {' ',' ','*', '*','*',' ',' ',0};
char avion_l3[] = {' ','*',' ', '*',' ','*',' ',0};

char explosion_l1[] = {' ',' ','*','*',' ',' ',' ',0};
char explosion_l2[] = {' ','*','*','*','*',' ',' ',0};
char explosion_l3[] = {' ',' ','*','*',' ',' ',' ',0};

char explosion_r1[] = {'*',' ','*','*',' ','*',' ',0};
char explosion_r2[] = {' ','*','*','*','*',' ',' ',0};
char explosion_r3[] = {'*',' ','*','*',' ','*',' ',0};

char borrar_avion[] = {' ',' ',' ',' ',' ',' ',' ',0};

//Variables
int num_vidas = 1;
int corazones = 5;
int ix = 35; // x inicial
int iy = 19; // y inicial
int i,v;
int repeticion = 0, nivel = 1;
bool condicion = false;
const int dimx=78, dimy=23;

// Asteroides
int ast1x = 12, ast1y = 8; 		// Posición del asteroide 1
int ast2x = 17, ast2y = 12;		// Posición del asteroide 2
int ast3x = 58, ast3y = 6;		// Posición del asteroide 3
int ast4x = 70, ast4y = 9;		// Posición del asteroide 4

//Funcion ubicar
void ubicar (int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

// Mostrar el cursor
void showConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;  // true para mostrar, false para ocultar
    SetConsoleCursorInfo(out, &cursorInfo);
}

// Vidas
void vidas(int vi)
{
	ubicar(2,1); printf("VIDAS %d", vi);
}

// Barra de salud
void barra_salud(int n)
{
	ubicar(72,1); printf(" ");
	ubicar(73,1); printf(" ");
	ubicar(74,1); printf(" ");
	
	for(v = 0; v < n; v++){
		ubicar(72+v,1); 
		printf("❤");
	}
}

//Limite del juego
void dibujar_borde()
{
	//lineas horizontales
	for(int i = 2; i < dimx; i++)
	{
		ubicar(i,3); printf_s("═");
		ubicar(i,23); printf_s("═");
	}
	//lineas verticales
	for(int i = 4; i < dimy; i++)
	{
		ubicar(2,i); printf_s("║");
		ubicar(77,i); printf_s("║");
	}
	//esquinas
	ubicar(2,3); printf_s("╔");
	ubicar(2,23); printf_s("╚");
	ubicar(77,3); printf_s("╗");
	ubicar(77,23); printf_s("╝");
}

//Explosion
void explosion(void)
{
	ubicar(ix,iy); printf("%s", explosion_l1);
	ubicar(ix,iy+1); printf("%s", explosion_l2);
	ubicar(ix,iy+2); printf("%s", explosion_l3);
	Sleep(350);

	ubicar(ix,iy); printf("%s", explosion_r1);
	ubicar(ix,iy+1); printf("%s", explosion_r2);
	ubicar(ix,iy+2); printf("%s", explosion_r3);
	Sleep(350);

	ubicar(ix,iy); printf("%s", borrar_avion);
	ubicar(ix,iy+1); printf("%s", borrar_avion);
	ubicar(ix,iy+2); printf("%s", borrar_avion);
}

//Jugar

void jugar(void)
{
	//rutina asteroides
	ubicar(ast1x,ast1y); printf("🌣");
	ubicar(ast2x,ast2y); printf("🌣");
	ubicar(ast3x,ast3y); printf("🌣");
	ubicar(ast4x,ast4y); printf("🌣");
	Sleep(150);

	//borrar asteroides
	ubicar(ast1x,ast1y); printf(" ");
	ubicar(ast2x,ast2y); printf(" ");
	ubicar(ast3x,ast3y); printf(" ");
	ubicar(ast4x,ast4y); printf(" ");

	if( ast1y > 20)
	{
		ast1y = 4;
		ast1x = (rand()%70) + 6;
	}
	if(ast2y > 20)
	{
		ast2y = 4;
		ast2x = (rand()%70) + 6;
	}
	if(ast3y > 20)
	{
		ast3y = 4;
		ast3x = (rand()%70) + 6;
	}
	if(ast4y > 20)
	{
		ast4y = 4;
		ast4x = (rand()%70) + 6;
	}

if(kbhit()){
	//mover nave
	unsigned char tecla = getch();

	switch(tecla)
	{
		case IZQUIERDA:
			if ( ix > 4)
			{
				//borrar el avion
				ubicar(ix,iy); printf("%s", borrar_avion);
				ubicar(ix,iy+1); printf("%s", borrar_avion);
				ubicar(ix,iy+2); printf("%s", borrar_avion);

				ix -=2;

				//dibujar_borde el avion
				ubicar(ix,iy); printf("%s", avion_l1);
				ubicar(ix,iy+1); printf("%s", avion_l2);
				ubicar(ix,iy+2); printf("%s", avion_l3);
			}
			break;
		case DERECHA:
			if ( ix < 68)
			{
				//borrar el avion
				ubicar(ix,iy); printf("%s", borrar_avion);
				ubicar(ix,iy+1); printf("%s", borrar_avion);
				ubicar(ix,iy+2); printf("%s", borrar_avion);

				ix +=2;

				//dibujar_borde el avion
				ubicar(ix,iy); printf("%s", avion_l1);
				ubicar(ix,iy+1); printf("%s", avion_l2);
				ubicar(ix,iy+2); printf("%s", avion_l3);
			}
			break;
	}
}

	// golpe asteroide
	if( 
		( ast1x > ix && ast1x < ix+6 && ast1y == iy-1) || 
		( ast2x > ix && ast2x < ix+6 && ast2y == iy-1) || 
		( ast3x > ix && ast3x < ix+6 && ast3y == iy-1) || 
		( ast4x > ix && ast4x < ix+6 && ast4y == iy-1) 
	) {
		corazones--;
		barra_salud(corazones);
		printf("\a"); // sonido de impacto
	}

	ubicar(ix,iy); printf("%s", avion_l1); 
	ubicar(ix,iy+1); printf("%s", avion_l2); 
	ubicar(ix,iy+2); printf("%s", avion_l3); 

	if ( corazones == 0) {
		num_vidas--;
		vidas(num_vidas);
		explosion();
		corazones = 3;
		barra_salud(corazones);

	}
	ast1y++;
	ast2y++;
	ast3y++;
	ast4y++;

}

int main()
{

	showConsoleCursor(false);
	dibujar_borde();
	vidas(num_vidas);
	barra_salud(corazones);

	//Avion
	ubicar(ix,iy); printf("%s", avion_l1);
	ubicar(ix,iy+1); printf("%s", avion_l2);
	ubicar(ix,iy+2); printf("%s", avion_l3);

	while( num_vidas > 0 ) {
		jugar();
	}

	ubicar(34,12); printf("GAME OVER");

	getch();
	return 0;
}