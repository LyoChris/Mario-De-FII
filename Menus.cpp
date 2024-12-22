#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Game.h"
using namespace std;

#define MAX1 30
#define MAX2 1000

extern clock_t start;
extern colectible coins[100], life[100];
extern goompa gompav[100];
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep;
extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
//extern int x, y, nl, nc, harta[30][1000], mv2, map, stage = -7, mappart, coino, lifo, flagpole;
extern int time1, okesc, n;
extern string direct;
//extern int lifes = 3, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0, hoverm = 0, play = 0, gdead = 0;

void MainMenu();
void LevelsMenu();
void ScoreLevel();
void SettingsMenu();

const int MENU_ITEMS = 4;
char* menuText[MENU_ITEMS] = { "START", "SETTINGS", "CONTROLS", "EXIT" };

// Variabile globale
int selectedOption = 0;

// Arrow
void drawArrow(int option, int color) {
	setcolor(color);
	int x = 270;
	int y = 280 + (option * 100);
	int points[8] = { x, y, x + 40, y + 20, x, y + 40, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

// Menu
void drawMenu(int box_color, int text_color) {
	setcolor(box_color);
	for (int i = 0; i < 10; i++) {
		rectangle(200 - i, 110 - i, 750 + i, 900 + i);
	}

	setcolor(text_color);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 5);
	for (int i = 0; i < MENU_ITEMS; i++) {
		outtextxy(340, 280 + (i * 100), menuText[i]);
	}

	drawArrow(selectedOption, 14);
}


void MainMenu() {
	cleardevice();
	/*setbkcolor(RGB(255, 255, 255));
	cleardevice();
	char t = getch();
	if (t == 'a') {
		LevelLoader();
		MarioGame();
		//LevelsMenu();
	}
	else {
		if (t == 'b') {
			SettingsMenu();
		}
		else {
			if (t == 'c') {
				closegraph();
				exit(0);
			}
		}
	}*/
	int box_color = 4;
	int text_color = 14;
	bool running = true;
	drawMenu(box_color, text_color);
	while (running) {
		char key = getch();
		std::cout << key<<" ";
		int key1 = (int)key;
		cout << key1 << '\n';
		switch (key1) {
		case 97:  // Up arrow
			selectedOption = (selectedOption - 1 + MENU_ITEMS) % MENU_ITEMS;
			break;
		case 115:  // Down arrow
			selectedOption = (selectedOption + 1) % MENU_ITEMS;
			break;
		case 13:  // Enter key
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
			switch (selectedOption) {
			case 0:
				outtextxy(350, 400, "Starting Game...");
				LevelLoader();
				MarioGame();
				break;
			case 1:
				outtextxy(350, 400, "Opening Options...");
				break;
			case 2:
				outtextxy(350, 400, "Loading Levels...");
				break;
			case 3:
				running = false;
				break;
			}
			delay(1000);
			break;
		default:
			break;
		}
	}
}

void LevelsMenu() {
	cleardevice();
	setbkcolor(RGB(255, 0, 0));
	cleardevice();
	char t = getch();
	if (t == 'a') {
		ScoreLevel();
	}
	else {
		if (t == 'b') {
			LevelLoader();
			MarioGame();
		}
	}
}

void ScoreLevel() {
	cleardevice();
	setbkcolor(RGB(0, 255, 0));
	cleardevice();
	char t = getch();
	if (t == 'a') {
		LevelLoader();
		MarioGame();
	}
	else {
		if (t == 'b') {
			LevelsMenu();
		}
	}
}

void SettingsMenu() {
	cleardevice();
	setbkcolor(RGB(0, 0, 255));
	cleardevice();
	char t = getch();
	if (t == 'a') {
		MainMenu();
	}
}