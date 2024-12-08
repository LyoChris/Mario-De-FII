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

extern int harta[30][1000];
int n = 0, gstage = 1, gdirection = 1;
extern float wh;

void gompastate() {
	switch (gstage) {
		case 1:

		case 2:

		case 3:

		case -1:

		case -2:

		case -3:

	break;
	}
}

void gompa(int a) {
	if (gompav[a].jgompa + 1 == 1) gdirection = 0;
	if (gompav[a].jgompa - 1 == 1) gdirection = 1;
	if (gdirection == 1) {
		if (gstage < 0) gstage = -gstage;
		gstage++;
		if (gstage > 3) gstage = 1;
		readimagefile("mario_vine.gif", gompav[a].jgompa * wh, gompav[a].igompa * wh, (gompav[a].jgompa + 1) * wh, (gompav[a].igompa + 1) * wh);
		if (gompav[a].jgompa > 0 /* && harta[gompav[a].igompa][gompav[a].jgompa - 1] != 1 */ ) {
			gompav[a].jgompa--;
			bar(gompav[a].jgompa * wh, gompav[a].igompa * wh, (gompav[a].jgompa + 1) * wh, (gompav[a].igompa + 1) * wh);
		}
		std::cout << gstage << " ";

	}
}