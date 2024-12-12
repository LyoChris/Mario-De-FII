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
#include "Map.h"
#include "Colectibles.h"
using namespace std;

string chg = "level1.txt";
string cht = "level2.txt";
ifstream f(chg);


/*9
    thread map_thread(MapLoader(), a);
    map_thread.join();
*/
extern colectible coins[100];
pozitii spawn[100];
float wh, ncf, nci = 0, nc1;
int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario, mappart, spawncount = 1;
extern goompa gompav[100];
extern int n, coino;

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
    ncf = nc1;
}

void MapLoader() {
    initwindow(x, y, "", -3, -3);
    int ow = getcurrentwindow();
    setbkcolor(RGB(0, 0, 0));
    initwindow(x, y, "", -3, -3);
    int on = getcurrentwindow();
    setcurrentwindow(ow);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0; i < nl;i += 1) {
        for (int j = nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", j * wh, i * wh, (j + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 3 )
                readimagefile("mario_vine.gif", j * wh, i * wh, (j + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 4 )
                readimagefile("mario_vine_top.gif", j * wh, i * wh, (j + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 9) {
                readimagefile("mario_idle_right.gif", j * (wh), i * (wh), (j + 1) * (wh), (i + 1) * (wh));
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
            if (harta[i][j] == 6) {
                if (spawn[(int)(nci/nc1)].ibegin == 0 && spawn[(int)(nci / nc1)].jbegin == 0) {
                    spawn[(int)(nci / nc1)].ibegin = i;
                    spawn[(int)(nci / nc1)].jbegin = j;
                }
                else {
                    spawn[(int)(nci / nc1)].jfinal = j;
                    spawn[(int)(nci / nc1)].ifinal = i;
                    
                }
            }
            if (harta[i][j] == 7) {
                //readimagefile("", j * wh, i * wh, (j + 1) * wh, (i + 1) * wh);
                bar(j * wh, i * wh, (j + 1) * wh, (i + 1) * wh);
                coino++;
                coins[coino].icolec = i;
                coins[coino].jcolec = j;
                coins[coino].mapart = (int)(nci - nc1);
            }
            if (harta[i][j] == 5) {
                n++;
                gompav[n].mapart = (int)(nci-nc1);
                gompav[n].igompa = i;
                gompav[n].jgompa = j;
                harta[i][j] = 0;
                readimagefile("goomba_walking_1.gif", gompav[n].jgompa * wh, gompav[n].igompa * wh, (gompav[n].jgompa + 1) * wh, (gompav[n].igompa + 1) * wh);
            }
        }
       
        readimagefile("SkyBlock.jpg", 0, 0, wh, wh);
    }
    cout << spawn[(int)(nci / nc1)].ibegin << " " << spawn[(int)(nci / nc1)].jbegin << '\n' << spawn[(int)(nci / nc1)].ifinal << " " << spawn[(int)(nci / nc1)].jfinal;
    setcurrentwindow(ow);
    closegraph(on);
}

void MapLoader2() {
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = nci;j < ncf; j += 1) {
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

void MapLoaderNextRight() {
    nci = nci + nc1;
    ncf = ncf + nc1;
    int ow = getcurrentwindow();
    setbkcolor(RGB(0, 0, 0));
    initwindow(x, y, "", -3, -3);
    int on = getcurrentwindow();
    setcurrentwindow(ow);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 3)
                readimagefile("mario_vine.gif", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 4)
                readimagefile("mario_vine_top.gif", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 6) {
                if (spawn[(int)(nci / nc1)].ibegin == 0 && spawn[(int)(nci / nc1)].jbegin == 0) {
                    spawn[(int)(nci / nc1)].ibegin = i;
                    spawn[(int)(nci / nc1)].jbegin = j;
                }
                else {
                    spawn[(int)(nci / nc1)].jfinal = j;
                    spawn[(int)(nci / nc1)].ifinal = i;

                }
            }
            if (harta[i][j] == 5) {
                n++;
                gompav[n].mapart = nci - nc1;
                gompav[n].igompa = i;
                gompav[n].jgompa = j;
                readimagefile("goomba_walking_1.gif", gompav[n].jgompa * wh, gompav[n].igompa * wh, (gompav[n].jgompa + 1) * wh, (gompav[n].igompa + 1) * wh);
                harta[i][j] = 0;
            }
        }
        imario = spawn[(int)(nci / nc1)].ibegin;
        jmario = spawn[(int)(nci / nc1)].jbegin;
        readimagefile("mario_idle_left.gif", (spawn[(int)(nci / nc1)].jbegin - nci) * wh, spawn[(int)(nci / nc1)].ibegin * wh, (spawn[(int)(nci / nc1)].jbegin - nci + 1) * wh, (spawn[(int)(nci / nc1)].ibegin + 1) * wh);
    }
    setcurrentwindow(ow);
    closegraph(on);
}

void MapLoaderPrevLeft() {
    nci = nci - nc1;
    ncf = ncf - nc1;
    int ow = getcurrentwindow();
    setbkcolor(RGB(0, 0, 0));
    initwindow(x, y, "", -3, -3);
    int on = getcurrentwindow();
    setcurrentwindow(ow);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 3)
                readimagefile("mario_vine.gif", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            if (harta[i][j] == 4)
                readimagefile("mario_vine_top.gif", (j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
            
        }
        imario = spawn[(int)(nci / nc1)].ifinal;
        jmario = spawn[(int)(nci / nc1)].jfinal;
        readimagefile("mario_idle_left.gif", (spawn[(int)(nci / nc1)].jfinal - nci) * wh, spawn[(int)(nci / nc1)].ifinal * wh, (spawn[(int)(nci / nc1)].jfinal - nci + 1) * wh, (spawn[(int)(nci / nc1)].ifinal + 1) * wh);
    }
    setcurrentwindow(ow);
    closegraph(on);
}