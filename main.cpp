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

#define MARIO_TIME 0.08 // 80 ms
#define ENEMY_TIME 0.3  // 300 ms

extern float wh, nc1;
extern int x, y, nl, nc, harta[30][1000], mv2, map, imario, jmario;
string direction, direction1;
int time1, ok = 1;


int main() {
    MapReaderandSetter();
    //initwindow(x, y, "", -3, -3);
    MapLoader(0);
    clock_t lastMarioMove = clock(); //facem cate un ceas pentru inamici si Mario
    clock_t lastEnemyMove = clock();

    double MarioInterval = MARIO_TIME;
    double enemyInterval = ENEMY_TIME;

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
        clock_t now = clock();
        if ((now - lastMarioMove) / (double)CLOCKS_PER_SEC >= MarioInterval) {
            MarioMovement();
            lastMarioMove = now;
        }
        if ((now - lastEnemyMove) / (double)CLOCKS_PER_SEC >= enemyInterval) {
            EnemiesMoving();
            lastEnemyMove = now;
        }
        
        
    } while (ok!=0);
    cleardevice();
    delay(300);
    CloseWindow;
    return 0;
}