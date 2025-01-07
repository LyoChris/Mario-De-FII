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
#include "Sounds.h"
#include "miniaudio.h"
#include "Game.h"
#include "MapEditor.h"
using namespace std;

#define MAX1 30
#define MAX2 1000

extern LevelStats levelstats[9], customstats[9];
extern ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, DeathEffect, BackGroundMusic, StageClear, PauseEffect, StarTheme;
extern clock_t start;
extern colectible coins[100], life[100];
extern goompa gompav[100];
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, *mario_main_screen, * mario_levels_menu;
extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000];
extern int time1, okesc, n, SplitMenuItems;
extern string direct, levelselect, cht;
//extern int lifes = 3, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0, hoverm = 0, play = 0, gdead = 0;

void MainMenu();
void LevelsMenu();
void ScoreLevel();
void SettingsMenu();
void CustomMenu();
void CustomLevelsMenu();
void StatsMenu();


const int MENU_ITEMS = 4;
char* menuTextEN[MENU_ITEMS] = { "START", "CUSTOM LEVELS", "CONTROLS", "EXIT" };
char* menuTextRO[MENU_ITEMS] = { "START", "NIVELE CUSTOM", "CONTROALE", "EXIT" };

const int GAMEOVER_ITEMS = 3;
char* gameOverTextEN[GAMEOVER_ITEMS] = { "RESTART", "LEVELS", "MAIN MENU" };
char* gameOverTextRO[GAMEOVER_ITEMS] = { "REINCEPE", "NIVELE", "MENIU PRINCIPAL" };

const int PAUSE_ITEMS = 3;
char* PauseTextEN[PAUSE_ITEMS] = { "RESUME", "LEVELS", "MAIN MENU" };
char* PauseTextRO[PAUSE_ITEMS] = { "RESUME", "NIVELE", "MENIU PRINCIPAL" };

const int LEVEL_ITEMS = 9;
char* levelTextEN[LEVEL_ITEMS] = { "LEVEL 1", "LEVEL 2", "LEVEL 3", "LEVEL 4", "LEVEL 5", "LEVEL 6", "LEVEL 7", "LEVEL 8", "INAPOI" };
char* levelTextRO[LEVEL_ITEMS] = { "NIVELUL 1", "NIVELUL 2", "NIVELUL 3", "NIVELUL 4", "NIVELUL 5", "NIVELUL 6", "NIVELUL 7", "NIVELUL 8", "INAPOI" };

const int CUSTOM_ITEMS = 4;
char* customTextEN[CUSTOM_ITEMS] = { "PLAY", "MAP EDITOR", "CONTROLS", "BACK"};
char* customTextRO[CUSTOM_ITEMS] = { "PLAY", "MAP EDITOR", "CONTROALE", "INAPOI"};

int CUSTOM_LEVEL_ITEMS;
char* customLevelText[10];

const int BUTTON_MENU_ITEMS = 3;
char* levelclearedText[BUTTON_MENU_ITEMS] = { "PLAY", "BACK", "MENU" };

// Global variable
int selectedOption = 0;
int hoveredButton = -1;  // Index of the button being hovered over
int clickedButton = -1;  // Index of the button clicked

// Function to calculate the width of the longest text element

