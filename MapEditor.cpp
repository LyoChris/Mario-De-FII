#include "graphics.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include "Mario.h"
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Menus.h"
#include "miniaudio.h"
using namespace std;

extern float wh, nci, ncf, nc1, nci;
extern int x, y, nl;

struct spawnpoint {
	int i1 = 0, j1 = 0;
	int i2 = 0, j2 = 0;

}spawn[100];

extern int CUSTOM_LEVEL_ITEMS;
extern char* customLevelText[10];

int hartaloader[20][1000] = { 0 }, nr=0, edit = 1, mapi = 0, mapj = 1, selecpoz[14] = { 1,0,3,4,12,13,14,8,7,2,5,9,11,6 }, iselec = 0, bkselect = 1, panelnr = 0, ncmax = 0, jpole = -1, ipole = -1;
float nwh, ncimap=0, ncfmap;

extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * flagpolemapedit, * pipehead, * pipebody, * pipeheadpir;
void* brickblockmap, * skyblockmap, * mario_vinemap, * mario_vine_topmap, * lucky_blockmap, * mario_coinmap, * mario_idle_rightmap, * one_upmap, * flagpolepmap, * gombamap,
* pipeheadmap, * pipebodymap, * pipeheadpirmap, * brickblockmono, * skyblockmono, * mario_vinemono, * mario_vine_topmono, * lucky_blockmono, * mario_coinmono,
* mario_idle_rightmono, * one_upmono, * flagpolepmono, * gombamono, * pipeheadmono, * pipebodymono, * pipeheadpirmono, * flagpolemapeditmono, * flagpolemapeditp;


void PutMovingImage(int i, int j) {
	if (hartaloader[i][j] == 0)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, skyblockmap, COPY_PUT);
	if (hartaloader[i][j] == 1)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, brickblockmap, COPY_PUT);
	if (hartaloader[i][j] == 3)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vinemap, COPY_PUT);
	if (hartaloader[i][j] == 4)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vine_topmap, COPY_PUT);
	if (hartaloader[i][j] == 5)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, gombamap, COPY_PUT);
	if (hartaloader[i][j] == 9)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_idle_rightmap, COPY_PUT);
	if (hartaloader[i][j] == 8)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, lucky_blockmap, COPY_PUT);
	if (hartaloader[i][j] == 7)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_coinmap, COPY_PUT);
	if (hartaloader[i][j] == 13)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadpirmap, COPY_PUT); // placeholder pt pirhana
	if (hartaloader[i][j] == 14)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadmap, COPY_PUT); // placeholder pt pipehead
	if (hartaloader[i][j] == 12)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipebodymap, COPY_PUT); // placeholder pt pipebody
	if (hartaloader[i][j] == 2)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, one_upmap, COPY_PUT);
	if (hartaloader[i][j] == 11)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, flagpolemapeditp, COPY_PUT);
}

void PutMapEditor(int i, int j, int block) {
	if (block == 0)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, skyblockmap, COPY_PUT);
	if (block == 1)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, brickblockmap, COPY_PUT);
	if (block == 3)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vinemap, COPY_PUT);
	if (block == 4)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_vine_topmap, COPY_PUT);
	if (block == 5)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, gombamap, COPY_PUT);
	if (block == 9)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_idle_rightmap, COPY_PUT);
	if (block == 8)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, lucky_blockmap, COPY_PUT);
	if (block == 7)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, mario_coinmap, COPY_PUT);
	if (block == 13)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadpirmap, COPY_PUT); // placeholder pt pirhana
	if (block == 14)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipeheadmap, COPY_PUT); // placeholder pt pipehead
	if (block == 12)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, pipebodymap, COPY_PUT); // placeholder pt pipebody
	if (block == 2)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, one_upmap, COPY_PUT);
	if (block == 11)
		putimage((j - ncimap + 1) * nwh, (i + 1) * nwh, flagpolemapeditp, COPY_PUT);
}

