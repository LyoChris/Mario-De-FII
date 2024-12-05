#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

string chg = "level1.txt";
string cht = "level2.txt";

ifstream f(chg);

#define MAX1 30
#define MAX2 1000

float wh, nc1;
int x, y, nl, nc, harta[MAX1][MAX2], mv2, stage=-7, k=0, map, imario, jmario;
char tasta;
string direction;


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

void MapLoader() {
    initwindow(x, y, "", -3, -3);
    setbkcolor(RGB(126, 132, 246));
    cleardevice();
    for (int i = 0;i < nl;i += 1) {
        for (int j = mv2;j < nc1+ mv2; j += 1) {
            //if(harta[i][j]==0)
              //readimagefile("SkyBlock.jpg", (j - mv2) * wh, i * wh, (j + 1 - mv2) * wh, (i + 1) * wh);
            if (harta[i][j] == 1)
                readimagefile("BrickBlock.jpg", (j-mv2) * wh, i * wh, (j + 1-mv2) * wh, (i + 1) * wh);
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
        readimagefile("mario_left_run_1.gif", jmario*wh, imario*wh, (jmario+1)*wh, (imario+1)*wh); break;
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

void NextState(string direction1){
    if (direction1 == "right"){
        if (abs(stage) == 10 || abs(stage) == 7 || abs(stage)== 6) stage = -1;
        if (stage > 0) stage = -stage;
        stage--; 
        if (stage == -4) stage = -1;
        readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
        if(harta[imario][jmario]==3) 
            readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        if (harta[imario][jmario] == 4)
            readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        if (jmario < nc1 - 1 && harta[imario][jmario + 1] != 1){
            jmario++;
            MarioStage();
        }
        else {
            stage = -7;
            MarioStage();
        }
    }
    else
        if (direction1 == "left"){
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
                stage=7;
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
        if (harta[imario ][jmario] == 3) {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        else {
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            readimagefile("mario_vine_top.gif", (jmario - mv2) * wh, imario * wh, (jmario + 1 - mv2) * wh, (imario + 1) * wh);
        }
        if ((harta[imario +1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
            imario++;
            MarioStage();
        }
    }

    if (direction1 == "space") {
        stage = -6;
        if(imario>0 && harta[imario-1][jmario]!=1 && harta[imario + 1][jmario] == 1){
            readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            imario--;
            MarioStage();
            delay(30);
            if (imario > 0 && harta[imario - 1][jmario] != 1) {
                readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
                imario--;
                MarioStage();
            }
        }
        
        
    }
    
}


int main() {
    int time = 0;
    int ok = 1;
    string direction1;
    MapReaderandSetter();
    //initwindow(x, y, "", -3, -3);
    MapLoader();
    do {
        /*if (tasta == 'd') {
            mv2++;
            cleardevice();
            MapLoader();
        }
        if (tasta == 'a') {
            mv2--;
            cleardevice();
            MapLoader();
        }*/
        if ((GetKeyState(0x41) < 0) && jmario > 0) {
            direction = "left";
            NextState("left");
        }
        if ((GetKeyState(0x44) < 0) && jmario < nc1 - 1) {
            direction = "right";
            NextState("right");
        }
        if ((GetKeyState(0x57) < 0) && (harta[imario - 1][jmario] == 3 || harta[imario - 1][jmario] == 4)) {
            direction = "up";
            NextState("up");
        }
        if ((GetKeyState(0x53) < 0) && (harta[imario + 1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
            direction = "down";
            NextState("down");
        }
        if ((GetKeyState(VK_SPACE) < 0)) {
            direction = "space";
            NextState("space");
            //k = 1;
        }
        if (harta[imario + 1][jmario] == 0) {
            
            if ((GetKeyState(0x41) < 0) && jmario > 0) {
                direction = "left";
                NextState("left");
            }
            if ((GetKeyState(0x44) < 0) && jmario < nc1 - 1) {
                direction = "right";
                NextState("right");
            }
            if ((GetKeyState(0x57) < 0) && (harta[imario - 1][jmario] == 3 || harta[imario - 1][jmario] == 4)) {
                direction = "up";
                NextState("up");
            }
            if ((GetKeyState(0x53) < 0) && (harta[imario + 1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
                direction = "down";
                NextState("down");
            }
            if ((GetKeyState(VK_SPACE) < 0)) {
                direction = "space";
                NextState("space");
                //k = 1;
            }
            delay(50);
            if (harta[imario + 1][jmario] == 0) {
                readimagefile("SkyBlock.jpg", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
                imario++;
                readimagefile("mario_jump_1.gif", jmario * wh, imario * wh, (jmario + 1) * wh, (imario + 1) * wh);
            }
            if (imario > nl) {
                CloseWindow;
                exit(0);
            }
        }
        
        //NextState(time);
        direction = "alba";
        time++;
        cout << direction<<" ";
        if (GetKeyState(0x43) < 0) {
            MapLoader2();
            readimagefile("mario_idle_right.gif", (jmario  - mv2) * (wh), imario * (wh), (jmario + 1 - mv2) * (wh), (imario + 1) * (wh));
        }
        delay(30);
        if (time == 1000) time = 00;
        cout << time<<" "<<imario << " " << jmario;
        if (GetKeyState(VK_ESCAPE) & 0x8000) ok = 0;
    } while (ok!=0);
    cleardevice();
    delay(300);
    CloseWindow;
    return 0;
}