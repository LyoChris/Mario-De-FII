#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
using namespace std;

#define MAX1 30
#define MAX2 1000

extern float wh, nc1;
extern int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario, stage=-7;
extern int time1, ok;

void MarioStage() {
    switch (stage) {
    case -10:
        readimagefile("mario_climbing_up_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 10:
        readimagefile("mario_climbing_up_2.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -9:
        readimagefile("mario_climbing_down_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 9:
        readimagefile("mario_climbing_down_2.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -7:
        readimagefile("mario_idle_right.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 7:
        readimagefile("mario_idle_left.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 1:
        readimagefile("mario_left_run_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 2:
        readimagefile("mario_left_run_2.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case 3:
        readimagefile("mario_left_run_3.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -1:
        readimagefile("mario_right_run_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -2:
        readimagefile("mario_right_run_2.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -3:
        readimagefile("mario_right_run_3.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    case -6:
        readimagefile("mario_jump_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh); break;
    }
}

void NextState(string direction1) {
    if (direction1 == "right") {
        if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = -1;
        if (stage > 0) stage = -stage;
        stage--;
        if (stage == -4) stage = -1;
        readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
        if (harta[imario][jmario] == 3)
            readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        if (harta[imario][jmario] == 4)
            readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        if (jmario < nc1 - 1 && harta[imario][jmario + 1] != 1) {
            jmario++;
            MarioStage();
        }
        else {
            stage = -7;
            MarioStage();
        }
    }
    else
        if (direction1 == "left") {
            if (abs(stage) == 10 || abs(stage) == 7 || abs(stage) == 6) stage = 1;
            if (stage < 0) stage = -stage;
            stage++;
            if (stage == 4) stage = 1;
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            if (harta[imario][jmario] == 3)
                readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
            if (harta[imario][jmario] == 4)
                readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
            if (jmario > 0 && harta[imario][jmario - 1] != 1) {
                jmario--;
                MarioStage();
            }
            else {
                stage = 7;
                MarioStage();
            }
        }

    if (direction1 == "up")
    {
        if (abs(stage) == 10) stage = -stage;
        else stage = 10;
        if (harta[imario][jmario] == 3) {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        else {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        if (harta[imario - 1][jmario] == 3 || harta[imario - 1][jmario] == 4) {
            imario--;
            MarioStage();
        }
    }

    if (direction1 == "down")
    {
        if (abs(stage) == 9) stage = -stage;
        else stage = -9;
        if (harta[imario][jmario] == 3) {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        else {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        if ((harta[imario + 1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
            imario++;
            MarioStage();
        }
    }

    if (direction1 == "space") {
        stage = -6;
        if (imario > 0 && harta[imario - 1][jmario] != 1 && harta[imario + 1][jmario] == 1) {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            imario--;
            MarioStage();
            delay(30);
            if (imario > 0 && harta[imario - 1][jmario] != 1) {
                readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
                imario--;
                MarioStage();
            }
            if (imario > 0 && harta[imario - 1][jmario] != 1) {
                readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
                imario--;
                MarioStage();
            }
        }


    }

}

void MarioMovement() {
    if ((GetKeyState(0x41) < 0 || (GetKeyState(VK_LEFT) < 0)) && jmario > 0) {
        NextState("left");
    }
    if ((GetKeyState(0x44) < 0 || (GetKeyState(VK_RIGHT) < 0)) && jmario < nc1 - 1) {
        NextState("right");
    }
    if ((GetKeyState(0x57) < 0 || (GetKeyState(VK_UP) < 0)) && (harta[imario - 1][jmario] == 3 || harta[imario - 1][jmario] == 4)) {
        NextState("up");
    }
    if ((GetKeyState(0x53) < 0 || (GetKeyState(VK_DOWN) < 0)) && (harta[imario + 1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
        NextState("down");
    }
    if ((GetKeyState(VK_SPACE) < 0)) {
        NextState("space");
        //k = 1;
    }
    if (harta[imario + 1][jmario] == 0) {
        delay(50);
        if (harta[imario + 1][jmario] == 0) {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            imario++;
            readimagefile("mario_jump_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
        }
        if (imario > nl) {
            MapLoader2();
            CloseWindow;
            exit(0);
        }
    }
    time1++;
    if (GetKeyState(0x43) < 0) {
        MapLoader2();
        readimagefile("mario_idle_right.gif", (jmario - mv2) * (wh), imario * (wh), (jmario + 1 - mv2) * (wh), (imario + 1) * (wh));
    }
    delay(30);
    if (GetKeyState(VK_ESCAPE) & 0x8000) ok = 0;
}