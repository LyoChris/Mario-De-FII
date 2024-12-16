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
using namespace std;

#define MAX1 30
#define MAX2 1000

extern colectible coins[100];
extern goompa gompav[100];

extern double MarioInterval;
extern float wh, ncf, nci, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000], mv2, map, stage=-7, mappart, coino;
extern int time1, okesc, n;
string direct;
int lifes = 3, safeimario, safejmario, mover = 0, coinono = 0, invincibilityframes = 0, ok = 0;

void MarioStage() {
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
        readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
        if (harta[(int)imario][(int)jmario] == 3)
            readimagefile("mario_vine.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
        if (harta[(int)imario][(int)jmario] == 4)
            readimagefile("mario_vine_top.gif", ((int)jmario - nci) * wh, (int)imario * wh, (((int)jmario - nci) + 1) * wh, ((int)imario + 1) * wh);
        jmario+=0.5;
        if (CheckBlock(imario*wh, jmario*wh, wh, (float)imario*wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario + 1] == 1 && (jmario-(int)jmario!=0)) || jmario > ncf) {
            jmario-=0.5;
            stage = -7;
            MarioStage();
        }
        else {
            MarioStage();
        }
    }
    else
        if (direction1 == "left") {
            if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = 1;
            if (stage < 0) stage = -stage;
            stage++;
            if (stage == 4) stage = 1;
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            if (harta[(int)imario][(int)jmario] == 3 && jmario - (int)jmario == 0)
                readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, ((imario + 1) * wh));
            if (harta[(int)imario][(int)jmario + 1] == 3)
                readimagefile("mario_vine.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
            if (harta[(int)imario][(int)jmario] == 4)
                readimagefile("mario_vine_top.gif", ((int)jmario + 1 - nci) * wh, (int)imario * wh, (((int)jmario + 1 - nci) + 1) * wh, ((int)imario + 1) * wh);
            jmario-=0.5;
            if (CheckBlock(imario*wh, jmario*wh, wh, (float)imario*wh, (float)(jmario)*wh) && (harta[(int)imario][(int)jmario] == 1 || jmario < 0)) {
                jmario+=0.5;
                stage = 7;
                MarioStage();
            }
            else {
                MarioStage();
            }
        }
    
    if (direction1 == "up")
    {
        if (abs(stage) == 10) stage = -stage;
        else stage = 10;
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
		//cout << jmario << " " << (int)jmario << '\n';
        imario-=0.5;
        if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !((harta[(int)imario][(int)jmario] == 3) || harta[(int)imario][(int)jmario] == 4) && (jmario - (int)jmario != 0)) {
            imario += 0.5;
            stage = 10;
            MarioStage();
        }
        else
            MarioStage();
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
        imario+=0.5;
        cout << jmario << " " << (int)jmario << '\n';
        if (jmario - (int)jmario == 0) {
            if (CheckBlock(imario, jmario, wh, (float)(imario), (float)(jmario)) && !(harta[(int)imario][(int)jmario] == 3 || harta[(int)imario][(int)jmario] == 4)) {
                imario -= 0.5;
                stage = 9;
                MarioStage();
            }
            else
                MarioStage();
        }
    }
    if (direction1 == "space" || ok>0) {
        stage = -6;
        if (ok > 0) {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            if (harta[(int)imario][(int)jmario] == 3)
                readimagefile("mario_vine.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            if (harta[(int)imario][(int)jmario] == 4)
                readimagefile("mario_vine_top.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            imario-=0.5;
            if (CheckBlock(imario, jmario, wh, (float)(imario - 1), (float)(jmario)) && (imario > 0 && harta[(int)imario][(int)jmario] != 1)) {
                delay(20);
                MarioStage();
                ok--;
            }
            else {
                imario+=0.5;
                ok = 0;
            }
        }
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
    if ((GetKeyState(VK_SPACE) < 0) && harta[(int)imario + 1][(int)jmario] == 1) {
        ok = 4;
        NextState("space");
        mover = 1;
        direct = "space";
        //k = 1;
    }
    if (ok > 0) {
		delay(MarioInterval);
        NextState("space");
    }
    if (harta[(int)imario + 1][(int)jmario] == 0 && ok==0) {
        mover = 1;
        if (harta[(int)imario + 1][(int)jmario] == 0) {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            imario+=0.5;
            readimagefile("mario_jump_1.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
        }
        if (imario > nl) {
            readimagefile("SkyBlock.jpg", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_idle_left.gif", (safejmario - nci) * wh, safeimario * wh, ((safejmario - nci) + 1) * wh, (safeimario + 1) * wh);
            lifes--;
            imario = safeimario;
            jmario = safejmario;
        }
    }
    for (int i = 1;i <= n;i++) { //checker pentru coliziuni cu goomba
		//cout << imario << " " << gompav[i].igompa << '\n';
        if (gompav[n].mapart == (int)(nci - nc1) && gompav[i].dead == 0) {
            float imariof = (float)imario;
            float jmariof = (float)jmario;
            if (CheckBlock(imariof * wh, jmariof * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "right") {
                if (imario < gompav[i].igompa) {
					gompav[i].dead = 1; 
					readimagefile("SkyBlock.jpg", (gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, ((gompav[i].jgompa - nci) + 1) * wh, (gompav[i].igompa + 1) * wh);
                    cout << "GOOMPA DEAD" << '\n';
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
            if (CheckBlock(imariof * wh, jmariof * wh, wh, (float)(gompav[i].igompa) * wh, (float)(gompav[i].jgompa) * wh) == 1 && direct == "left") {
                if (imario < gompav[i].igompa) {
                    gompav[i].dead = 1;
                    readimagefile("SkyBlock.jpg", (gompav[i].jgompa - nci) * wh, gompav[i].igompa * wh, ((gompav[i].jgompa - nci) + 1) * wh, (gompav[i].igompa + 1) * wh);
                    cout << "GOOMPA DEAD" << '\n';
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
            float imariof = (float)imario;
            float jmariof = (float)jmario;
            if (CheckBlock(imariof * wh, jmariof * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec) * wh) == 1 && direct == "right" && coins[i].colected == 0) {
                coinono++;
                coins[i].colected = 1;
                readimagefile("SkyBlock.jpg", (coins[i].jcolec -nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
                readimagefile("mario_idle_right.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
            }
            if (CheckBlock(imariof * wh, jmariof * wh, wh, (float)(coins[i].icolec) * wh, (float)(coins[i].jcolec) * wh) == 1 && direct == "left" && coins[i].colected == 0) {
                coinono++;
                coins[i].colected = 1;
                readimagefile("SkyBlock.jpg", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
                readimagefile("mario_idle_left.gif", (jmario - nci) * wh, imario * wh, ((jmario - nci) + 1) * wh, (imario + 1) * wh);
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
    if (lifes <= 0) {
        delay(500);
        closegraph();
        exit(0);
    }
    if (GetKeyState(VK_ESCAPE) & 0x8000) okesc = 0;
}