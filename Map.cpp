#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <thread>
#include <string>
#include <mmsystem.h>
#include "Enemies.h"
#include "Map.h"
#include "Colectibles.h"
#include "Loader.h"
#include "Sounds.h"
#include "MapEditor.h"
using namespace std;


string cht,  levelselect;

void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, * one_up, * flagpolep, * flagpolemapedit, * pipebody,
* mario_star, * pipehead, * pirana_1, * pirana_2, * pipeheadpir, * mariostar, * mario_climbing_down_1_star, * mario_climbing_down_2_star, * mario_climbing_up_1_star,
* mario_climbing_up_2_star, * mario_idle_left_star, * mario_idle_right_star, * mario_jump_1_star, * mario_left_run_1_star, * mario_left_run_2_star,
* mario_left_run_3_star, * mario_right_run_1_star, * mario_right_run_2_star, * mario_right_run_3_star;

extern pirhana piranav[100];
extern colectible coins[100], life[100], starpow[100];
pozitii spawn[100];
float wh, ncf, nci = 0, nc1, imario, jmario;
int  x, y, nl = 20, nc, harta[30][1000], mv2, map, mappart, spawncount = 1, vizc[100], vize[100], buffersize, flagpole = 00;
extern goompa gompav[100];
extern int n, coino, lifo, p, staro;



void MapReaderandSetter() {
    x = GetSystemMetrics(SM_CXSCREEN); //1536 864
    y = GetSystemMetrics(SM_CYSCREEN);
    wh = (float)y / (float)nl;
    nc1 = (float)x / wh;
    ncf = nc1;
	cout << "Dimensiuni ecran: " << x << " " << y << '\n';
	AssetLoader();
	AssetLoaderMap();
	initwindow(x, y, "", -3, -3);
}

