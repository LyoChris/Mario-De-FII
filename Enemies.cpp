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
extern colectible coins[100];

ofstream gout("testing.txt");

extern float nci, ncf, nc1;
extern int harta[30][1000], coino;
int n = 0;
extern float wh;

void gompastate(int a) {
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
		if (gompav[a].gstage < 0) gompav[a].gstage = 0;
		gompav[a].gstage++;
		if (gompav[a].gstage > 2) gompav[a].gstage = 1;
		readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[i].icolec, coins[i].jcolec)) {
					readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		if (gompav[a].jgompa > 0 && harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] != 1) {
			gompav[a].jgompa -= 0.5;
			gompastate(a);
		}
	}
	if (gompav[a].gdirection == 0) {
		
		if (gompav[a].gstage > 0) gompav[a].gstage = 0;
		gompav[a].gstage--;
		if (gompav[a].gstage < -2) gompav[a].gstage = -1;
		readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (gompav[a].jgompa - (int)gompav[a].jgompa != 0) {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 3) {
				readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa + 1] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 3) {
				readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)gompav[a].igompa][(int)gompav[a].jgompa] == 7) {
				readimagefile("mario_coin.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino/2;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == gompav[a].igompa && coins[i].colected == 0) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[i].icolec, coins[i].jcolec)) {
					readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
			if (coins[coino-i].mapart == (int)(nci - nc1) && coins[coino-i].icolec == gompav[a].igompa && coins[coino-i].colected == 0) {
				if (CheckBlock(gompav[a].igompa, gompav[a].jgompa, wh, coins[coino - i].icolec, coins[coino - i].jcolec)) {
					readimagefile("mario_coin.gif", (coins[coino - i].jcolec - nci) * wh, coins[coino - i].icolec * wh, ((coins[coino - i].jcolec - nci) + 1) * wh, (coins[coino - i].icolec + 1) * wh);
				}
			}
		}
		if (gompav[a].jgompa < ncf) {
			gompav[a].jgompa += 0.5;
			gompastate(a);
		}
	}
}

void EnemiesMoving() {
	for (int i = 1;i <= n;i++) {
		if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
			gompa(i);
		}
	}
}