void drawLanguage(int screenWidth, int screenHeight) {
	cleardevice();
	int selectedImage = 0;
	// Set up scaling factors for the images
	int imageWidth = screenWidth / 3;   // Set image width to 1/3 of screen width
	int imageHeight = screenHeight / 3;  // Set image height to 1/3 of screen height

	// Calculate X and Y positions for both images to be centered
	int x1 = (screenWidth - imageWidth) / 4;  // Left image X position
	int y1 = (screenHeight - imageHeight) / 2;                   // Centered vertically

	int x2 = (screenWidth - imageWidth)/4 + imageWidth + imageWidth/30;  // Right image X position (10 pixels apart)
	int y2 = (screenHeight - imageHeight) / 2;      // Centered vertically

	// Load and display the images
	readimagefile("ROFLAG.jpg", x1, y1, x1 + imageWidth, y1 + imageHeight);
	readimagefile("ENFLAG.jpg", x2, y2, x2 + imageWidth, y2 + imageHeight);

	// Display a simple instruction message
	setcolor(WHITE);
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, 4);
	outtextxy((x2-x1), y1+imageHeight +imageHeight/20, "SELECT THE LANGUAGE");
	outtextxy((x2 - x1/1.25), y1 + imageHeight + imageHeight/5, "SELECTEAZA LIMBA");

	// Wait for mouse click
	while (true) {
		// Continuously track mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Handle hover effect: Highlight the image being hovered over
		if (mouseX >= x1 && mouseX <= x1 + imageWidth && mouseY >= y1 && mouseY <= y1 + imageHeight) {
			setcolor(LIGHTBLUE);
			for (int i = 0;i < 4;i++) {
				rectangle(x1 + i, y1 + i, x1 + imageWidth + i, y1 + imageHeight + i); // Draw a border around the hovered image
			}
		}
		else {
			setcolor(BLACK);
			for (int i = 0;i < 4;i++) {
				rectangle(x1 + i, y1 + i, x1 + imageWidth + i, y1 + imageHeight + i); // Draw a border around the hovered image
			}
		}
		if (mouseX >= x2 && mouseX <= x2 + imageWidth && mouseY >= y2 && mouseY <= y2 + imageHeight) {
			setcolor(LIGHTBLUE);
			for (int i = 0;i < 4;i++) {
				rectangle(x2+i, y2+i, x2 + imageWidth+i, y2 + imageHeight+i); // Draw a border around the hovered image
			}
		}
		else {
			setcolor(BLACK);
			for (int i = 0;i < 4;i++) {
				rectangle(x2 + i, y2 + i, x2 + imageWidth + i, y2 + imageHeight + i); // Draw a border around the hovered image
			}
		}

		// Check if the mouse click occurs on one of the images
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);  // Clear the click event

			// Handle selection and change variable based on clicked image
			if (mouseX >= x1 && mouseX <= x1 + imageWidth && mouseY >= y1 && mouseY <= y1 + imageHeight) {
				selectedImage = 1;  // Set the variable to 1 if the left image is selected
				setcolor(GREEN);
				outtextxy(screenWidth / 2 - 70, screenHeight - 50, "Left image selected!");
				SplitMenuItems = 1;
				break; // Exit the loop after selection
			}
			else if (mouseX >= x2 && mouseX <= x2 + imageWidth && mouseY >= y2 && mouseY <= y2 + imageHeight) {
				selectedImage = 2;  // Set the variable to 2 if the right image is selected
				setcolor(GREEN);
				outtextxy(screenWidth / 2 - 70, screenHeight - 50, "Right image selected!");
				SplitMenuItems = 0;
				break; // Exit the loop after selection
			}
		}

		delay(20); // Small delay to prevent high CPU usage
	}
}

// Function to Draw a Button
void drawButton(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;  // Highlight hovered button
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	// Draw text
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);

	// Reset background color
	setbkcolor(button_color);
}

// Function to Detect Which Button the Mouse is Hovering Over
int detectMouseHover(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 7;
	int marginY = screenHeight / 5;

	for (int i = 0; i < MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		// Check if the mouse is over this button
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;  // No button is being hovered over
}

// Draw Menu
void drawMenu(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 7;
	int marginY = screenHeight / 5;
	
	settextjustify(LEFT_TEXT, TOP_TEXT);

	for (int i = 0; i < MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButton(x, y, buttonWidth, buttonHeight, menuTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButton(x, y, buttonWidth, buttonHeight, menuTextEN[i], WHITE, BLACK, isHovered);
	}
	int imageWidth = screenWidth / 3;  // Image takes 1/3 of the screen width
	int imageX = (screenWidth - imageWidth) / 2;  // Center horizontally
	int imageY = marginY - (x / 3 * 612) / x - screenHeight / 20;  // Place above the first button with padding

	putimage((x - x / 3) / 2, marginY - (x / 3 * 7) / x - y / 20, mario_main_screen, COPY_PUT);
}

void MainMenu() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&BackGroundMusic)) ma_sound_start(&BackGroundMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Detect hover
		hoveredButton = detectMouseHover(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawMenu(screenWidth, screenHeight);

		// Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					LevelsMenu();
					/*outtextxy(screenWidth / 4, screenHeight / 2, "Starting Game...");
					delay(2000);
					break;*/
				case 1:
					CustomMenu();
					break;
				case 2:
					outtextxy(screenWidth / 5, screenHeight / 2, "Opening Controls...");
					delay(2000);
					break;
				case 3:
					saveStats(levelstats);
					saveData(customLevelText, CUSTOM_LEVEL_ITEMS);
					running = false;
					break;
				}
			}
		}

		page = 1 - page;
		delay(50);  // Reduce CPU usage
	}

	//closegraph();
	exit(0);
}

