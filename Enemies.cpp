#include "graphics.h"
//#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"

goompa gompav[100];

extern float nci, ncf, nc1;
extern int harta[30][1000];
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
	float w=0;
	if (harta[gompav[a].igompa][gompav[a].jgompa + 1] == 1 || gompav[a].jgompa + 1 > ncf) gompav[a].gdirection = 1;
	if (harta[gompav[a].igompa][gompav[a].jgompa - 1] == 1 || gompav[a].jgompa - 1 < 0) gompav[a].gdirection = 0;
	if (gompav[a].gdirection == 1) {
		if (gompav[a].gstage < 0) gompav[a].gstage = 0;
		gompav[a].gstage++;
		if (gompav[a].gstage > 2) gompav[a].gstage = 1;
		readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (harta[gompav[a].igompa][gompav[a].jgompa] == 3) {
			readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		}
		if (gompav[a].jgompa > 0 && harta[gompav[a].igompa][gompav[a].jgompa - 1] != 1) {
			gompav[a].jgompa--;
			gompastate(a);
		}
	}
	if (gompav[a].gdirection == 0) {
		if (gompav[a].gstage > 0) gompav[a].gstage = 0;
		gompav[a].gstage--;
		if (gompav[a].gstage < -2) gompav[a].gstage = -1;
		readimagefile("SkyBlock.jpg", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (harta[gompav[a].igompa][gompav[a].jgompa] == 3) {
			readimagefile("mario_vine.gif", (gompav[a].jgompa- nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
		}
		if (gompav[a].jgompa < ncf) {
			gompav[a].jgompa++;
			gompastate(a);
		}
	}
}

void EnemiesMoving() {
	for (int i = 1;i <= n;i++) {
		if (gompav[i].mapart == (int)(nci - nc1)) {
			gompa(i);
		}
	}
}
