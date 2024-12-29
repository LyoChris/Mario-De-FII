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
extern int x, y, nl, nc, harta[30][1000];
extern int time1, okesc, n;
extern string direct;
//extern int lifes = 3, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0, hoverm = 0, play = 0, gdead = 0;

void MainMenu();
void LevelsMenu();
void ScoreLevel();
void SettingsMenu();


const int MENU_ITEMS = 4;
char* menuText[MENU_ITEMS] = { "START", "CUSTOM LEVELS", "CONTROLS", "EXIT" };

const int GAMEOVER_ITEMS = 2;
char* gameOverText[GAMEOVER_ITEMS] = { "RESTART", "MAIN MENU" };

// Global variable
int selectedOption = 0;

// Function to calculate the width of the longest text element
int calculateLongestTextWidthMenu() {
	int maxWidth = 0;
	for (int i = 0; i < MENU_ITEMS; i++) {
		int textWidth = textwidth(menuText[i]);
		if (textWidth > maxWidth) {
			maxWidth = textWidth;
		}
	}
	return maxWidth;
}

void drawArrowMainMenu(int option, int color, int menuX, int menuY, int menuSpacing) {
	setcolor(color);
	int x = menuX - 50;
	int y = menuY + (option * menuSpacing);
	int points[8] = { x, y, x + 40, y + 20, x, y + 40, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

void drawMenu(int box_color, int text_color) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int padding = 30;
	int menuWidth = winWidth / 3 + calculateLongestTextWidthMenu() +2* padding;
	int menuHeight = winHeight - 100;
	int menuX = 100;
	int menuY = 100; // Adjusted to reduce top padding
	int menuSpacing = menuHeight / (MENU_ITEMS + 2); // Adjusted spacing to reduce bottom padding

	setcolor(box_color);
	for (int i = 0; i < 10; i++) {
		rectangle(menuX - i, menuY - i, menuX + menuWidth + i, menuY + menuHeight - menuSpacing + i); // Scaled rectangle to match text area
	}

	setcolor(text_color);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 5);
	for (int i = 0; i < MENU_ITEMS; i++) {
		int textX = menuX + menuWidth / 6;
		int textY = menuY + (i + 1) * menuSpacing;
		outtextxy(textX, textY, menuText[i]);
	}
}

void MainMenu() {
	cleardevice();

	int box_color = 4;
	int text_color = 14;
	int arrow_color = 14;

	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight - 100;
	int menuX = 100;
	int menuY = 100;
	int menuSpacing = menuHeight / (MENU_ITEMS + 2);

	drawMenu(box_color, text_color);
	drawArrowMainMenu(selectedOption, arrow_color, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) {//UP
			drawArrowMainMenu(selectedOption, 0, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing); // Erase current arrow
			selectedOption = (selectedOption - 1 + MENU_ITEMS) % MENU_ITEMS;
			drawArrowMainMenu(selectedOption, arrow_color, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing); // Draw new arrow
		}
		if (key == 's' || key == 80) {//DOWN
			drawArrowMainMenu(selectedOption, 0, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing); // Erase current arrow
			selectedOption = (selectedOption + 1) % MENU_ITEMS;
			drawArrowMainMenu(selectedOption, arrow_color, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing); // Draw new arrow
		}
		if (key == 13 || key == 32) {//ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				outtextxy(200, 400, "Starting Game...");
				break;
			case 1:
				outtextxy(200, 400, "Opening Settings...");
				break;
			case 2:
				outtextxy(200, 400, "Loading Controls...");
				break;
			case 3:
				running = false;
				exit(0);
				closegraph();
				break;
			}
			delay(1000);
			cleardevice();
			drawMenu(box_color, text_color);
			drawArrowMainMenu(selectedOption, arrow_color, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing);
		}
	}
}