// Function to Draw a Button
void drawButtonLevels(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	// Set button color
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;
	setcolor(10);
	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	// Draw text
	/*setcolor(text_color);
	setbkcolor(BLACK);*/
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);
	setbkcolor(button_color);
}

// Function to Detect Which Button the Mouse is Hovering Over
int detectMouseHoverLevels(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4;  // Button width
	int cellHeight = screenHeight / 6; // Button height
	int marginX = (screenWidth - (3 * cellWidth)) / 4; // Horizontal margin
	int marginY = (screenHeight - (3 * cellHeight)) / 4; // Vertical margin

	for (int i = 0; i < LEVEL_ITEMS; i++) {
		int column = i % 3; // Column index
		int row = i / 3;    // Row index

		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		// Check if the mouse is over this button
		if (mouseX >= x && mouseX <= x + cellWidth && mouseY >= y && mouseY <= y + cellHeight) {
			return i;
		}
	}
	return -1; // No button is being hovered over
}

// Draw Levels Menu
void drawLevelsMenu(int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4;  // Button width
	int cellHeight = screenHeight / 6; // Button height
	int marginX = (screenWidth - (3 * cellWidth)) / 4; // Horizontal margin
	int marginY = (screenHeight - (3 * cellHeight)) / 4; // Vertical margin

	for (int i = 0; i < LEVEL_ITEMS; i++) {
		int column = i % 3; // Column index
		int row = i / 3;    // Row index

		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButtonLevels(x, y, cellWidth, cellHeight, levelTextRO[i], WHITE, BLUE, isHovered);
		else
			drawButtonLevels(x, y, cellWidth, cellHeight, levelTextEN[i], WHITE, BLUE, isHovered);
	}
}

void LevelsMenu() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&BackGroundMusic)) ma_sound_start(&BackGroundMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Detect hover
		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawLevelsMenu(screenWidth, screenHeight);

		//Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				switch (clickedButton) {
				case 0: 
					cht = "level1.txt";
					StatsMenu();
					break;
				case 1: 
					cht = "level2.txt";
					StatsMenu();
					break;
				case 2: cht = "level3.txt";
					StatsMenu();
					break;
				case 3: cht = "level4.txt";
					StatsMenu();
					break;
				case 4: cht = "level5.txt";
					StatsMenu();
					break;
				case 5: cht = "level6.txt";
					StatsMenu();
					break;
				case 6: cht = "level7.txt";
					StatsMenu();
					break;
				case 7: cht = "level8.txt";
					StatsMenu();
					break;
				case 8: 
					MainMenu();
					break;
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	//closegraph();
	exit(0);
}

int detectMouseHoverCustom(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 7;
	int marginY = screenHeight / 5;

	for (int i = 0; i < CUSTOM_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		// Check if the mouse is over this button
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;  // No button is being hovered over
}

// Draw Menu
void drawCustomMenu(int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 7;
	int marginY = screenHeight / 5;

	settextjustify(LEFT_TEXT, TOP_TEXT);

	for (int i = 0; i < CUSTOM_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		bool isHovered = (i == hoveredButton);
		if (SplitMenuItems == 1)
			drawButton(x, y, buttonWidth, buttonHeight, customTextRO[i], WHITE, BLACK, isHovered);
		else
			drawButton(x, y, buttonWidth, buttonHeight, customTextEN[i], WHITE, BLACK, isHovered);
	}
	int imageWidth = screenWidth / 3;  // Image takes 1/3 of the screen width
	int imageX = (screenWidth - imageWidth) / 2;  // Center horizontally
	int imageY = marginY - (x / 3 * 612) / x - screenHeight / 20;  // Place above the first button with padding

	putimage((x - x / 3) / 2, marginY - (x / 3 * 7) / x - y / 20, mario_main_screen, COPY_PUT);
}

void CustomMenu() {
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	while (running) {
		if (!ma_sound_is_playing(&BackGroundMusic)) ma_sound_start(&BackGroundMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();

		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Detect hover
		hoveredButton = detectMouseHoverCustom(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawCustomMenu(screenWidth, screenHeight);

		// Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					CustomLevelsMenu();
					/*outtextxy(screenWidth / 4, screenHeight / 2, "Starting Game...");
					delay(2000);*/
					break;
				case 1:
					MapEditorLevels();
					break;
				case 2:
					outtextxy(screenWidth / 5, screenHeight / 2, "Opening Controls...");
					delay(2000);
					break;
				case 3:
					MainMenu();
				}
			}
		}

		page = 1 - page;
		delay(50);  // Reduce CPU usage
	}

	//closegraph();
	exit(0);
}