void SelectorImageMono(int i){
	if (iselec == 0) putimage((1 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	if (iselec == 1) putimage((1 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	if (iselec == 2)putimage((1 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	if (iselec == 3)putimage((1 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	if (iselec == 4)putimage((1 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((1 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((1 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((1 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	if (iselec == 8)putimage((1 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	if (iselec == 9)putimage((1 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	if (iselec == 10)putimage((1 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	if (iselec == 11)putimage((1 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	if (iselec == 12)putimage((1 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);
}

void SelectorImage(int i) {
	if (iselec == 0) putimage((1 + 0) * wh, 17 * wh, brickblock, COPY_PUT);
	if (iselec == 1) putimage((1 + 1.5) * wh, 17 * wh, skyblock, COPY_PUT);
	if (iselec == 2)putimage((1 + 3.0) * wh, 17 * wh, mario_vine, COPY_PUT);
	if (iselec == 3)putimage((1 + 4.5) * wh, 17 * wh, mario_vine_top, COPY_PUT);
	if (iselec == 4)putimage((1 + 6.0) * wh, 17 * wh, pipebody, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((1 + 7.5) * wh, 17 * wh, pipeheadpir, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((1 + 9.0) * wh, 17 * wh, pipehead, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((1 + 10.5) * wh, 17 * wh, lucky_block, COPY_PUT);
	if (iselec == 8)putimage((1 + 12.0) * wh, 17 * wh, mario_coin, COPY_PUT);
	if (iselec == 9)putimage((1 + 13.5) * wh, 17 * wh, one_up, COPY_PUT);
	if (iselec == 10)putimage((1 + 15.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT);
	if (iselec == 11)putimage((1 + 16.5) * wh, 17 * wh, mario_idle_right, COPY_PUT);
	if (iselec == 11)putimage((1 + 18.0) * wh, 17 * wh, flagpolemapedit, COPY_PUT);
}

void MapPaneler() {
	cleardevice();

	int lastColumnX = 0; // To track the x-coordinate of the last column

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	// Draw the matrix
	for (int i = 0; i < nl; i += 1) {
		for (int j = (int)ncimap; j < ncfmap; j += 1) {
			cout << i << " " << j << endl;
			PutMovingImage(i, j);
			lastColumnX = j - ncimap; // Keep updating to get the last column index
		}
	}

	// Compute the x-coordinate of the last column's right edge
	int blockWidth = nwh; // Assuming 'wh' is the width of a single block
	int menuStartX = (lastColumnX + 4) * blockWidth + (blockWidth / 10); // One padding space to the right of the last column

	// Place other game elements
	putimage((1 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	putimage((1 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((1 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((1 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((1 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT);
	putimage((1 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT);
	putimage((1 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT);
	putimage((1 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((1 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((1 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((1 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((1 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((1 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

	// Menu parameters
	int winHeight = getmaxy();
	int padding = blockWidth / 5;        // Padding between menu elements
	int elementHeight = winHeight / 15; // Scalable element height
	int rectWidth = elementHeight;      // Rectangle width matches height
	int textSize = elementHeight / 12;  // Scalable font size

	int baseX = menuStartX;              // Base X position for menu
	int baseY = padding * 6;             // Base Y position for menu

	cout << "baseX" << ' ' << baseX << '\n';
	// Menu items and their keys
	char* menuItems[5] = { "SAVE MAP", "LOAD MAP", "PREV PANEL", "NEXT PANEL", "BACK" };
	char keys[5] = { 'M', 'N', 'J', 'L','B' };

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, textSize); // Set scalable font

	// Draw the menu
	for (int i = 0; i < 5; i++) {
		int rectY = baseY + i * (elementHeight + 2 * padding); // Rectangle Y-coordinate
		cout << 'a';
		// Draw key rectangle
		rectangle(baseX, rectY, baseX + rectWidth, rectY + elementHeight);

		// Center the key within the rectangle
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		char key[2] = { keys[i], '\0' }; // Convert char to string
		int keyCenterX = baseX + rectWidth / 2;
		int keyCenterY = rectY + elementHeight / 1.5;
		outtextxy(keyCenterX, keyCenterY, key);

		// Align menu text vertically and horizontally with the key
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(baseX + rectWidth + padding, keyCenterY, menuItems[i]);
	}

	// Draw panel controls below the matrix
	int panelTextY = nl * (blockWidth + 2); // Y-coordinate for panel control text
	int matrixEndX = (lastColumnX + 1) * blockWidth; // X-coordinate of the last column

	// Current Panel
	int currentCenterX = (matrixEndX - blockWidth) / 3; // Center for "CURRENT PANEL"
	char currentPanelText[20];
	sprintf(currentPanelText, "CURRENT PANEL: %d", panelnr); // Replace '1' with the current panel number
	outtextxy(currentCenterX, panelTextY + elementHeight / 2, currentPanelText);

}

void InitialDrawing() {
	cleardevice();
	memset(hartaloader, 0, sizeof(hartaloader));
	ncimap = 0;
	ncfmap = ncf;
	panelnr = 0;

	int lastColumnX = 0; // To track the x-coordinate of the last column

	// Draw the matrix
	for (int i = 0; i < nl; i += 1) {
		for (int j = (int)ncimap; j < ncfmap; j += 1) {
			cout << i << " " << j << endl;
			PutMovingImage(i, j);
			lastColumnX = j; // Keep updating to get the last column index
		}
	}

	// Compute the x-coordinate of the last column's right edge
	int blockWidth = nwh; // Assuming 'wh' is the width of a single block
	int menuStartX = (lastColumnX + 4) * blockWidth + (blockWidth / 10); // One padding space to the right of the last column

	// Place other game elements
	putimage((1 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	putimage((1 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((1 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((1 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((1 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT);
	putimage((1 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT);
	putimage((1 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT);
	putimage((1 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((1 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((1 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((1 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((1 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((1 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

	// Menu parameters
	int winHeight = getmaxy();
	int padding = blockWidth / 5;        // Padding between menu elements
	int elementHeight = winHeight / 15; // Scalable element height
	int rectWidth = elementHeight;      // Rectangle width matches height
	int textSize = elementHeight / 12;  // Scalable font size

	int baseX = menuStartX;              // Base X position for menu
	int baseY = padding * 6;             // Base Y position for menu
	cout << "baseX" << ' ' << baseX << '\n';
	// Menu items and their keys
	char* menuItems[5] = { "SAVE MAP", "LOAD MAP", "PREV PANEL", "NEXT PANEL", "BACK"};
	char keys[5] = { 'M', 'N', 'J', 'L','B'};

	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, textSize); // Set scalable font

	// Draw the menu
	for (int i = 0; i < 5; i++) {
		int rectY = baseY + i * (elementHeight + 2 * padding); // Rectangle Y-coordinate

		// Draw key rectangle
		rectangle(baseX, rectY, baseX + rectWidth, rectY + elementHeight);

		// Center the key within the rectangle
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		char key[2] = { keys[i], '\0' }; // Convert char to string
		int keyCenterX = baseX + rectWidth / 2;
		int keyCenterY = rectY + elementHeight / 1.5;
		outtextxy(keyCenterX, keyCenterY, key);

		// Align menu text vertically and horizontally with the key
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(baseX + rectWidth + padding, keyCenterY, menuItems[i]);
	}

	// Draw panel controls below the matrix
	int panelTextY = nl*(blockWidth +2); // Y-coordinate for panel control text
	int matrixEndX = (lastColumnX + 1) * blockWidth; // X-coordinate of the last column

	// Current Panel
	int currentCenterX = (matrixEndX - blockWidth)/3; // Center for "CURRENT PANEL"
	char currentPanelText[20];
	sprintf(currentPanelText, "CURRENT PANEL: %d", panelnr); // Replace '1' with the current panel number
	outtextxy(currentCenterX, panelTextY + elementHeight / 2, currentPanelText);

}

void saveMap() {
	char filename[50] = ""; // Buffer for the file name
	int pos = 0;           // Current position in the filename buffer
	char ch;

	// Prompt user to enter filename
	setvisualpage(1);
	setactivepage(1);
	cleardevice();

	setcolor(WHITE);
	int fontSize = min(x / 20, y / 15); // Scale with window size
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, fontSize / 10); // Adjust text style

	char prompt[] = "Enter filename to save (without externsion):";
	int textWidth = textwidth(prompt);
	int textHeight = textheight(prompt);
	outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, prompt);

	while (true) {
		ch = getch();

		if (ch == 13) { // If ENTER is pressed
			break;
		}
		else if (ch == 8) { // If BACKSPACE is pressed
			if (pos > 0) {
				pos--;
				filename[pos] = '\0';
				// Clear and redraw the filename input
				setfillstyle(SOLID_FILL, BLACK);
				bar(50, y / 2, x - 50, y / 2 + 50); // Clear area
				outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
			}
		}
		else if (pos < 49 && (isalnum(ch) || ch == '_')) { // Allow alphanumeric and underscore
			filename[pos] = ch;
			filename[pos + 1] = '\0';
			pos++;

			// Display typed filename
			setfillstyle(SOLID_FILL, BLACK);
			bar(50, y / 2, x - 50, y / 2 + 50); // Clear area
			outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
		}
	}
	if (CUSTOM_LEVEL_ITEMS ==8) {
		CUSTOM_LEVEL_ITEMS == 8;
	}
	else {
		CUSTOM_LEVEL_ITEMS++;
		customLevelText[CUSTOM_LEVEL_ITEMS] = "BACK";
		customLevelText[CUSTOM_LEVEL_ITEMS - 1] = filename;
	}
	

	strcat(filename, ".txt"); // Append file extension

	// Save the grid to the file
	ofstream outfile(filename);
	outfile << ncmax << '\n';
	if (outfile) {
		for (int i = 0; i < nl; i++) {
			for (int j = 0; j < ncmax; j++) {
				outfile << hartaloader[i][j] << " ";
			}
			outfile << endl;
		}
		outfile.close();
		outtextxy((x - textwidth("Map saved successfully!")) / 2, y - 7 * nwh, "Map saved successfully!");
	}
	else {
		setcolor(RED);
		outtextxy((x - textwidth("Error saving file.")) / 2, y - 7 * nwh, "Error saving6 file.");
	}
	delay(2000);
	setvisualpage(0);
	setactivepage(0);
}

void loadMap() {
	char filename[50] = ""; // Buffer for the file name
	int pos = 0;           // Current position in the filename buffer
	char ch;
	// Prompt user to enter filename
	setvisualpage(1);
	setactivepage(1);
	cleardevice();

	setcolor(WHITE);
	int fontSize = min(x / 20, y / 15); // Scale with window size
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, fontSize / 10); // Adjust text style
	
	char prompt[] = "Enter filename to load (without externsion):";
	int textWidth = textwidth(prompt);
	int textHeight = textheight(prompt);
	outtextxy((x - textWidth) / 2, (y - textHeight) / 2 - 20, prompt);

	while (true) {
		ch = getch();

		if (ch == 13) { // If ENTER is pressed
			break;
		}
		else if (ch == 8) { // If BACKSPACE is pressed
			if (pos > 0) {
				pos--;
				filename[pos] = '\0';

				// Clear and redraw the filename input
				setfillstyle(SOLID_FILL, BLACK);
				bar(50, y / 2, x - 50, y / 2 + 50); // Clear area
				outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
			}
		}
		else if (pos < 49 && (isalnum(ch) || ch == '_')) { // Allow alphanumeric and underscore
			filename[pos] = ch;
			filename[pos + 1] = '\0';
			pos++;

			// Display typed filename
			setfillstyle(SOLID_FILL, BLACK);
			bar(50, y / 2, x - 50, y / 2 + 50); // Clear area
			outtextxy((x - textwidth(filename)) / 2, y / 2, filename);
		}
	}

	strcat(filename, ".txt"); // Append file extension

	// Save the grid to the file
	ifstream infile(filename);
	infile >> ncmax;
	if (infile) {
		for (int i = 0; i < nl; i++) {
			for (int j = 0; j < ncmax; j++) {
				infile >> hartaloader[i][j];
			};
		}
		infile.close();
		outtextxy((x - textwidth("Map loaded successfully!")) / 2, y - 7*nwh, "Map loaded successfully!");
	}
	else {
		setcolor(RED);
		outtextxy((x - textwidth("Error loading file.")) / 2, y - 7*nwh, "Error loading file.");
	}
	delay(2000);
	cleardevice();
	setactivepage(0);
	InitialDrawing();
	setvisualpage(0);
}

void MapEditorLevels() {
	nwh = 0.7 * wh;
	ncfmap = nc1;
	InitialDrawing();
	cout << nc1 << endl;
	cout << ncimap << " " << ncfmap << endl;
	cout << mapi << " " << mapj << endl;
	while (true) {
		PutMovingImage(mapi, mapj);
		PutMapEditor(mapi, mapj, bkselect);
		SelectorImage(iselec);
		cout << mapi << mapj << '\n';
		char t = getch();
		if (t == 'm') saveMap();
		if (t == 'n') loadMap();
		if (t == 'c' && edit == 0) edit = 1;
		else {
			if(t=='c') edit = 0;
		}
		if (edit == 1) {
			cout << "Mapa este selectata pentru editare" << '\n';
			PutMovingImage(mapi, mapj);
			PutMapEditor(mapi, mapj, bkselect);
			if (t == 'w' && mapi> 0) {
				PutMovingImage(mapi, mapj);
				mapi--;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if (t == 'a' && mapj > ncimap) {
				PutMovingImage(mapi, mapj);
				mapj--;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if (t == 'd' && mapj < ncfmap-1) {
				PutMovingImage(mapi, mapj);
				mapj++;
				PutMapEditor(mapi, mapj, bkselect);
			}
			if (t == 's' && mapi < nl-1) {
				PutMovingImage(mapi, mapj);
				mapi++;
				cout << "Mapi: " << mapi << '\n';
				PutMapEditor(mapi, mapj, bkselect);
			}
			if ((int)t == 32) {
				if (bkselect == 11 && mapi > 7 && mapj < ncfmap-3) {
					if (ipole == -1 && jpole == -1) {
						hartaloader[mapi][mapj] = bkselect;
						ipole = mapi;
						jpole = mapj;
					}
					else {
						putimage((jpole - ncimap + 1) * nwh, (ipole + 1) * nwh, skyblockmap, COPY_PUT);
						hartaloader[ipole][jpole] = 0;
						hartaloader[mapi][mapj] = bkselect;
						ipole = mapi;
						jpole = mapj;
					}
					
				}
				if (bkselect != 6 && bkselect != 11) {
					hartaloader[mapi][mapj] = bkselect;
				}
			}
			if (t == 'j' && ncimap > 0) {
				panelnr--;
				ncimap =ncimap- nc1;
				ncfmap =ncfmap - nc1;
				mapi = 0;
				mapj = ncimap + 1;
				cout << ncimap << " " << ncfmap << '\n';
				cleardevice();
				MapPaneler();
			}
			if (t == 'l' && ncfmap < 1000) {
				panelnr++;
				ncimap = ncimap + nc1;
				ncfmap = ncfmap + nc1;
				mapi = 0;
				mapj = ncimap+1;
				cout << ncimap << " " << ncfmap << '\n';
				cleardevice();
				MapPaneler();
			}
			if(ncfmap>ncmax) ncmax = (int)ncfmap;
		}
		if (edit == 0) {
			cout << "Selectie blocks" << '\n';
			if (t == 'a' && iselec > 0) {
				SelectorImageMono(iselec);
				iselec--;
				SelectorImage(iselec);
			}
			if (t == 'd' && iselec < 13) {
				SelectorImageMono(iselec);
				iselec++;
				SelectorImage(iselec);
			}
			if ((int)t == 32) {
				bkselect = selecpoz[iselec];
				cout << bkselect << '\n';
				edit = 1;
			}

		}
		if (t == 'b') {
			CustomMenu();
		}
	}
	
}