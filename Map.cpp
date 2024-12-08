#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
using namespace std;

string chg = "level1.txt";
string cht = "level2.txt";
ifstream f(chg);

float wh, nc1;
int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario;

void MapReaderandSetter() {
    f >> nl >> nc;
    for (int i = 0; i < nl;i++) {
        for (int j = 0;j < nc;j++) {
            f >> harta[i][j];
        }
    }
    x = GetSystemMetrics(SM_CXSCREEN);
    y = GetSystemMetrics(SM_CYSCREEN);
    wh = (float)y / (float)nl;
    nc1 = (float)x / wh;
}

void MapLoader() {
    initwindow(x, y, "", -3, -3);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = mv2;j < nc1 + mv2; j += 1) {
            //if(harta[i][j]==0)
              //readimagefile("SkyBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 3)
                readimagefile("mario_vine.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 4)
                readimagefile("mario_vine_top.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 9) {
                readimagefile("mario_idle_right.gif", (j - mv2) * (wh), i * (wh), (j + 1 - mv2) * (wh), (i + 1) * (wh));
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
        }
    }
}

void MapLoader2() {
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = mv2;j < nc1 + mv2; j += 1) {
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 3)
                readimagefile("mario_vine.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 4)
                readimagefile("mario_vine_top.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 9) {
                readimagefile("mario_idle_right.gif", (j - mv2) * (wh), i * (wh), (j + 1 - mv2) * (wh), (i + 1) * (wh));
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
        }
    }
}