// Draw Levels Menu
void drawCustomLevelsMenu(int screenWidth, int screenHeight) {
	int cellWidth = screenWidth / 4;  // Button width
	int cellHeight = screenHeight / 6; // Button height
	int marginX = (screenWidth - (3 * cellWidth)) / 4; // Horizontal margin
	int marginY = (screenHeight - (3 * cellHeight)) / 4; // Vertical margin
	cout << CUSTOM_LEVEL_ITEMS;
	for (int i = 0; i < CUSTOM_LEVEL_ITEMS; i++) {
		int column = i % 3; // Column index
		int row = i / 3;    // Row index
		cout << customLevelText[i] << endl;
		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY);

		bool isHovered = (i == hoveredButton);
		if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 0) {
			drawButtonLevels(x, y, cellWidth, cellHeight, "BACK", WHITE, BLUE, isHovered);
		}
		else {
			if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 1) {
				drawButtonLevels(x, y, cellWidth, cellHeight, "INAPOI", WHITE, BLUE, isHovered);
			}
			else {
				drawButtonLevels(x, y, cellWidth, cellHeight, customLevelText[i], WHITE, BLUE, isHovered);
			}
		}
	}
}

void CustomLevelsMenu() {
	ma_sound_stop(&StarTheme);
	ma_sound_seek_to_pcm_frame(&StarTheme, 0);
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {

		if (!ma_sound_is_playing(&BackGroundMusic)) {
			ma_sound_start(&BackGroundMusic);
		}
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Detect hover
		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawCustomLevelsMenu(screenWidth, screenHeight);

		//Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				if (strcmp(customLevelText[clickedButton], "BACK") == 0) {
					CustomMenu();
				}
				else {
					char path[50];
					strcpy(path, customLevelText[clickedButton]);
					strcat(path, ".txt"); // Append file extension
					cht = path;
					MapLoader();
					MarioGame();
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	//closegraph();
	exit(0);
}

void drawButtonLevelsReplacer(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered, int yOffset) {
	// Set button color
	int finalColor = isHovered ? RED : button_color;
	int textColor = isHovered ? YELLOW : default_text_color;
	setcolor(10);
	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	// Draw text
	/*setcolor(text_color);
	setbkcolor(BLACK);*/
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)+ yOffset) / 2 ;
	outtextxy(textX, textY, text);
	setbkcolor(button_color);
}

void drawCustomLevelsMenuReplacer(int screenWidth, int screenHeight) {
	int textHeight;

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 4); // Set font and size
	if (SplitMenuItems == 1) {
		char headerText[] = "ALEGE CE NIVEL INLOCUIESTI:";
		int textWidth = textwidth(headerText);
		textHeight = textheight(headerText);
		outtextxy((screenWidth - textWidth) / 2, textHeight, headerText);
	}
	else {
		char headerText[] = "CHOOSE WHICH LEVEL TO REPLACE:";
		int textWidth = textwidth(headerText);
		textHeight = textheight(headerText);
		outtextxy((screenWidth - textWidth) / 2, textHeight, headerText);
	}

	// Calculate button grid layout
	int cellWidth = screenWidth / 4;  // Button width
	int cellHeight = screenHeight / 6; // Button height
	int marginX = (screenWidth - (3 * cellWidth)) / 4; // Horizontal margin
	int marginY = (screenHeight - (3 * cellHeight)) / 4; // Vertical margin
	int yOffset = textHeight; // Offset buttons below the header text

	// Draw buttons
	for (int i = 0; i < CUSTOM_LEVEL_ITEMS; i++) {
		int column = i % 3; // Column index
		int row = i / 3;    // Row index
		int x = marginX + column * (cellWidth + marginX);
		int y = marginY + row * (cellHeight + marginY) + yOffset;

		bool isHovered = (i == hoveredButton);

		if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 0) {
			drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, "BACK", WHITE, BLUE, isHovered, yOffset);
		}
		else {
			if (i == CUSTOM_LEVEL_ITEMS - 1 && SplitMenuItems == 1) {
				drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, "INAPOI", WHITE, BLUE, isHovered, yOffset);
			}
			else {
				drawButtonLevelsReplacer(x, y, cellWidth, cellHeight, customLevelText[i], WHITE, BLUE, isHovered, yOffset);
			}
		}
	}
}

