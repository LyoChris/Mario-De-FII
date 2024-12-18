#include "graphics.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <dos.h>
#include <string.h>
#include <random>
#include <windows.h>
#include "Enemies.h"
#include "Map.h"
#include "Colectibles.h"


extern std::string cht;
extern float wh;
extern void* brickblock, * lucky_block, * mario_coin, * goomba_walking_1, * goomba_walking_2, * mario_climbing_down_1, * mario_climbing_down_2, * mario_climbing_up_1,
* mario_climbing_up_2, * mario_idle_left, * mario_idle_right, * mario_jump_1, * mario_left_run_1, * mario_left_run_2, * mario_left_run_3, * mario_right_run_1,
* mario_right_run_2, * mario_right_run_3, * mario_vine, * mario_vine_top, * skyblock, * lucky_block_used, *one_up, *flagpolep;

void preloadImage(const char* filename, int width, int height, void*& buffer) {
    readimagefile(filename, 0, 0, width, height);
    buffer = malloc(imagesize(0, 0, width, height));
    getimage(0, 0, width, height, buffer);
}

void AssetLoader() {
    initwindow(wh + 1, 7* wh + 1, "", -3, -3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("BrickBlock.jpg", wh, wh, brickblock);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("SkyBlock.jpg", wh, wh, skyblock);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine.gif", wh, wh, mario_vine);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_vine_top.gif", wh, wh, mario_vine_top);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_block.jpg", wh, wh, lucky_block);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_coin.gif", wh, wh, mario_coin);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_1.gif", wh, wh, goomba_walking_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("goomba_walking_2.gif", wh, wh, goomba_walking_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_down_1.gif", wh, wh, mario_climbing_down_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_down_2.gif", wh, wh, mario_climbing_down_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_up_1.gif", wh, wh, mario_climbing_up_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_climbing_up_2.gif", wh, wh, mario_climbing_up_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_left.gif", wh, wh, mario_idle_left);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_idle_right.gif", wh, wh, mario_idle_right);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_jump_1.gif", wh, wh, mario_jump_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_1.gif", wh, wh, mario_left_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_2.gif", wh, wh, mario_left_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_left_run_3.gif", wh, wh, mario_left_run_3);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_1.gif", wh, wh, mario_right_run_1);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_2.gif", wh, wh, mario_right_run_2);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("mario_right_run_3.gif", wh, wh, mario_right_run_3);
	cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("lucky_block_used.jpg", wh, wh, lucky_block_used);
    cleardevice();
    setbkcolor(RGB(126, 132, 246));
    preloadImage("one_up.gif", wh, wh, one_up);
	cleardevice(); 
    setbkcolor(RGB(126, 132, 246));
    preloadImage("Flagpole.gif", wh, 7*wh, flagpolep);
	closegraph();
}

int randnumb(int a, int b) {
    // Cream un random number generator
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(a, b);

    int randomInt = dist(gen);  // Generam un numar random
    return randomInt;
}

void LevelLoader() {
    int arg;
	std::cout << "Choose a level: ";
    std::cin >> arg;
    switch (arg) {
    case 1:
        cht = "level1.txt"; break;
	case 2:
		cht = "level2.txt"; break;
	case 3:
		cht = "level3.txt"; break;
	case 4:
		cht = "level4.txt"; break;
	case 5:
		cht = "level5.txt"; break;
	case 6:
		cht = "level6.txt"; break;
    }
}