/*
// Arrow
void drawArrowMainMenu(int option, int color, int menuX, int menuY, int menuSpacing) {
	setcolor(color);
	int x = menuX - 50;
	int y = menuY + (option * menuSpacing);
	int points[8] = { x, y, x + 40, y + 20, x, y + 40, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

// Menu
void drawMenu(int box_color, int text_color) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight - 100;
	int menuX = 100;
	int menuY = 100; // Adjusted to reduce top padding
	int menuSpacing = menuHeight / (MENU_ITEMS + 2); // Adjusted spacing to reduce bottom padding

	setcolor(box_color);
	for (int i = 0; i < 10; i++) {
		rectangle(menuX - i, menuY - i, menuX + menuWidth + i, menuY + menuHeight - menuSpacing + i); // Scaled rectangle to match text area
	}

	setcolor(text_color);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 5);
	for (int i = 0; i < MENU_ITEMS; i++) {
		int textX = menuX + menuWidth / 4;
		int textY = menuY + (i + 1) * menuSpacing;
		outtextxy(textX, textY, menuText[i]);
	}

	drawArrow(selectedOption, text_color, menuX + menuWidth / 4, menuY + menuSpacing, menuSpacing);
}

void MainMenu() {
	cleardevice();

	int box_color = 4;
	int text_color = 14;
	bool running = true;

	drawMenu(box_color, text_color);

	while (running) {
		char key = getch();
		switch (key) {
		case 'w': // Up
			selectedOption = (selectedOption - 1 + MENU_ITEMS) % MENU_ITEMS;
			cleardevice();
			drawMenu(box_color, text_color);
			break;
		case 's': // Down
			selectedOption = (selectedOption + 1) % MENU_ITEMS;
			cleardevice();
			drawMenu(box_color, text_color);
			break;
		case 13: // Enter
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				outtextxy(200, 400, "Starting Game...");
				break;
			case 1:
				outtextxy(200, 400, "Opening Settings...");
				break;
			case 2:
				outtextxy(200, 400, "Loading Controls...");
				break;
			case 3:
				running = false;
				break;
			}
			delay(1000);
			cleardevice();
			drawMenu(box_color, text_color);
			break;
		default:
			break;
		}
	}
}



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
	setbkcolor(RGB(255, 255, 255));
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
	}
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
}*/


int calculateLongestTextWidthOver() {
	int maxWidth = 0;
	for (int i = 0; i < GAMEOVER_ITEMS; i++) {
		int textWidth = textwidth(gameOverText[i]);
		if (textWidth > maxWidth) {
			maxWidth = textWidth;
		}
	}
	return maxWidth;
}

void drawArrowGameOver(int option, int color, int menuX, int menuY, int menuSpacing) {
	setcolor(color);
	int x = menuX - 50;
	int y = menuY + (option * menuSpacing);
	int points[8] = { x, y, x + 40, y + 20, x, y + 40, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

void drawGameOver(int text_color) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int padding = 30;
	int menuWidth = winWidth / 3 + calculateLongestTextWidthOver() + 2 * padding;
	int menuHeight = winHeight - 100;

	// Center the menu horizontally and vertically
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (MENU_ITEMS + 2); // Adjusted spacing

	setcolor(text_color);

	// Draw "GAME OVER" text above the menu
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);
	int gameOverWidth = textwidth("GAME OVER");
	int gameOverX = (winWidth - gameOverWidth) / 2;
	int gameOverY = menuY - 50;  // Positioning above the menu
	outtextxy(gameOverX, gameOverY, "GAME OVER");

	// Draw menu options
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	for (int i = 0; i < GAMEOVER_ITEMS; i++) {
		int textX = menuX + menuWidth / 6;
		int textY = menuY + (i + 1) * menuSpacing;
		outtextxy(textX, textY, gameOverText[i]);
	}
}

void GameOverMenu() {
	setbkcolor(BLACK);
	cleardevice();
	setbkcolor(BLACK);

	int text_color = 14;
	int arrow_color = 14;

	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight - 100;

	// Calculate menu position
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 2);

	drawGameOver(text_color);
	drawArrowGameOver(selectedOption, arrow_color, menuX + menuWidth / 6, menuY + menuSpacing, menuSpacing);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) { // UP
			drawArrowGameOver(selectedOption, 0, menuX + menuWidth / 2, menuY + menuSpacing, menuSpacing); // Erase current arrow
			selectedOption = (selectedOption - 1 + GAMEOVER_ITEMS) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + menuWidth / 2, menuY + menuSpacing, menuSpacing); // Draw new arrow
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowGameOver(selectedOption, 0, menuX + menuWidth / 2, menuY + menuSpacing, menuSpacing); // Erase current arrow
			selectedOption = (selectedOption + 1) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + menuWidth / 2, menuY + menuSpacing, menuSpacing); // Draw new arrow
		}
		if (key == 13 || key == 32) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				outtextxy(200, 400, "Starting Game...");
				break;
			case 1:
				selectedOption = 0;
				MainMenu();
			}
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