void CustomLevelsMenuReplacer(char filename[]) {

	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;

	while (running) {
		if (!ma_sound_is_playing(&BackGroundMusic)) ma_sound_start(&BackGroundMusic);
		setactivepage(page);
		setvisualpage(1 - page);
		cleardevice();
		putimage(0, 0, mario_levels_menu, COPY_PUT);

		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();

		// Detect hover
		hoveredButton = detectMouseHoverLevels(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawCustomLevelsMenuReplacer(screenWidth, screenHeight);

		//Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				setvisualpage(page);
				cleardevice();
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);
				if (strcmp(customLevelText[clickedButton], "BACK") != 0) {
					delete customLevelText[clickedButton];
					customLevelText[clickedButton] = new char[strlen(filename) + 1];  // Allocate memory for the string
					strcpy(customLevelText[clickedButton], filename);  // Copy the string into the allocated memory
					setactivepage(page);
					cleardevice();
					setbkcolor(BLACK);
					setactivepage(1 - page);
					cleardevice();
					setbkcolor(BLACK);
					MapPaneler();
					return;
				}
				if (strcmp(customLevelText[clickedButton], "BACK") == 0) {
					setactivepage(page);
					setcolor(WHITE);
					cleardevice();
					setbkcolor(BLACK);
					setactivepage(1 - page);
					cleardevice();
					setbkcolor(BLACK);
					MapPaneler();
					return;
				}
			}
		}
		page = 1 - page;
		delay(50);
	}

	//closegraph();
	exit(0);
}

void drawArrowGameOver(int option, int color, int menuX, int menuY, int menuSpacing, int winWidth, int winHeight) {
	setcolor(color);

	// Scale the arrow dimensions relative to the window size
	int arrowWidth = winWidth / 40;  // Scalable width (proportional to window width)
	int arrowHeight = winHeight / 30; // Scalable height (proportional to window height)

	// Arrow's horizontal position (offset slightly to the left of the text)
	int x = menuX - arrowWidth - 10;
	int textHeight;
	// Arrow's vertical position aligned to the text
	if (SplitMenuItems == 1) {
		textHeight = textheight(gameOverTextRO[option]);
	}
	else {
		textHeight = textheight(gameOverTextEN[option]);
	}
	
	int y = menuY + (option * menuSpacing) + (menuSpacing / 2) - (textHeight / 2);

	// Define the arrow points
	int points[8] = { x, y, x + arrowWidth, y + arrowHeight / 2, x, y + arrowHeight, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, color);
	fillpoly(4, points);
}

void drawGameOver(int text_color) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	// Dynamically calculate font size
	int fontSize = winHeight / 40; // Dynamically calculate font size
	if (fontSize > 15) fontSize = 15;  // Set a max font size
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; // Adjusted menu height for better centering

	// Center the menu horizontally and vertically
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 1); // Adjusted spacing for centering

	setcolor(text_color);

	// Draw "GAME OVER" text above the menu
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);
	if (SplitMenuItems == 0) {
		int gameOverWidth = textwidth("GAME OVER");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  // Increased padding above "GAME OVER"
		outtextxy(gameOverX, gameOverY, "GAME OVER");
	}
	else {
		int gameOverWidth = textwidth("AI PIERDUT");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  // Increased padding above "GAME OVER"
		outtextxy(gameOverX, gameOverY, "AI PIERDUT");
	}

	int textX, textY;

	// Draw menu options
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	for (int i = 0; i < GAMEOVER_ITEMS; i++) {
		if (SplitMenuItems == 1) {
			textX = menuX + (menuWidth - textwidth(gameOverTextRO[i])) / 2; // Center text horizontally
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, gameOverTextRO[i]);
		}
		else {
			textX = menuX + (menuWidth - textwidth(gameOverTextEN[i])) / 2; // Center text horizontally
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, gameOverTextEN[i]);
		}
	}
}