void MapLoader() {
    ifstream f(cht);
    f >> nc;
    for (int i = 0; i < nl;i++) {
        for (int j = 0;j < nc;j++) {
            f >> harta[i][j];
        }
    }
    levelselect = cht;
    //initwindow(x, y, "", -3, -3);
	setvisualpage(1);
    setactivepage(0);
	cleardevice();
    setbkcolor(RGB(126, 132, 246));
	cleardevice();
    for (int i = 0; i < nl;i += 1) {
        for (int j = nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                putimage(j * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
                putimage(j * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
                putimage(j * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 9) {
				putimage(j * wh, i * wh, mario_idle_right, COPY_PUT);
				cout << "Mario coord init: "<< i << " " << j << '\n';
                imario = i, jmario = j;
                harta[i][j] = 0;
            }
            if (harta[i][j] == 6) {
                if (spawn[(int)(nci / nc1)].ibegin == 0 && spawn[(int)(nci / nc1)].jbegin == 0) {
                    spawn[(int)(nci / nc1)].ibegin = i;
                    spawn[(int)(nci / nc1)].jbegin = j;
                }
                else {
                    spawn[(int)(nci / nc1)].jfinal = j;
                    spawn[(int)(nci / nc1)].ifinal = i;

                }
                harta[i][j] = 0;
            }
            if (harta[i][j] == 7) {
					putimage(j * wh, i * wh, mario_coin, COPY_PUT);   
                    coino++;
                    coins[coino].icolec = i;
                    coins[coino].jcolec = j;
                    coins[coino].mapart = (int)(nci - nc1);
                    harta[i][j] = 0;
            }
            if (harta[i][j] == 15) {
				putimage(j * wh, i * wh, mario_star, COPY_PUT);
                staro++;
                starpow[staro].icolec = i;
                starpow[staro].jcolec = j;
                starpow[staro].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 8) {
				putimage(j * wh, i * wh, lucky_block, COPY_PUT); 
            }
            if (harta[i][j] == 10) {
				putimage(j * wh, i * wh, lucky_block_used, COPY_PUT);
            }
            if (harta[i][j] == 2) {
				putimage(j * wh, i * wh, one_up, COPY_PUT);
                lifo++;
                life[lifo].icolec = i;
				life[lifo].jcolec = j;
				life[lifo].mapart = (int)(nci - nc1);
				harta[i][j] = 0;

            }
            if (harta[i][j] == 11) {
                flagpole = j;
				putimage(j * wh, (i-7) * wh, flagpolep, COPY_PUT);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 12) {
                putimage(j * wh, i * wh, pipebody, COPY_PUT);
                //bar(j * wh, i * wh, (j + 1) * wh, (i + 1) * wh); // placeholder pentru pipe body
            }
            if(harta[i][j] == 14) {
                putimage(j * wh, i * wh, pipehead, COPY_PUT);
                //bar(j * wh, i * wh, (j + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head without pirhana
            }
            if (harta[i][j] == 13) {
                putimage(j * wh, i * wh, pipehead, COPY_PUT);
                //bar(j * wh, i * wh, (j + 0.5) * wh, (i + 1) * wh); // placeholder pentru pipe head with pirhana
                p++;
				piranav[p].ipinit = i;
				piranav[p].jpinit = j;
                piranav[p].ipirana = i;
                piranav[p].jpirana = j;
				piranav[p].mapart = (int)(nci - nc1);
            }
            if (harta[i][j] == 5) {
                    n++;
                    gompav[n].mapart = (int)(nci - nc1);
                    gompav[n].igompa = i;
                    gompav[n].jgompa = j;
                    harta[i][j] = 0;
                    cout << "Map Tester:" << n << " " << gompav[n].mapart << " " << gompav[n].igompa << " " << gompav[n].jgompa << '\n';
					putimage(j * wh, i * wh, goomba_walking_1, COPY_PUT);
                    harta[i][j] == 0;
            }
        }
		putimage(0, 0, skyblock, COPY_PUT);
    }
	setvisualpage(0);
}

void MapLoaderNextRight() {
    nci = nci + nc1;
    ncf = ncf + nc1;
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
				putimage((j - nci) * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
				putimage((j - nci) * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
				putimage((j - nci) * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 6) {
                if (spawn[(int)(nci / nc1)].ibegin == 0 && spawn[(int)(nci / nc1)].jbegin == 0) {
                    spawn[(int)(nci / nc1)].ibegin = i;
                    spawn[(int)(nci / nc1)].jbegin = j;
                }
                else {
                    spawn[(int)(nci / nc1)].jfinal = j;
                    spawn[(int)(nci / nc1)].ifinal = i;

                }
                harta[i][j] = 0;
            }
            if (harta[i][j] == 8) {
                putimage((j - nci) * wh, i * wh, lucky_block, COPY_PUT);
            }
            if (harta[i][j] == 10) {
                putimage((j - nci) * wh, i * wh, lucky_block_used, COPY_PUT);
            }
            if (harta[i][j] == 5) {
                n++;
                gompav[n].mapart = (int)(nci - nc1);
                gompav[n].igompa = i;
                gompav[n].jgompa = j;
                cout << "Map Tester:" << n << " " << gompav[n].mapart << " " << gompav[n].igompa << " " << gompav[n].jgompa << '\n';
                putimage((j - nci) * wh, i * wh, goomba_walking_1, COPY_PUT);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 11) {
                flagpole = j;
                putimage((j - nci) * wh, (i-6) * wh, flagpolep, COPY_PUT);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 12) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe body
            }
            if (harta[i][j] == 14) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head without pirhana
            }
            if (harta[i][j] == 13) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head with pirhana
                p++;
                piranav[p].ipinit = i;
                piranav[p].jpinit = j;
                piranav[p].ipirana = i;
                piranav[p].jpirana = j;
                piranav[p].mapart = (int)(nci - nc1);
            }
            if (harta[i][j] == 7) {
                putimage((j - nci) * wh, i * wh, mario_coin, COPY_PUT);
                coino++;
                coins[coino].icolec = i;
                coins[coino].jcolec = j;
                coins[coino].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
            if (harta[i][j] == 15) {
				setcolor(YELLOW);
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh);
                staro++;
                starpow[staro].icolec = i;
                starpow[staro].jcolec = j;
                starpow[staro].mapart = (int)(nci - nc1);
                harta[i][j] = 0;
            }
        }
        imario = spawn[(int)(nci / nc1)].ibegin;
        jmario = spawn[(int)(nci / nc1)].jbegin;
		putimage((spawn[(int)(nci / nc1)].jbegin - nci) * wh, spawn[(int)(nci / nc1)].ibegin * wh, mario_idle_right, COPY_PUT);
    }
    setvisualpage(0);
}

void MapLoaderPrevLeft() {
    nci = nci - nc1;
    ncf = ncf - nc1;
    setvisualpage(1);
    setactivepage(0);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = (int)nci;j < ncf; j += 1) {
            if (harta[i][j] == 1)
                putimage((j - nci) * wh, i * wh, brickblock, COPY_PUT);
            if (harta[i][j] == 3)
                putimage((j - nci) * wh, i * wh, mario_vine, COPY_PUT);
            if (harta[i][j] == 4)
                putimage((j - nci) * wh, i * wh, mario_vine_top, COPY_PUT);
            if (harta[i][j] == 8) {
                putimage((j-nci) * wh, i * wh, lucky_block, COPY_PUT);
            }
            if (harta[i][j] == 12) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe body
            }
            if (harta[i][j] == 14) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head without pirhana
            }
            if (harta[i][j] == 13) {
                bar((j - nci) * wh, i * wh, (j - nci + 1) * wh, (i + 1) * wh); // placeholder pentru pipe head with pirhana
            }
            if (harta[i][j] == 10) {
                putimage((j-nci) * wh, i * wh, lucky_block_used, COPY_PUT);
            }
        }
        imario = spawn[(int)(nci / nc1)].ifinal;
        jmario = spawn[(int)(nci / nc1)].jfinal;
		putimage((spawn[(int)(nci / nc1)].jfinal - nci) * wh, spawn[(int)(nci / nc1)].ifinal * wh, mario_idle_left, COPY_PUT);
    }
	setvisualpage(0);
}