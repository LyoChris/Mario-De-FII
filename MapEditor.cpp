#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
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

int hartaloader[30][1000], edit = 1, mapi = 0, mapj = 0, selecpoz[14] = { 1,0,3,4,0,0,0,8,7,2,5,9,11,6 }, iselec = 0;
float nwh, ncimap=0, ncfmap;


extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, *flagpolemapedit;
void* brickblockmap, * skyblockmap, * mario_vinemap, * mario_vine_topmap, * lucky_blockmap, * mario_coinmap, * mario_idle_rightmap, * one_upmap, * flagpolepmap, * gombamap;

void InitialDrawing() {
	cleardevice();
	for (int i = 0;i < nl;i+=1) {
		for (int j = 0;j < ncfmap; j+=1) {
			cout << i << " " << j << endl;
			hartaloader[i][j] = 0;
			putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, skyblockmap, COPY_PUT);
		}
	}

	putimage((3 + 0) * wh, 17 * wh, brickblock, COPY_PUT);
	putimage((3 + 1.5) * wh, 17 * wh, skyblock, COPY_PUT);
	putimage((3 + 3.0) * wh, 17 * wh, mario_vine, COPY_PUT);
	putimage((3 + 4.5) * wh, 17 * wh, mario_vine_top, COPY_PUT);
	putimage((3 + 6.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT); //placeholder pt pipe body
	putimage((3 + 7.5) * wh, 17 * wh, mario_climbing_down_1, COPY_PUT); //placeholder pt pipe head
	putimage((3 + 9.0) * wh, 17 * wh, lucky_block_used, COPY_PUT); //placeholder pt pirhana
	putimage((3 + 10.5) * wh, 17 * wh, lucky_block, COPY_PUT);
	putimage((3 + 12.0) * wh, 17 * wh, mario_coin, COPY_PUT);
	putimage((3 + 13.5) * wh, 17 * wh, one_up, COPY_PUT);
	putimage((3 + 15.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT);
	putimage((3 + 16.5) * wh, 17 * wh, mario_idle_right, COPY_PUT);
	putimage((3 + 18.0) * wh, 17 * wh, flagpolemapedit, COPY_PUT);

}

void PutMovingImage(int i, int j) {
	if (hartaloader[i][j] == 0)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, skyblockmap, COPY_PUT);
	if (hartaloader[i][j] == 1)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, brickblockmap, COPY_PUT);
	if (hartaloader[i][j] == 3)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_vinemap, COPY_PUT);
	if (hartaloader[i][j] == 4)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_vine_topmap, COPY_PUT);
	if (hartaloader[i][j] == 5)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, gombamap, COPY_PUT);
	if (hartaloader[i][j] == 9)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_idle_rightmap, COPY_PUT);
	if (hartaloader[i][j] == 8)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_blockmap, COPY_PUT);
	if (hartaloader[i][j] == 7)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_coinmap, COPY_PUT);
	if (hartaloader[i][j] == 13)
		//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_block_used, COPY_PUT); // placeholder pt pirhana
	if (hartaloader[i][j] == 14)
		//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_block, COPY_PUT); // placeholder pt pipehead
	if (hartaloader[i][j] == 12)
		//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, one_upmap, COPY_PUT); // placeholder pt pipebody
	if (hartaloader[i][j] == 2)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, one_upmap, COPY_PUT);
	if (hartaloader[i][j] == 11)
		putimage((j - ncimap + 3) * nwh, (i + 2 - 7) * nwh, flagpolepmap, COPY_PUT);
}

void PutMapEditor(int i, int j, int block) {
	if (block == 0)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, skyblockmap, COPY_PUT);
	if (block == 1)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, brickblockmap, COPY_PUT);
	if (block == 3)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_vinemap, COPY_PUT);
	if (block == 4)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_vine_topmap, COPY_PUT);
	if (block == 5)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, gombamap, COPY_PUT);
	if (block == 9)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_idle_rightmap, COPY_PUT);
	if (block == 8)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_blockmap, COPY_PUT);
	if (block == 7)
		putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, mario_coinmap, COPY_PUT);
	if (block == 13)
		//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_block_used, COPY_PUT); // placeholder pt pirhana
		if (block == 14)
			//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, lucky_block, COPY_PUT); // placeholder pt pipehead
			if (block == 12)
				//putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, one_upmap, COPY_PUT); // placeholder pt pipebody
				if (block == 2)
					putimage((j - ncimap + 3) * nwh, (i + 2) * nwh, one_upmap, COPY_PUT);
	if (block == 11)
		putimage((j - ncimap + 3) * nwh, (i + 2 - 7) * nwh, flagpolepmap, COPY_PUT);
}