void GameOverMenu() {
	ma_sound_stop(&BackGroundMusic);
	if (!ma_sound_is_playing(&DeathEffect)) ma_sound_start(&DeathEffect);
	selectedOption = 0;
	setbkcolor(BLACK);
	cleardevice();
	setbkcolor(BLACK);

	int text_color = 14;
	int arrow_color = 14;

	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; // Adjusted menu height

	// Calculate menu position
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (GAMEOVER_ITEMS + 1);

	drawGameOver(text_color);
	drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight);

	bool running = true;
	while (running) {
		char key = getch();
		if (key == 'w' || key == 72) { // UP
			drawArrowGameOver(selectedOption, 0, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Erase current arrow
			selectedOption = (selectedOption - 1 + GAMEOVER_ITEMS) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Draw new arrow
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowGameOver(selectedOption, 0, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Erase current arrow
			selectedOption = (selectedOption + 1) % GAMEOVER_ITEMS;
			drawArrowGameOver(selectedOption, arrow_color, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Draw new arrow
		}
		if (key == 13) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				MapReseter();
				cht = levelselect;
				ma_sound_stop(&DeathEffect);
				MarioGame();
				break;
			case 1:
				selectedOption = 0;
				MainMenu();
				break;
			case 2:
				selectedOption = 0;
				MainMenu();
				break;
			}
		}
	}
}

void drawArrowPause(int option, int r, int g, int b, int menuX, int menuY, int menuSpacing, int winWidth, int winHeight) {
	setcolor(RGB(r, g, b));

	// Scale the arrow dimensions relative to the window size
	int arrowWidth = winWidth / 40;  // Scalable width (proportional to window width)
	int arrowHeight = winHeight / 30; // Scalable height (proportional to window height)

	// Arrow's horizontal position (offset slightly to the left of the text)
	int x = menuX - arrowWidth - 10;
	int textHeight;

	if (SplitMenuItems == 1)
		textHeight = textheight(PauseTextRO[option]);
	else
		textHeight = textheight(PauseTextEN[option]);
	int y = menuY + (option * menuSpacing) + (menuSpacing / 2) - (textHeight / 2);

	// Define the arrow points
	int points[8] = { x, y, x + arrowWidth, y + arrowHeight / 2, x, y + arrowHeight, x, y };
	drawpoly(4, points);
	setfillstyle(SOLID_FILL, RGB(r, g, b));
	fillpoly(4, points);
}

void drawPause(int r, int g, int b) {
	int winWidth = getmaxx();
	int winHeight = getmaxy();

	int fontSize = winHeight / 40; // Dynamically calculate font size
	if (fontSize > 15) fontSize = 15;  // Set a max font size
	settextstyle(DEFAULT_FONT, HORIZ_DIR, fontSize);
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; // Adjusted menu height for better centering

	// Center the menu horizontally and vertically
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;

	int menuSpacing = menuHeight / (PAUSE_ITEMS + 1); // Adjusted spacing for centering

	setcolor(RGB(r, g, b));
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize + 4);

	if (SplitMenuItems == 1) {
		int gameOverWidth = textwidth("PAUZA");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  // Increased padding above "GAME PAUSED"
		outtextxy(gameOverX, gameOverY, "PAUZA");
	}
	else {
		int gameOverWidth = textwidth("GAME PAUSED");
		int gameOverX = (winWidth - gameOverWidth) / 2;
		int gameOverY = menuY - 150;  // Increased padding above "GAME PAUSED"
		outtextxy(gameOverX, gameOverY, "GAME PAUSED");
	}

	// Draw menu options
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	for (int i = 0; i < PAUSE_ITEMS; i++) {
		int textX, textY;
		if (SplitMenuItems == 1) {
			textX = menuX + (menuWidth - textwidth(PauseTextRO[i])) / 2; // Center text horizontally
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, PauseTextRO[i]);
		}
		else {
			textX = menuX + (menuWidth - textwidth(PauseTextEN[i])) / 2; // Center text horizontally
			textY = menuY + i * menuSpacing;
			outtextxy(textX, textY, PauseTextEN[i]);
		}
	}
}

