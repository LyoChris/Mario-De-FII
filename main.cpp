#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Mario.h"
#include "Enemies.h"
using namespace std;

extern float wh, nc1;
extern int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario;
string direction, direction1;
int time1, ok = 1;


int main() {
    MapReaderandSetter();
    //initwindow(x, y, "", -3, -3);
    MapLoader(0);
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
        MarioMovement();
        gompa(1);
    } while (ok!=0);
    cleardevice();
    delay(300);
    CloseWindow;
    return 0;
}