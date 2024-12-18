#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
using namespace std;

#define MAX1 30
#define MAX2 1000

extern colectible coins[100], life[100];
extern goompa gompav[100];
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, *one_up, *flagpolep;
extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000], mv2, map, stage=-7, mappart, coino, lifo, flagpole;
extern int time1, okesc, n;
string direct;
int lifes = 3, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0, hoverm=0, play=0;

void MarioStageput() {
    switch (stage) {
    case -10:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_up_1, COPY_PUT); break;
        //readimagefile("mario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_up_2, COPY_PUT); break;
        //readimagefile("mario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_down_1, COPY_PUT); break;
        //readimagefile("mario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
		putimage((jmario - nci) * wh, imario * wh, mario_climbing_down_2, COPY_PUT); break;
        //readimagefile("mario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
		putimage((jmario - nci) * wh, imario * wh, mario_idle_right, COPY_PUT); break;
        //readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
		putimage((jmario - nci) * wh, imario * wh, mario_idle_left, COPY_PUT); break;
        //readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_1, COPY_PUT); break;
        //readimagefile("mario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_2, COPY_PUT); break;
        //readimagefile("mario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
		putimage((jmario - nci) * wh, imario * wh, mario_left_run_3, COPY_PUT); break;
        //readimagefile("mario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_1, COPY_PUT); break;
        //readimagefile("mario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_2, COPY_PUT); break;
        //readimagefile("mario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
		putimage((jmario - nci) * wh, imario * wh, mario_right_run_3, COPY_PUT); break;
        //readimagefile("mario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
		putimage((jmario - nci) * wh, imario * wh, mario_jump_1, COPY_PUT); break;
        //readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void MarioStageread() {
    switch (stage) {
    case -10:
        readimagefile("mario_climbing_up_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("mario_climbing_up_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("mario_climbing_down_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("mario_climbing_down_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("mario_left_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("mario_left_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("mario_left_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("mario_right_run_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("mario_right_run_2.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("mario_right_run_3.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh); break;
    }
}

void NextState(string direction1) {
    if (direction1 == "right") { 
        if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = -1;
        if (stage > 0) stage = -stage;
        stage--;
        if (stage == -4) stage = -1;
        //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
		putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
        jmario += 0.5;
        if (jmario - (int)jmario != 0) {
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                //readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario +1] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci+1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                //readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario+1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci+1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                //readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (jmario + 1 == flagpole) {
                hoverm = 1;
                putimage(((int)jmario - nci + 1) * wh, (int)imario *6* wh, flagpolep, COPY_PUT);
                //readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (jmario==flagpole) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario *6* wh, flagpolep, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
        }
        else {
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                //readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario -1] == 3) {
                hoverm = 1;
                putimage(((int)jmario -1 - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (jmario == flagpole) {
                hoverm = 1;
                putimage(((int)jmario - nci) * wh, (int)imario * 6 * wh, flagpolep, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (jmario-1 == flagpole) {
                hoverm = 1;
                putimage(((int)jmario -1- nci) * wh, (int)imario * 6 * wh, flagpolep, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
            if (harta[(int)imario][(int)jmario - 1] == 4) {
                hoverm = 1;
                putimage(((int)jmario - 1 - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                //readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            }
        }
        if (hoverm == 1) {
            //jmario += 0.5;
            if (imario - (int)imario != 0) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf) {
                    jmario -= 0.5;
                    stage = -7;
                    PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    MarioStageread();
                }
                else {
                    MarioStageread();
                }
            }
            else {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf) {
                    jmario -= 0.5;
                    stage = -7;
                    PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    MarioStageread();
                }
                else {
                    MarioStageread();
                }
            }
        }
        else {
            //jmario += 0.5;
            if (imario - (int)imario != 0) {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf) {
                    jmario -= 0.5;
                    stage = -7;
                    PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    MarioStageput();
                }
                else {
                    MarioStageput();
                }
            }
            else {
                if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 1 && (jmario - (int)jmario != 0)) || jmario > ncf) {
                    jmario -= 0.5;
                    stage = -7;
                    PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    MarioStageput();
                }
                else {
                    MarioStageput();
                }
            }
        }
        hoverm = 0;
    }
    else
        if (direction1 == "left") {
            hoverm = 0;
            if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = 1;
            if (stage < 0) stage = -stage;
            stage++;
            if (stage == 4) stage = 1;
			putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
            jmario -= 0.5;
            //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                if (harta[(int)imario][(int)jmario] == 3) {
                    hoverm = 1;
					putimage(((int)jmario - nci)* wh, (int)imario* wh, mario_vine, COPY_PUT);
                    //readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, ((imario + 1) * wh));
                }
                if (harta[(int)imario][(int)jmario + 1] == 3) {
					hoverm = 1;
                    putimage(((int)jmario - nci + 1) * wh, (int)imario * wh, mario_vine, COPY_PUT);
                    //readimagefile("mario_vine.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
                }
                if (harta[(int)imario][(int)jmario] == 4) {
                    hoverm = 1;
                    putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                    //readimagefile("mario_vine_top.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
                }
                if (harta[(int)imario][(int)jmario +1] == 4) {
                    hoverm = 1;
                    putimage(((int)jmario - nci +1) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
                    //readimagefile("mario_vine_top.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
                }
                cout << "Mario : " << imario << " " << jmario << '\n';
            if (hoverm == 1) {
                //jmario -= 0.5;
                if (imario - (int)imario != 0) {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 1 || jmario < 0)) {
                        jmario += 0.5;
                        stage = 7;
                        PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        MarioStageread();
                    }
                    else {
                        MarioStageread();
                    }
                }
                else {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 1 || jmario < 0)) {
                        jmario += 0.5;
                        stage = 7;
                        PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        MarioStageread();
                    }
                    else {
                        MarioStageread();
                    }
                }
            }
            else {
                //jmario -= 0.5;
                if (imario - (int)imario != 0) {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario + 1][(int)jmario] == 1 || jmario < 0)) {
                        jmario += 0.5;
                        stage = 7;
                        PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        MarioStageput();
                    }
                    else {
                        MarioStageput();
                    }
                }
                else {
                    if (CheckBlock(imario * wh, jmario * wh, wh, (float)imario * wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 1 || jmario < 0)) {
                        jmario += 0.5;
                        stage = 7;
                        PlaySound(TEXT("bump.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        MarioStageput();
                    }
                    else {
                        MarioStageput();
                    }
                }
            }
        }
    
    if (direction1 == "up")
    {
        if (abs(stage) == 10) stage = -stage;
        else stage = 10;
		cout << "Nature: " << harta[(int)imario][(int)jmario] << '\n';
        if (harta[(int)imario][(int)jmario] == 3) {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
        }
        else {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine_top.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
        }
        if (harta[(int)imario][(int)jmario - 1] == 3) {
            readimagefile("SkyBlock.jpg", ((int)jmario - 1 - nci) * wh, (int)imario * wh, (((int)jmario - 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
            readimagefile("mario_vine.gif", ((int)jmario - 1 - nci) * wh, (int)imario * wh, (((int)jmario - 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
        }
		cout << "Mario : " << imario << " " << jmario <<" " << jmario - (int)jmario<< '\n';
        
        if (jmario - (int)jmario == 0) {
            imario-=0.5;
            if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !((harta[(int)imario][(int)jmario] == 3) || harta[(int)imario][(int)jmario] == 4) && (jmario - (int)jmario == 0)) {
                imario += 0.5;
                stage = 10;
                MarioStageread();
            }
            else
                MarioStageread();
        }
    }

    if (direction1 == "down")
    {
        if (abs(stage) == 9) stage = -stage;
        else stage = -9;
        if (harta[(int)imario][(int)jmario] == 3) {
            readimagefile("SkyBlock.jpg", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
            readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
        }
        else {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
        }
        if(harta[(int)imario][(int)jmario + 1] == 3) {
            readimagefile("SkyBlock.jpg", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
            readimagefile("mario_vine.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
        }
        
        if (jmario - (int)jmario == 0) {
            imario+=0.5;
            if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !(harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4)) {
                imario -= 0.5;
                stage = 9;
                MarioStageread();
            }
            else
                MarioStageread();
        }
    }
    if (direction1 == "space" || ok>0) {
        stage = -6;
        if (ok > 0) {
            //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
			putimage((jmario - nci)* wh, imario* wh, skyblock, COPY_PUT);
            imario -= 0.5;
            if (harta[(int)imario][(int)jmario] == 3) {
                hoverm = 1;
                //readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario][(int)jmario] == 4) {
                hoverm = 1;
                //readimagefile("mario_vine_top.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage(((int)jmario - nci) * wh, (int)imario * wh, mario_vine_top, COPY_PUT);
            }
            if (harta[(int)imario+1][(int)jmario] == 3) {
                hoverm = 1;
                //readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage(((int)jmario - nci) * wh, ((int)imario+1) * wh, mario_vine, COPY_PUT);
            }
            if (harta[(int)imario+1][(int)jmario] == 4) {
                hoverm = 1;
                //readimagefile("mario_vine_top.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage(((int)jmario - nci) * wh, ((int)imario+1) * wh, mario_vine_top, COPY_PUT);
            }
            if (hoverm == 1) {
                //imario-=0.5;
                if (jmario - (int)jmario != 0) {
                    if ((imario > 0 && ((harta[(int)imario][(int)jmario] != 1 && (harta[(int)imario][(int)jmario + 1] != 1)) && (harta[(int)imario][(int)jmario] != 8 && (harta[(int)imario][(int)jmario + 1] != 8) && (harta[(int)imario][(int)jmario] != 10 && (harta[(int)imario][(int)jmario + 1] != 10)))))) {
                        delay(20);
                        if (ok == 4) {
                            PlaySound(TEXT("jump_small.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        MarioStageread();
                        ok--;
                    }
                    else {
                        imario += 0.5;
                        ok = 0;
                    }
                }
                else {
                    if (CheckBlock(imario, jmario, wh, (float)(imario - 1), (float)(jmario)) && (imario > 0 && (harta[(int)imario][(int)jmario] != 1) && (harta[(int)imario][(int)jmario] != 8) && (harta[(int)imario][(int)jmario] != 10))) {
                        delay(20);
                        if (ok == 4) {
                            PlaySound(TEXT("jump_small.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        MarioStageread();
                        ok--;
                    }
                    else {
                        if (harta[(int)imario][(int)jmario] == 8) {
                            //readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
							putimage(((int)jmario - nci)* wh, ((int)imario)* wh, lucky_block_used, COPY_PUT);
                            int ranblock = randnumb(0, 1);
                            if (ranblock == 1) {
                                lifo++;
                                life[lifo].icolec = (int)imario;
								life[lifo].jcolec = (int)jmario;
								life[lifo].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci)* wh, ((int)imario -1)* wh, one_up, COPY_PUT);
                            }
                            else {
                                coino++;
                                coins[coino].icolec = (int)imario;
								coins[coino].jcolec = (int)jmario;
								coins[coino].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci)* wh, ((int)imario - 1)* wh, mario_coin, COPY_PUT);
                            }
                            harta[(int)imario][(int)jmario] = 10;
                        }
                        imario += 0.5;
                        ok = 0;
                    }
                }
            }
            else {
                //imario -= 0.5;
                if (jmario - (int)jmario != 0) {
                    if ((imario > 0 && ((harta[(int)imario][(int)jmario] != 1 && (harta[(int)imario][(int)jmario + 1] != 1)) && (harta[(int)imario][(int)jmario] != 8 && (harta[(int)imario][(int)jmario + 1] != 8) 
                        && (harta[(int)imario][(int)jmario] != 10 && (harta[(int)imario][(int)jmario + 1] != 10)))))) {
                        delay(20);
                        if (ok == 4) {
                            PlaySound(TEXT("jump_small.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        MarioStageput();
                        ok--;
                    }
                    else {
                        imario += 0.5;
                        ok = 0;
                    }
                }
                else {
                    if (CheckBlock(imario, jmario, wh, (float)(imario - 1), (float)(jmario)) && (imario > 0 && (harta[(int)imario][(int)jmario] != 1) && (harta[(int)imario][(int)jmario] != 8) && (harta[(int)imario][(int)jmario] != 10))) {
                        delay(20);
                        if (ok == 4) {
                            PlaySound(TEXT("jump_small.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        MarioStageput();
                        ok--;
                    }
                    else {
                        if (harta[(int)imario][(int)jmario] == 8) {
                            //readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                            putimage(((int)jmario - nci) * wh, ((int)imario) * wh, lucky_block_used, COPY_PUT);
                            int ranblock = randnumb(0, 1);
							cout << ranblock << '\n';
                            if (ranblock == 1) {
                                lifo++;
                                life[lifo].icolec = (int)imario;
                                life[lifo].jcolec = (int)jmario;
                                life[lifo].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, one_up, COPY_PUT);
                            }
                            else {
                                coino++;
                                coins[coino].icolec = (int)imario;
                                coins[coino].jcolec = (int)jmario;
                                coins[coino].mapart = (int)(nci - nc1);
                                putimage(((int)jmario - nci) * wh, ((int)imario - 1) * wh, mario_coin, COPY_PUT);
                            }
                            harta[(int)imario][(int)jmario] = 10;
                        }
                        imario += 0.5;
                        ok = 0;
                    }
                }
            }
            
        }
        hoverm = 0;
    }

}

void MarioMovement() {
    if (harta[(int)imario + 1][(int)jmario] == 1) {
        safeimario = imario;
        safejmario = jmario;
    }
    if ((GetKeyState(0x41) < 0 || (GetKeyState(VK_LEFT) < 0)) && jmario > 0) {
        NextState("left");
        mover = 1;
        direct = "left";
    }
    if ((GetKeyState(0x44) < 0 || (GetKeyState(VK_RIGHT) < 0)) && jmario < ncf - 1) {
        NextState("right");
        mover = 1;
        direct = "right";
    }
    if ((GetKeyState(0x57) < 0 || (GetKeyState(VK_UP) < 0)) && (harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4)) {
        NextState("up");
        mover = 1;
        direct = "up";
    }
    if ((GetKeyState(0x53) < 0 || (GetKeyState(VK_DOWN) < 0)) && (harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4)) {
        NextState("down");
        mover = 1;
        direct = "down";
    }
    if ((GetKeyState(VK_SPACE) < 0) && harta[(int)imario + 1][(int)jmario] == 1 ) {
        ok = 4;
        NextState("space");
        mover = 1;
        direct = "space";
        //k = 1;
    }
    if (ok > 0) {
        NextState("space");
        delay(MarioInterval);
    }
    if ((int)jmario - jmario != 0) {
        if (harta[(int)imario + 1][(int)jmario] == 0 && harta[(int)imario + 1][(int)jmario + 1] == 0 && ok == 0) {
            mover = 1;
            if (harta[(int)imario + 1][(int)jmario] == 0) {
                //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
				putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                imario += 0.5;
				putimage((jmario - nci) * wh, (imario) * wh, mario_jump_1, COPY_PUT);
                //readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            }
            if (imario > nl) {
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                //readimagefile("mario_idle_left.gif", (safejmario - nci) * wh, safeimario * wh, ((safejmario - nci) + 1) * wh, (safeimario + 1) * wh);
				putimage((safejmario - nci) * wh, (safeimario) * wh, mario_idle_left, COPY_PUT);
                lifes--;
                imario = safeimario;
                jmario = safejmario;
            }
        }
    }
    else {
        if (harta[(int)imario + 1][(int)jmario] == 0 && ok == 0) {
            mover = 1;
            if (harta[(int)imario + 1][(int)jmario] == 0) {
                //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                imario += 0.5;
                //readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((jmario - nci) * wh, (imario) * wh, mario_jump_1, COPY_PUT);
            }
            if (imario > nl) {
                putimage((jmario - nci) * wh, imario * wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((safejmario - nci) * wh, (safeimario) * wh, mario_idle_left, COPY_PUT);
                //readimagefile("mario_idle_left.gif", (safejmario - nci) * wh, safeimario * wh, ((safejmario - nci) + 1) * wh, (safeimario + 1) * wh);
                lifes--;
                imario = safeimario;
                jmario = safejmario;
            }
        }
    }
    for (int i = 1;i <= n;i++) { //checker pentru coliziuni cu goomba
        if (gompav[i].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "right") {
                if (imario < gompav[i].igompa) {
					gompav[i].dead = 1;
                    ok += 4;
                    PlaySound(TEXT("stomp.wav"), NULL, SND_FILENAME | SND_ASYNC);
					putimage((gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, skyblock, COPY_PUT);
					//readimagefile("SkyBlock.jpg", (gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, ((gompav[i].jgompa - nci) + 1) * wh, (gompav[i].igompa + 1) * wh);
                    std::cout << "GOOMPA DEAD" << '\n';
                }
                else {
                    NextState("left");
                    NextState("left");
                    if (invincibilityframes == 0) {
                        lifes--;
                        invincibilityframes = 10;
                    }
                }
                
            }
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "left") {
                if (imario < gompav[i].igompa) {
                    gompav[i].dead = 1;
                    ok += 4;
                    PlaySound(TEXT("stomp.wav"), NULL, SND_FILENAME | SND_ASYNC);
					putimage((gompav[i].jgompa - nci)* wh, gompav[i].igompa* wh, skyblock, COPY_PUT);
                    //readimagefile("SkyBlock.jpg", (gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, ((gompav[i].jgompa - nci) + 1) * wh, (gompav[i].igompa + 1) * wh);
                    std::cout << "GOOMPA DEAD" << '\n';
                }
                else {
                    NextState("right");
                    NextState("right");
                    if (invincibilityframes == 0) {
                        lifes--;
                        invincibilityframes = 10;
                    }
                }
            }
        }
    }
    for (int i = 1;i <= coino;i++) { //checker pentru coliziuni cu coins
        if (coins[i].mapart == (int)(nci - nc1)) {
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec) * wh) == 1 && direct == "right" && coins[i].colected == 0) {
                coinono++;
                coins[i].colected = 1;
                delay(30);
                PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
				putimage((coins[i].jcolec - nci)* wh, coins[i].icolec* wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (coins[i].jcolec -nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
                //readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
				putimage((jmario - nci)* wh, imario* wh, mario_idle_right, COPY_PUT);
                
            }
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec) * wh) == 1 && direct == "left" && coins[i].colected == 0) {
                coinono++;
                coins[i].colected = 1;
                delay(30);
                PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
                putimage((coins[i].jcolec - nci)* wh, coins[i].icolec* wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
                //readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((jmario - nci)* wh, imario* wh, mario_idle_right, COPY_PUT);
            }
        }
    }
    for (int i = 1;i <= lifo;i++) { //checker pentru coliziuni cu one_ups
        if (life[i].mapart == (int)(nci - nc1)) {
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(life[i].icolec) * wh, (float)(life[i].jcolec) * wh) == 1 && direct == "right" && life[i].colected == 0) {
                lifes++;
                life[i].colected = 1;
                delay(100);
                PlaySound(TEXT("one_up.wav"), NULL, SND_FILENAME | SND_ASYNC);
                putimage((life[i].jcolec - nci)* wh, life[i].icolec* wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (life[i].jcolec - nci) * wh, life[i].icolec * wh, ((life[i].jcolec - nci) + 1) * wh, (life[i].icolec + 1) * wh);
                //readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((jmario - nci)* wh, imario* wh, mario_idle_right, COPY_PUT);
                
            }
            if (CheckBlock(imario * wh, jmario * wh, wh, (float)(life[i].icolec) * wh, (float)(life[i].jcolec) * wh) == 1 && direct == "left" && life[i].colected == 0) {
                lifes++;
                life[i].colected = 1;
                PlaySound(TEXT("one_up.wav"), NULL, SND_FILENAME | SND_ASYNC);
                delay(100);
                putimage((life[i].jcolec - nci)* wh, life[i].icolec* wh, skyblock, COPY_PUT);
                //readimagefile("SkyBlock.jpg", (life[i].jcolec - nci) * wh, life[i].icolec * wh, ((life[i].jcolec - nci) + 1) * wh, (life[i].icolec + 1) * wh);
                //readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
                putimage((jmario - nci)* wh, imario* wh, mario_idle_right, COPY_PUT);
            }
        }
    }
    if (jmario >= (int)ncf) MapLoaderNextRight(); //randam urmatoarea parte din harta
    if (jmario <= (int)nci && jmario > 0) MapLoaderPrevLeft(); //randam o parte anterioara a hartii
    /*if (mover == 0) {
        readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
        readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
    }
    mover = 0;*/
    if(invincibilityframes!=0) invincibilityframes--;
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
    char text1[20] = "Coins ";
    char text2[20] = "Lives ";
    char score[10], lives[10];
    itoa(coinono, score, 10);
    itoa(lifes, lives, 10);
    outtextxy(25, 25, text1);
    outtextxy(100, 25, score);
    outtextxy(25, 50, text2);
    outtextxy(100, 50, lives);
    if (jmario == flagpole && flagpole != 0 && play==0) {
        PlaySound(TEXT("flagpole.wav"), NULL, SND_FILENAME | SND_SYNC);
        play = 1;
    }
	if (jmario > flagpole+ 1 && flagpole!=0) {
		PlaySound(TEXT("stage_clear.wav"), NULL, SND_FILENAME | SND_SYNC);
		closegraph();
		exit(0);
    }
    if (lifes <= 0) {
        PlaySound(TEXT("gameover.wav"), NULL, SND_FILENAME | SND_SYNC);
        closegraph();
        exit(0);
    }
    if (GetKeyState(VK_ESCAPE) & 0x8000) okesc = 0;
}