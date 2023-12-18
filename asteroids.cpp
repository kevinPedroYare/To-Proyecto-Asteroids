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
int num_vidas = 3;
int corazones = 3;
int ix = 35;
int iy = 19;
int i,v;
int repeticion = 0, nivel = 1;
bool condicion = false;

int x = 10, y = 4;
int xx = 20, yy = 4;
int x1 = 30, y11 = 4;
int x2 = 40, y2 = 4;

//Funcion gotoxy
void gotoxy (int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon,dwPos);
}

// Vidas
void vidas(int vi)
{
	gotoxy(2,1); printf("VIDAS %d", vi);
}

// Barra de salud
void barra_salud(int n)
{
	gotoxy(72,1); printf(" ");
	gotoxy(73,1); printf(" ");
	gotoxy(74,1); printf(" ");

	for(v = 0; v < n; v++){
		gotoxy(72+v,1); 
		printf("%c", 79);
	}
}

//Limite del juego
void pintar()
{
	//lineas horizontales
	for(int i = 2; i < 78; i++)
	{
		gotoxy(i,3); printf_s("═");
		gotoxy(i,23); printf_s("═");
	}
	//lineas verticales
	for(int i = 4; i < 23; i++)
	{
		gotoxy(2,i); printf_s("║");
		gotoxy(77,i); printf_s("║");
	}
	//esquinas
	gotoxy(2,3); printf_s("╔");
	gotoxy(2,23); printf_s("╚");
	gotoxy(77,3); printf_s("╗");
	gotoxy(77,23); printf_s("╝");
}

//Explosion
void explosion(int x, int y)
{
	gotoxy(x,y); printf("%s", explosion_l1);
	gotoxy(x,y+1); printf("%s", explosion_l2);
	gotoxy(x,y+2); printf("%s", explosion_l3);
	Sleep(200);

	gotoxy(x,y); printf("%s", explosion_r1);
	gotoxy(x,y+1); printf("%s", explosion_r2);
	gotoxy(x,y+2); printf("%s", explosion_r3);
	Sleep(200);

	gotoxy(x,y); printf("%s", borrar_avion);
	gotoxy(x,y+1); printf("%s", borrar_avion);
	gotoxy(x,y+2); printf("%s", borrar_avion);
}

//Jugar

void jugar(void)
{
	//rutina asteroides
	gotoxy(ix,iy); printf("%c", 2);
	gotoxy(xx,yy); printf("%c", 2);
	gotoxy(x1,y11); printf("%c", 2);
	gotoxy(x2,y2); printf("%c", 2);
	Sleep(150);

	//borrar asteroides
	gotoxy(x,y); printf(" ");
	gotoxy(xx,yy); printf(" ");
	gotoxy(x1,y11); printf(" ");
	gotoxy(x2,y2); printf(" ");

	if(y > 20)
	{
		y = 4;
		x = (rand()%70) + 6;
	}
	if(yy > 20)
	{
		y = 4;
		x = (rand()%70) + 6;
	}
	if(y11 > 20)
	{
		y = 4;
		x = (rand()%70) + 6;
	}
	if(y2 > 20)
	{
		y = 4;
		x = (rand()%70) + 6;
	}

	//mover nave
	unsigned char tecla = getch();

	switch(tecla)
	{
		case IZQUIERDA:
			if ( ix > 4)
			{
				//borrar el avion
				gotoxy(ix,iy); printf("%s", borrar_avion);
				gotoxy(ix,iy+1); printf("%s", borrar_avion);
				gotoxy(ix,iy+2); printf("%s", borrar_avion);

				ix -=2;

				//pintar el avion
				gotoxy(ix,iy); printf("%s", avion_l1);
				gotoxy(ix,iy+1); printf("%s", avion_l2);
				gotoxy(ix,iy+2); printf("%s", avion_l3);
			}
			break;
		case DERECHA:
			if ( ix > 70)
			{
				//borrar el avion
				gotoxy(ix,iy); printf("%s", borrar_avion);
				gotoxy(ix,iy+1); printf("%s", borrar_avion);
				gotoxy(ix,iy+2); printf("%s", borrar_avion);

				ix +=2;

				//pintar el avion
				gotoxy(ix,iy); printf("%s", avion_l1);
				gotoxy(ix,iy+1); printf("%s", avion_l2);
				gotoxy(ix,iy+2); printf("%s", avion_l3);
			}
			break;
	}
}

int main()
{
	pintar();
	vidas(num_vidas);
	barra_salud(corazones);

	//Avion
	gotoxy(ix,iy); printf("%s", avion_l1);
	gotoxy(ix,iy+1); printf("%s", avion_l2);
	gotoxy(ix,iy+2); printf("%s", avion_l3);

	getch();
	return 0;
}