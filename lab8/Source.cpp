#include <stdio.h> 
#include <windows.h> 
#include <time.h>
#include<conio.h>
#define screen_x 80 
#define screen_y 25 
HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void drawship()
{
	printf(" <-0-> ");
}
void draw_ship(int x, int y)
{
	gotoxy(x,y);
	drawship();
}
void erase_ship(){
	printf("                                                                                                                                              \n");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	for (int y = 0; y < 80; y++) {
		erase_ship();
	}
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void coler() {
	int p = (rand() % 10);
	int q = 0;
	gotoxy(p, q);
	setcolor(p, q);
}
void boys() {
	int p = (rand() % 69) + 9;
	int q = (rand() % 4) + 1;
	gotoxy(p, q);
	printf("*");
}

void boy() {
	for (int i = 0; i < 50; i++)
	{
		boys();
	}
}
char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (
		!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read)) return '\0';
	else
		return buf[0];
}
void score(int a) {
	int x = 1, y = 1, u;
	gotoxy(x, y);
	printf("%d", a);
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
	int u = 0;
	score(u);
	int bulletstatus = 0;
	boy();
	bool play = true;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	setConsole(screen_x, screen_y);
	setMode();
	while (play)
	{
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);  for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT &&
					eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					coler();
				}
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
					int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;  int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;  if (eventBuffer[i].Event.MouseEvent.dwButtonState &
						FROM_LEFT_1ST_BUTTON_PRESSED) {
						printf("left click\n");
					}
					else if (eventBuffer[i].Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED) {
						printf("right click\n");
					}
					else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) { 
						erase_ship(0, 0); boy(); draw_ship(posx, posy);
					if (cursor(posx, posy-1) == '*') {
						score(++u);
					}
					else if (cursor(posx, posy +1) == '*') {
						score(++u);
					}
					else if (cursor(posx-1, posy) == '*') {
						score(++u);
					}
					else if (cursor(posx+1, posy) == '*') {
						score(++u);
					}
					char ch = 27;
					if (_kbhit()) {
						ch = _getch();
						if (ch == 27) {
							break;
						}
					}
					}
				}
			}
			delete[] eventBuffer;
		}
		Sleep(100);
		if (u == 10) {
			break;
		}
	}
	return 0;
}
