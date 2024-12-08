#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Mario.h"
using namespace std;


extern float wh, nc1;
extern int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario;
string direction, direction1; 


int main() {
    int time = 0;
    int ok = 1;
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
        if ((GetKeyState(0x41) < 0 || (GetKeyState(VK_LEFT) < 0)) && jmario > 0) {
            direction = "left";
            NextState("left");
        }
        if ((GetKeyState(0x44) < 0 || (GetKeyState(VK_RIGHT) < 0)) && jmario < nc1 - 1) {
            direction = "right";
            NextState("right");
        }
        if ((GetKeyState(0x57) < 0 || (GetKeyState(VK_UP) < 0)) && (harta[imario - 1][jmario] == 3 || harta[imario - 1][jmario] == 4)) {
            direction = "up";
            NextState("up");
        }
        if ((GetKeyState(0x53) < 0 || (GetKeyState(VK_DOWN) < 0)) && (harta[imario + 1][jmario] == 3 || harta[imario + 1][jmario] == 4)) {
            direction = "down";
            NextState("down");
        }
        if ((GetKeyState(VK_SPACE) < 0)) {
            direction = "space";
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
        
        //NextState(time);
        direction = "alba";
        time++;
        cout << direction<<" ";
        if (GetKeyState(0x43) < 0) {
            MapLoader2();
            readimagefile("mario_idle_right.gif", (jmario  - mv2) * (wh), imario * (wh), (jmario + 1 - mv2) * (wh), (imario + 1) * (wh));
        }
        delay(30);
        if (time == 1000) time = 0;
        cout << time<<" "<<imario << " " << jmario;
        if (GetKeyState(VK_ESCAPE) & 0x8000) ok = 0;
    } while (ok!=0);
    cleardevice();
    delay(300);
    CloseWindow;
    return 0;
}