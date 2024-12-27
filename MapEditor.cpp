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
#include "miniaudio.h"
using namespace std;

extern float wh, nci, ncf, nc1, nci;
extern int x, y, nl;

struct spawnpoint {
	int i1 = 0, j1 = 0;
	int i2 = 0, j2 = 0;

}spawn[100];

int hartaloader[30][1000] = { 0 }, nr=0, edit = 1, mapi = 0, mapj = 1, selecpoz[14] = { 1,0,3,4,12,13,14,8,7,2,5,9,11,6 }, iselec = 0, bkselect = 1, panelnr = 0, ncmax = 0, jpole = -1, ipole = -1;
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
	if (iselec == 0) putimage((3 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	if (iselec == 1) putimage((3 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	if (iselec == 2)putimage((3 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	if (iselec == 3)putimage((3 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	if (iselec == 4)putimage((3 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((3 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((3 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((3 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	if (iselec == 8)putimage((3 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	if (iselec == 9)putimage((3 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	if (iselec == 10)putimage((3 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	if (iselec == 11)putimage((3 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	if (iselec == 12)putimage((3 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);
}

void SelectorImage(int i) {
	if (iselec == 0) putimage((3 + 0) * wh, 17 * wh, brickblock, COPY_PUT);
	if (iselec == 1) putimage((3 + 1.5) * wh, 17 * wh, skyblock, COPY_PUT);
	if (iselec == 2)putimage((3 + 3.0) * wh, 17 * wh, mario_vine, COPY_PUT);
	if (iselec == 3)putimage((3 + 4.5) * wh, 17 * wh, mario_vine_top, COPY_PUT);
	if (iselec == 4)putimage((3 + 6.0) * wh, 17 * wh, pipebody, COPY_PUT); //placeholder pt pipe body
	if (iselec == 5)putimage((3 + 7.5) * wh, 17 * wh, pipeheadpir, COPY_PUT); //placeholder pt pirhana
	if (iselec == 6)putimage((3 + 9.0) * wh, 17 * wh, pipehead, COPY_PUT); //placeholder pt pipe head
	if (iselec == 7)putimage((3 + 10.5) * wh, 17 * wh, lucky_block, COPY_PUT);
	if (iselec == 8)putimage((3 + 12.0) * wh, 17 * wh, mario_coin, COPY_PUT);
	if (iselec == 9)putimage((3 + 13.5) * wh, 17 * wh, one_up, COPY_PUT);
	if (iselec == 10)putimage((3 + 15.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT);
	if (iselec == 11)putimage((3 + 16.5) * wh, 17 * wh, mario_idle_right, COPY_PUT);
	if (iselec == 11)putimage((3 + 18.0) * wh, 17 * wh, flagpolemapedit, COPY_PUT);
}

void MapPaneler() {
	for (int i = 0;i < nl;i += 1) {
		for (int j = (int)ncimap;j < ncfmap; j += 1) {
			PutMovingImage(i, j);
		}
	}
	putimage((3 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	putimage((3 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((3 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((3 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((3 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	putimage((3 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	putimage((3 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	putimage((3 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((3 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((3 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((3 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((3 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((3 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

	SelectorImage(iselec);
}

void InitialDrawing() {
	cleardevice();
	for (int i = 0;i < nl;i += 1) {
		for (int j = (int)ncimap;j < ncfmap; j += 1) {
			cout << i << " " << j << endl;
			PutMovingImage(i, j);
		}
	}

	putimage((3 + 0) * wh, 17 * wh, brickblockmono, COPY_PUT);
	putimage((3 + 1.5) * wh, 17 * wh, skyblockmono, COPY_PUT);
	putimage((3 + 3.0) * wh, 17 * wh, mario_vinemono, COPY_PUT);
	putimage((3 + 4.5) * wh, 17 * wh, mario_vine_topmono, COPY_PUT);
	putimage((3 + 6.0) * wh, 17 * wh, pipebodymono, COPY_PUT); //placeholder pt pipe body
	putimage((3 + 7.5) * wh, 17 * wh, pipeheadpirmono, COPY_PUT); //placeholder pt pirhana
	putimage((3 + 9.0) * wh, 17 * wh, pipeheadmono, COPY_PUT); //placeholder pt pipe head
	putimage((3 + 10.5) * wh, 17 * wh, lucky_blockmono, COPY_PUT);
	putimage((3 + 12.0) * wh, 17 * wh, mario_coinmono, COPY_PUT);
	putimage((3 + 13.5) * wh, 17 * wh, one_upmono, COPY_PUT);
	putimage((3 + 15.0) * wh, 17 * wh, gombamono, COPY_PUT);
	putimage((3 + 16.5) * wh, 17 * wh, mario_idle_rightmono, COPY_PUT);
	putimage((3 + 18.0) * wh, 17 * wh, flagpolemapeditmono, COPY_PUT);

}

void saveMap() {
	char filename[50] = ""; // Buffer for the file name
	int pos = 0;           // Current position in the filename buffer
	char ch;

	// Prompt user to enter filename
	setvisualpage(1);
	setactivepage(1);

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
	cleardevice();
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
				if (bkselect == 6 && mapj < ncfmap - 1 && mapj> ncimap + 1) {
					if ((spawn[panelnr].i1 == 0 && spawn[panelnr].j1 == 0)) {
							hartaloader[mapi][mapj] = bkselect;
							spawn[panelnr].i1 = mapi;
							spawn[panelnr].j1 = mapj;
					}
					else {
						if ((spawn[panelnr].i2 == 0 && spawn[panelnr].j2 == 0)) {
							hartaloader[mapi][mapj] = bkselect;
							spawn[panelnr].i2 = mapi;
							spawn[panelnr].j2 = mapj;
						}
						else {
							putimage((spawn[panelnr].j2 - ncimap + 1) * nwh, (spawn[panelnr].i2 + 1) * nwh, skyblockmap, COPY_PUT);
							hartaloader[spawn[panelnr].i2][spawn[panelnr].j2] = 0;
							hartaloader[mapi][mapj] = bkselect;
							spawn[panelnr].i2 = mapi;
							spawn[panelnr].j2 = mapj;
						}
					}
					
				}
				if (bkselect == 11 && mapi > 7) {
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
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			exit(0);
			closegraph();
		}
	}
	
}