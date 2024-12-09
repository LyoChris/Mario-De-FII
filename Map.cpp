#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <thread>
#include "Enemies.h"
using namespace std;

string chg = "level1.txt";
string cht = "level2.txt";
ifstream f(chg);


/*9
    thread map_thread(MapLoader(), a);
    map_thread.join();
*/

float wh, nc1;
int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario;
extern goompa gompav[100];
extern int n;

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

void MapLoader(int a) {
    initwindow(x, y, "", -3, -3);
    int ow = getcurrentwindow();
    setbkcolor(RGB(0, 0, 0));
    initwindow(x, y, "", -3, -3);
    int on = getcurrentwindow();
    setcurrentwindow(ow);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = mv2;j < nc1 + mv2; j += 1) {
            //if(harta[i][j]==0)
              //readimagefile("SkyBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 3 )
                readimagefile("mario_vine.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 4 )
                readimagefile("mario_vine_top.gif", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 9) {
                readimagefile("mario_idle_right.gif", (j - mv2) * (wh), i * (wh), (j + 1 - mv2) * (wh), (i + 1) * (wh));
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
            if (harta[i][j] == 5) {
                readimagefile("goomba_walking_1.gif", gompav[a].jgompa * wh, gompav[a].igompa * wh, (gompav[a].jgompa + 1) * wh, (gompav[a].igompa + 1) * wh);
                n++;
                gompav[n].igompa = i;
                gompav[n].jgompa = j;
                harta[i][j] = 0;
            }
        }
    }
    setcurrentwindow(ow);
    closegraph(on);
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