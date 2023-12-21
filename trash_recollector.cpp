// LIBRERÍAS NECESARIAS
#include <windows.h>
#include <iostream>
#include <conio.h>

#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80

using namespace std;

char box_l1[] = {'\\','-','-','-','-','-','/',0};
char box_l2[] = {' ','|',' ','R',' ','|',' ',0};
char box_l3[] = {' ','|','_','_','_','|',' ',0};

char explosion_l1[] = {' ',' ','*','*',' ',' ',' ',0};
char explosion_l2[] = {' ','*','*','*','*',' ',' ',0};
char explosion_l3[] = {' ',' ','*','*',' ',' ',' ',0};

char explosion_r1[] = {'*',' ','*','*',' ','*',' ',0};
char explosion_r2[] = {' ','*','*','*','*',' ',' ',0};
char explosion_r3[] = {'*',' ','*','*',' ','*',' ',0};

char borrar_box[] = {' ',' ',' ',' ',' ',' ',' ',0};

//Variables
int num_vidas = 3;
int corazones = 3;
int ix = 35; // x inicial
int iy = 19; // y inicial
int i,v;
int score = 0;
int repeticion = 0, nivel = 1;
bool condicion = false;
const int dimx=78, dimy=23;

// Obstáculos
int obs1x = 12, obs1y = 8; 		// Posición del obstáculo 1
int obs2x = 17, obs2y = 12;		// Posición del obstáculo 2
int obs3x = 58, obs3y = 6;		// Posición del obstáculo 3
int obs4x = 70, obs4y = 9;		// Posición del obstáculo 4

// Basuras
int bas1x = 10, bas1y = 6; 		// Posición de la basura 1
int bas2x = 14, bas2y = 11;		// Posición de la basura 2
int bas3x = 45, bas3y = 7;		// Posición de la basura 3
int bas4x = 65, bas4y = 10;		// Posición de la basura 4

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

// Score
void score_view(int s)
{
	ubicar(2,25); printf("SCORE %d", s);
}

// Barra de salud
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

//Limite del juego
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

	ubicar(ix,iy); printf("%s", borrar_box);
	ubicar(ix,iy+1); printf("%s", borrar_box);
	ubicar(ix,iy+2); printf("%s", borrar_box);
}

//Jugar

