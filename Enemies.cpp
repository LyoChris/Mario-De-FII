#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
using namespace std;

goompa gompav[100];
pirhana piranav[100];
extern colectible coins[100];

ofstream gout("testing.txt");
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, *skyblock;

extern float nci, ncf, nc1;
extern int harta[30][1000], coino;
int n = 0, hoverg = 0, p = 0;
extern float wh;

void gompastateput(int a) {
	switch (gompav[a].gstage) {
	case 1:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_1, COPY_PUT); break;
		//readimagefile("goomba_walking_1.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
	case 2:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_2, COPY_PUT); break;
		//readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
	case -1:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_1, COPY_PUT); break;
		//readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
	case -2:
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, goomba_walking_2, COPY_PUT); break;
		//readimagefile("goomba_walking_1.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);break;
	}
}

void gompastateread(int a) {
	switch (gompav[a].gstage) {
		case 1:
			readimagefile("goomba_walking_1.gif", (gompav[a].jgompa- nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa -nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case 2:
			readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case -1:
			readimagefile("goomba_walking_2.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh); break;
		case -2:
			readimagefile("goomba_walking_1.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);break;
	}
}

void gompa(int a) {
	float w = 0;
	if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 1 || gompav[a].jgompa + 1 > ncf) gompav[a].gdirection = 1;
	if ((harta[(int)gompav[a].igompa][(int)gompav[a].jgompa - 1] == 1 && gompav[a].jgompa - (int)gompav[a].jgompa == 0) || gompav[a].jgompa - 1 < 0) gompav[a].gdirection = 0;
	if (gompav[a].gdirection == 1) {
		hoverg = 0;
		if (gompav[a].gstage < 0) gompav[a].gstage = 0;
		gompav[a].gstage++;
		if (gompav[a].gstage > 2) gompav[a].gstage = 1;
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, skyblock, COPY_PUT);
		//readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa -nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1 -nci) * wh, gompav[a].igompa * wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[i].icolec, coins[i].jcolec)) {
					hoverg = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		//cout << hoverg << '\n';
		if (hoverg == 1) {
			if (gompav[a].jgompa > 0 && harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] != 1) {
				gompav[a].jgompa -= 0.5;
				gompastateread(a);
			}
		}
		else {
			if (gompav[a].jgompa > 0 && harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] != 1) {
				gompav[a].jgompa -= 0.5;
				gompastateput(a);
			}
		}
		hoverg = 0;
	}
	hoverg = 0;
	if (gompav[a].gdirection == 0) {
		hoverg = 0;
		if (gompav[a].gstage > 0) gompav[a].gstage = 0;
		gompav[a].gstage--;
		if (gompav[a].gstage < -2) gompav[a].gstage = -1;
		putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, skyblock, COPY_PUT);
		//readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa +1 - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa + 1- nci) * wh, gompav[a].igompa * wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				hoverg = 1;
				putimage((gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				hoverg = 1;
				putimage(((int)gompav[a].jgompa - nci)* wh, gompav[a].igompa* wh, mario_coin, COPY_PUT);
				//readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[i].icolec, coins[i].jcolec)) {
					hoverg = 1;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		//cout << hoverg << '\n';
		if (hoverg == 1) {
			if (gompav[a].jgompa < ncf) {
				gompav[a].jgompa += 0.5;
				gompastateread(a);
			}
		}
		else {
			if (gompav[a].jgompa < ncf) {
				gompav[a].jgompa += 0.5;
				gompastateput(a);
			}
		}
		hoverg = 0;
	}
	hoverg = 0;
}

void pirhanastate(int a) {
	switch (piranav[a].pstage) {
		case 1:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, mario_climbing_down_1, COPY_PUT); break;	
		case 2:
			putimage((piranav[a].jpirana - nci) * wh, piranav[a].ipirana * wh, mario_climbing_down_2, COPY_PUT); break;
	}
}

void EnemiesMoving() {
	for (int i = 1;i <= n;i++) {
		if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
			gompa(i);
		}
	}
}