void PauseMenu() {
	setvisualpage(1);
	setactivepage(1);
	selectedOption = 2;
	setbkcolor(RGB(126, 132, 246));
	cleardevice();
	setbkcolor(RGB(126, 132, 246));

	int arrow_color[3] = { 255, 255, 255 };
	char text_color[20] = "RGB(126, 132, 246)";

	int winWidth = getmaxx();
	int winHeight = getmaxy();
	int menuWidth = winWidth / 3;
	int menuHeight = winHeight / 4; // Adjusted menu height

	// Calculate menu position
	int menuX = (winWidth - menuWidth) / 2;
	int menuY = (winHeight - menuHeight) / 2;
	int menuSpacing = menuHeight / (PAUSE_ITEMS + 1);
	ma_sound_stop(&BackGroundMusic);
	ma_sound_start(&PauseEffect);
	drawPause(255, 255, 255);
	drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight);

	char key = getch();

	bool running = true;
	while (running) {
		char key = getch();
		cout << (int)key << '\n';
		cout << selectedOption << '\n';
		if (key == 'w' || key == 72) { // UP
			drawArrowPause(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Erase current arrow
			selectedOption = (selectedOption - 1 + PAUSE_ITEMS) % PAUSE_ITEMS;
			drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Draw new arrow
		}
		if (key == 's' || key == 80) { // DOWN
			drawArrowPause(selectedOption, 126, 132, 246, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Erase current arrow
			selectedOption = (selectedOption + 1) % PAUSE_ITEMS;
			drawArrowPause(selectedOption, 255, 255, 255, menuX + winWidth / 22, menuY - winHeight / 80, menuSpacing, winWidth, winHeight); // Draw new arrow
		}
		if (key == 13) { // ENTER || SPACE
			cleardevice();
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
			switch (selectedOption) {
			case 0:
				setvisualpage(0);
				setactivepage(0);
				delay(1000);
				return;
				break;
			case 1:
				std::cout << "Levels Menu";
				exit(0);
				break;
			case 2:
				selectedOption = 0;
				MapReseter();
				MainMenu();
				break;
			}
		}
	}
}

void displayText(char* text, int screenWidth, int screenHeight, int fontSize, int color) {
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, fontSize);
	setcolor(color);
	int textX = (screenWidth - textwidth(text)) / 2;
	int textY = (screenHeight - textheight(text)) / 2;
	outtextxy(textX, textY, text);
}

void drawButtonStats(int x, int y, int width, int height, char* text, int default_text_color, int button_color, bool isHovered) {
	int finalColor = isHovered ? RED : button_color;  // Highlight hovered button
	int textColor = isHovered ? YELLOW : default_text_color;

	setfillstyle(SOLID_FILL, finalColor);
	bar(x, y, x + width, y + height);

	// Draw border
	setcolor(WHITE);
	rectangle(x, y, x + width, y + height);

	// Draw text
	setbkcolor(finalColor);
	setcolor(textColor);
	settextstyle(EUROPEAN_FONT, HORIZ_DIR, height / 110);
	int textX = x + (width - textwidth(text)) / 2;
	int textY = y + (height - textheight(text)) / 2;
	outtextxy(textX, textY, text);

	setcolor(WHITE);
	line(x + 1.40 * width, y - 1.25 * height, x + 1.40 * width, y + 2 * height);

	// Reset background color
	setbkcolor(button_color);
}

// Function to Detect Which Button the Mouse is Hovering Over
int detectMouseHoverStats(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 11;
	int marginY = screenHeight / 3;

	for (int i = 0; i < BUTTON_MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		// Check if the mouse is over this button
		if (mouseX >= x && mouseX <= x + buttonWidth && mouseY >= y && mouseY <= y + buttonHeight) {
			return i;
		}
	}
	return -1;  // No button is being hovered over
}

