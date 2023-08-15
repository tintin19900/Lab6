#include<stdio.h>
#include<Windows.h>
#include<conio.h>


void setcolor(int fg, int bg)
{
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, bg * 16 + fg);
	}
}
typedef struct Bullet {
	bool active;
	int x, y;
}Bullet;
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf(" <-0-> ");
}
void draw_ammo(int x, int y)
{
	gotoxy(x, y);
	setcolor(7, 4);
	printf("I");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("         ");
}

void erase_ammo(int x, int y)
{
	gotoxy(x , y );
	setcolor(0, 0);
	printf("   ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}


int main()
{
	setcursor(0);
	char ch = ' ';
	int x = 38, y = 20;
	int x1[5], y1[5], i = 0;
	int x2 = 38, x3 = 38, x4 = 38, x5 = 38;
	int y2=20,y3=20,y4=20,y5 = 20;
	int moveh=99,movev=99,left=0,right=1,up=2,down=3;
	int count_b = 5;
	Bullet bullet[4] = { 1 };
	for (int i = 0;i < 5;i++) {
		bullet[i].active = false;
	}

	for (int j = 0;j < 5;j++) {
		x1[j] = 99;
		y1[j] = 99;
	}
	draw_ship(x, y);
	do { 
		if (_kbhit()) { //movement and ammo
			ch = _getch();
			if (x != 0) {
				if (ch == 'a') { moveh = left; } //left
			}
			if (x != 80) {
				if (ch == 'd') { moveh = right; } //right
			}
			if (y != 0) {
				if (ch == 'w') { movev = up; } //up
			}
			if (y != 24) {
				if (ch == 's') { movev = down; } //down
			}
			if (ch == 'z') { movev = 99;moveh = 99; } //stop all
			
			if (ch == 'f') { 
				if (count_b > 0) {
					for (int i = 0;i < 5;i++) {
						if (bullet[i].active == false) {
							bullet[i].active = true;
							bullet[i].x = x + 4;
							bullet[i].y = y - 1;
							count_b--;
							break;
						}
						
					}
				}
			}
			fflush(stdin);
		}
		Sleep(100);
		if (moveh == 99){}
		if (movev == 99){}
		if ((moveh == left) && x!=0) { erase_ship(x, y);  draw_ship(--x, y); }
		if ((moveh == right) && x!=80){ erase_ship(x, y);  draw_ship(++x, y);}
		if ((movev == up) && y != 0) { Sleep(50);erase_ship(x, y);  draw_ship(x, --y); }
		if ((movev == down) && y != 24) { Sleep(50);erase_ship(x, y);  draw_ship(x, ++y); }
		setcolor(7, 0);
		for (int i = 0;i < 5;i++) {
			if (bullet[i].y == 1) {
				erase_ammo(bullet[i].x, bullet[i].y);
				bullet[i].active = false;
				count_b++;
			}
			if (bullet[i].active) {
				erase_ammo(bullet[i].x, bullet[i].y);
				draw_ammo(bullet[i].x, --bullet[i].y);
			}
		}
	} while (ch != 'x');
	return 0;
}