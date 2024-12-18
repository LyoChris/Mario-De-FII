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

#define MARIO_TIME 0.05 // 80 ms
#define ENEMY_TIME 0.2  // 200 ms
#define FRAME_TIME 0.08 // 16 ms

void* playerImg1;

extern float wh, nc1, imario, jmario;
extern int x, y, nl, nc, harta[30][1000], mv2, map;
string direction, direction1;
int time1, okesc = 1, ok1=0;

double MarioInterval = MARIO_TIME;
double enemyInterval = ENEMY_TIME;
double FrameInterval = FRAME_TIME;

//int bufferSize = imagesize(0, 0, x, y);
//void* buffer = malloc(bufferSize);

int main() {
    MapReaderandSetter();
    //initwindow(x, y, "", -3, -3);
    MapLoader();
    clock_t lastMarioMove = clock(); //facem cate un ceas pentru inamici si Mario
    clock_t lastEnemyMove = clock();
    clock_t lastFrame = clock();

    int page = 0;
    /*preloadImage("mario_idle_right.gif", wh, playerImg1);
    if (playerImg1 == NULL) {
        cout << "EROARE LOADING";
        exit(0);
    }*/

    do {
        clock_t now = clock();
        if ((now - lastFrame) / (double)CLOCKS_PER_SEC >= FrameInterval) {
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
            // Set active page for drawing
            //setactivepage(page);
            //cleardevice();


            if (harta[(int)imario + 1][(int)jmario] == 0) {
                MarioInterval = MarioInterval * 1.5;
                ok1 = 1;
            }
            if ((now - lastMarioMove) / (double)CLOCKS_PER_SEC >= MarioInterval) {
                MarioMovement();
                lastMarioMove = now;
            }
            if ((now - lastEnemyMove) / (double)CLOCKS_PER_SEC >= enemyInterval) {
                EnemiesMoving();
                lastEnemyMove = now;
            }
            if (ok1 == 1) {
                MarioInterval = MarioInterval / 1.5;
                ok1 = 0;
            }
            // Switch visual page to display
            //setvisualpage(page);
            //Toggle active page for next frame
           // page = 1 - page;
            lastFrame = now;
        }
        
    } while (okesc!=0);
    cleardevice();
    delay(300);
    CloseWindow;
    return 0;
}