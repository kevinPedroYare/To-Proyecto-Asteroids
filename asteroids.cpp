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
int num_vidas = 3;
int corazones = 3;
int ix = 35; // x inicial
int iy = 19; // y inicial
int i,v;
int repeticion = 0, nivel = 1;
bool condicion = false;
const int dimx=78, dimy=23;

// Asteroides
int x = 12, y = 8;
int xx = 17, yy = 12;
int x1 = 58, ypos1 = 6;
int x2 = 70, y2 = 9;

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
		printf("♥");
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
	ubicar(ix,iy); printf("🌣");
	ubicar(xx,yy); printf("🌣");
	ubicar(x1,ypos1); printf("🌣");
	ubicar(x2,y2); printf("🌣");
	Sleep(150);

	//borrar asteroides
	ubicar(x,y); printf(" ");
	ubicar(xx,yy); printf(" ");
	ubicar(x1,ypos1); printf(" ");
	ubicar(x2,y2); printf(" ");

	if(y > 20)
	{
		y = 4;
		x = (rand()%70) + 6;
	}
	if(yy > 20)
	{
		yy = 4;
		xx = (rand()%70) + 6;
	}
	if(ypos1 > 20)
	{
		ypos1 = 4;
		x1 = (rand()%70) + 6;
	}
	if(y2 > 20)
	{
		y2 = 4;
		x2 = (rand()%70) + 6;
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
			if ( ix < 70)
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
		( x > ix && x < ix+6 && y == iy-1) || 
		( xx > ix && xx < ix+6 && yy == iy-1) || 
		( x1 > ix && x1 < ix+6 && ypos1 == iy-1) || 
		( x2 > ix && x2 < ix+6 && y2 == iy-1) 
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
	y++;
	yy++;
	ypos1++;
	y2++;

}

int main()
{
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