// Draw Menu
void drawStatsMenu(int screenWidth, int screenHeight, int selected) {
	int buttonWidth = screenWidth / 4;
	int buttonHeight = screenHeight / 10;
	int marginX = screenWidth / 11;
	int marginY = screenHeight / 3;

	settextjustify(LEFT_TEXT, TOP_TEXT);
	int fontsize = screenHeight / 170;
	char LevelSpecific[50], coinsCounter[50], enemiesCounter[50], timeCounter[50], scoreCounter[50];

	sprintf(LevelSpecific, "%s STATS", levelstats[selected].disname);
	displayText(LevelSpecific, 1.35 * screenWidth, 2 * marginY, fontsize + 1, WHITE);

	int textHeight = textheight(LevelSpecific);
	sprintf(coinsCounter, "Coins collected:  %d", levelstats[selected].coins);
	sprintf(enemiesCounter, "Enemies killed:  %d", levelstats[selected].enemies);
	sprintf(timeCounter, "TIME:  %ds", levelstats[selected].time);
	sprintf(scoreCounter, "HIGH SCORE:  %d", levelstats[selected].score);


	
	displayText(coinsCounter, 1.35 * screenWidth, 2 * marginY + 4.5 * textHeight, fontsize, WHITE);
	displayText(enemiesCounter, 1.35 * screenWidth, 2 * marginY + 7.0 * textHeight, fontsize, WHITE);
	displayText(timeCounter, 1.35 * screenWidth, 2 * marginY + 9.5 * textHeight, fontsize, WHITE);
	displayText(scoreCounter, 1.35 * screenWidth, 2 * marginY + 13.0 * textHeight, fontsize + 0.75, WHITE);

	for (int i = 0; i < BUTTON_MENU_ITEMS; i++) {
		int x = marginX;
		int y = marginY + i * (buttonHeight + screenHeight / 20);  // Vertical spacing as 5% of screen height

		bool isHovered = (i == hoveredButton);

		drawButtonStats(x, y, buttonWidth, buttonHeight, levelclearedText[i], WHITE, BLACK, isHovered);
		//if (SplitMenuItems == 1)
			//drawButton(x, y, buttonWidth, buttonHeight, menuTextRO[i], WHITE, BLACK, isHovered);
		//else
		  //  drawButton(x, y, buttonWidth, buttonHeight, menuTextEN[i], WHITE, BLACK, isHovered);

	}
}

void StatsMenu() {
	int screenWidth = x;
	int screenHeight = y;
	bool running = true;
	int page = 0;
	int selected = 0;
	hoveredButton = -1;
	clickedButton = -1;

	char charArray[50];
	strcpy(charArray, cht.c_str());
	cout << '\n';
	cout << "CHT: " << cht;
	cout << " " << charArray;
	cout << " " << levelstats[1].name;
	
	for (int i = 0;i < 9;i++) {
		cout << strcmp(charArray, levelstats[i].name)<<" ";
		if (strcmp(charArray, levelstats[i].name) == 0)
		{
			cout << " " << levelstats[i].name;
			cout << " " << levelstats[i].disname;
			selected = i;
			break;
		}
	}
	cout << '\n';

	while (running) {
		setactivepage(page);
		setvisualpage(1 - page);
		setbkcolor(BLACK);
		cleardevice();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		// Get mouse position
		int mouseX = mousex();
		int mouseY = mousey();



		// Detect hover
		hoveredButton = detectMouseHoverStats(mouseX, mouseY, screenWidth, screenHeight);

		// Draw the menu
		drawStatsMenu(screenWidth, screenHeight, selected);

		// Check for mouse click
		if (ismouseclick(WM_LBUTTONDOWN)) {
			clearmouseclick(WM_LBUTTONDOWN);

			if (hoveredButton != -1) {
				clickedButton = hoveredButton;

				// Perform action based on the clicked button
				cleardevice();
				setvisualpage(page);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				switch (clickedButton) {
				case 0:
					MapReseter();
					delay(1000);
					MarioGame();
					break;
				case 1:
					LevelsMenu();
					break;
				case 2:
					MainMenu();
					break;
				}
			}
		}

		page = 1 - page;
		delay(50);  // Reduce CPU usage
	}

	//closegraph();
}