void SelectorImage(int i){
	if (selecpoz[i] == 1) putimage((3 + 0) * wh, 17 * wh, brickblock, COPY_PUT);
	if (selecpoz[i] == 0) putimage((3 + 1.5) * wh, 17 * wh, skyblock, COPY_PUT);
	if (selecpoz[i] == 3)putimage((3 + 3.0) * wh, 17 * wh, mario_vine, COPY_PUT);
	if (selecpoz[i] == 4)putimage((3 + 4.5) * wh, 17 * wh, mario_vine_top, COPY_PUT);
	if (selecpoz[i] == 14)putimage((3 + 6.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT); //placeholder pt pipe body
	if (selecpoz[i] == 12)putimage((3 + 7.5) * wh, 17 * wh, mario_climbing_down_1, COPY_PUT); //placeholder pt pipe head
	if (selecpoz[i] == 13)putimage((3 + 9.0) * wh, 17 * wh, lucky_block_used, COPY_PUT); //placeholder pt pirhana
	if (selecpoz[i] == 8)putimage((3 + 10.5) * wh, 17 * wh, lucky_block, COPY_PUT);
	if (selecpoz[i] == 7)putimage((3 + 12.0) * wh, 17 * wh, mario_coin, COPY_PUT);
	if (selecpoz[i] == 2)putimage((3 + 13.5) * wh, 17 * wh, one_up, COPY_PUT);
	if (selecpoz[i] == 5)putimage((3 + 15.0) * wh, 17 * wh, goomba_walking_1, COPY_PUT);
	if (selecpoz[i] == 9)putimage((3 + 16.5) * wh, 17 * wh, mario_idle_right, COPY_PUT);
	if (selecpoz[i] == 11)putimage((3 + 18.0) * wh, 17 * wh, flagpolemapedit, COPY_PUT);
}


void MapEditorLevels() {
	nwh = 0.7 * wh;
	ncfmap = nc1;
	InitialDrawing();
	cout << mapi << " " << mapj << endl;
	while (true) {
		char t = getch();
		if (t == 'c' && edit == 0) edit = 1;
		else {
			if(t=='c') edit = 0;
		}
		if (edit == 1) {
			cout << "Mapa este selectata pentru editare" << '\n';
			PutMovingImage(mapi, mapj);
			putimage((mapj - ncimap + 3) * nwh, (mapi + 2) * nwh, brickblockmap, COPY_PUT);
			if (t == 'w' && mapi>ncimap) {
				PutMovingImage(mapi, mapj);
				mapi--;
				putimage((mapj - ncimap + 3) * nwh, (mapi + 2) * nwh, brickblockmap, COPY_PUT);
				cout << "Mapi: " << mapi << '\n';
			}
			if (t == 'a' && mapj > ncimap) {
				PutMovingImage(mapi, mapj);
				mapj--;
				cout << "Mapj: " << mapj << '\n';
				putimage((mapj - ncimap + 3) * nwh, (mapi + 2) * nwh, brickblockmap, COPY_PUT);
			}
			if (t == 'd' && mapj < ncfmap-1) {
				PutMovingImage(mapi, mapj);
				mapj++;
				cout << "Mapj: " << mapj << '\n';
				putimage((mapj - ncimap + 3) * nwh, (mapi + 2) * nwh, brickblockmap, COPY_PUT);
			}
			if (t == 's' && mapi < nl-1) {
				PutMovingImage(mapi, mapj);
				mapi++;
				cout << "Mapi: " << mapi << '\n';
				putimage((mapj - ncimap + 3) * nwh, (mapi + 2) * nwh, brickblockmap, COPY_PUT);
			}
		}
		if (edit == 0) {
			cout << "Selectie blocks" << '\n';
			if (t == 'a' && iselec > 0) {
				SelectorImage(iselec);
				iselec--;
			}
			if (t == 'd' && iselec < 13) {
				SelectorImage(iselec);
				iselec++;
			}

		}
		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			exit(0);
			closegraph();
		}
	}
	
}