void jugar(void)
{
	//rutina asteroides
	ubicar(obs1x,obs1y); printf("%c", 251);
	ubicar(obs2x,obs2y); printf("%c", 251);
	ubicar(obs3x,obs3y); printf("%c", 251);
	ubicar(obs4x,obs4y); printf("%c", 251);


	ubicar(bas1x,bas1y); printf("%c", 184);
	ubicar(bas2x,bas2y); printf("%c", 184);
	ubicar(bas3x,bas3y); printf("%c", 184);
	ubicar(bas4x,bas4y); printf("%c", 184);


	Sleep(150);

	//borrar obstáculos
	ubicar(obs1x,obs1y); printf(" ");
	ubicar(obs2x,obs2y); printf(" ");
	ubicar(obs3x,obs3y); printf(" ");
	ubicar(obs4x,obs4y); printf(" ");
	
	//borrar basura
	ubicar(bas1x,bas1y); printf(" ");
	ubicar(bas2x,bas2y); printf(" ");
	ubicar(bas3x,bas3y); printf(" ");
	ubicar(bas4x,bas4y); printf(" ");

	// Obstáculos
	if( obs1y > 20)
	{
		obs1y = 4;
		obs1x = (rand()%70) + 6;
	}
	if(obs2y > 20)
	{
		obs2y = 4;
		obs2x = (rand()%70) + 6;
	}
	if(obs3y > 20)
	{
		obs3y = 4;
		obs3x = (rand()%70) + 6;
	}
	if(obs4y > 20)
	{
		obs4y = 4;
		obs4x = (rand()%70) + 6;
	}

	// BASURA
	if( bas1y > 20)
	{
		bas1y = 4;
		bas1x = (rand()%70) + 6;
	}
	if(bas2y > 20)
	{
		bas2y = 4;
		bas2x = (rand()%70) + 6;
	}
	if(bas3y > 20)
	{
		bas3y = 4;
		bas3x = (rand()%70) + 6;
	}
	if(bas4y > 20)
	{
		bas4y = 4;
		bas4x = (rand()%70) + 6;
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
				ubicar(ix,iy); printf("%s", borrar_box);
				ubicar(ix,iy+1); printf("%s", borrar_box);
				ubicar(ix,iy+2); printf("%s", borrar_box);

				ix -=2;

				//dibujar_borde el avion
				ubicar(ix,iy); printf("%s", box_l1);
				ubicar(ix,iy+1); printf("%s", box_l2);
				ubicar(ix,iy+2); printf("%s", box_l3);
			}
			break;
		case DERECHA:
			if ( ix < 68)
			{
				//borrar el avion
				ubicar(ix,iy); printf("%s", borrar_box);
				ubicar(ix,iy+1); printf("%s", borrar_box);
				ubicar(ix,iy+2); printf("%s", borrar_box);

				ix +=2;

				//dibujar_borde el avion
				ubicar(ix,iy); printf("%s", box_l1);
				ubicar(ix,iy+1); printf("%s", box_l2);
				ubicar(ix,iy+2); printf("%s", box_l3);
			}
			break;

			case ARRIBA: // Tecla de flecha arriba
				if ( iy > 4)
				{
					//borrar el avion
					ubicar(ix,iy); printf("%s", borrar_box);
					ubicar(ix,iy+1); printf("%s", borrar_box);
					ubicar(ix,iy+2); printf("%s", borrar_box);

					iy--;

					//dibujar el avion
					ubicar(ix,iy); printf("%s", box_l1);
					ubicar(ix,iy+1); printf("%s", box_l2);
					ubicar(ix,iy+2); printf("%s", box_l3);
				}
				break;
			case ABAJO: // Tecla de flecha abajo
				if ( iy < dimy - 3)
				{
					//borrar el avion
					ubicar(ix,iy); printf("%s", borrar_box);
					ubicar(ix,iy+1); printf("%s", borrar_box);
					ubicar(ix,iy+2); printf("%s", borrar_box);

					iy++;

					//dibujar el avion
					ubicar(ix,iy); printf("%s", box_l1);
					ubicar(ix,iy+1); printf("%s", box_l2);
					ubicar(ix,iy+2); printf("%s", box_l3);
				}
				break;
	}
}

	// Golpe Obstáculo
	if( 
		( obs1x > ix && obs1x < ix+6 && obs1y == iy-1) || 
		( obs2x > ix && obs2x < ix+6 && obs2y == iy-1) || 
		( obs3x > ix && obs3x < ix+6 && obs3y == iy-1) || 
		( obs4x > ix && obs4x < ix+6 && obs4y == iy-1) 
	) {
		corazones--;
		barra_salud(corazones);
		printf("\a"); // sonido de impacto
	}

	if( 
		( bas1x > ix && bas1x < ix+6 && bas1y == iy-1) || 
		( bas2x > ix && bas2x < ix+6 && bas2y == iy-1) || 
		( bas3x > ix && bas3x < ix+6 && bas3y == iy-1) || 
		( bas4x > ix && bas4x < ix+6 && bas4y == iy-1) 
	) {
		score++;
		score_view(score);
	}

	ubicar(ix,iy); printf("%s", box_l1); 
	ubicar(ix,iy+1); printf("%s", box_l2); 
	ubicar(ix,iy+2); printf("%s", box_l3); 

	if ( corazones == 0) {
		num_vidas--;
		vidas(num_vidas);
		explosion();
		corazones = 3;
		barra_salud(corazones);
	}
	obs1y++;
	obs2y++;
	obs3y++;
	obs4y++;


	bas1y++;
	bas2y++;
	bas3y++;
	bas4y++;

}

int main()
{

	showConsoleCursor(false);
	dibujar_borde();
	vidas(num_vidas);
	score_view(score);
	barra_salud(corazones);

	//Avion
	ubicar(ix,iy); printf("%s", box_l1);
	ubicar(ix,iy+1); printf("%s", box_l2);
	ubicar(ix,iy+2); printf("%s", box_l3);

	while( num_vidas > 0 ) {
		jugar();
	}

	ubicar(34,12); printf("GAME OVER");

	getch();
	return 0;
}