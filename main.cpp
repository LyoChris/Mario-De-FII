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
#include "Loader.h"
#include "Game.h"
#include "Menus.h"
#include "Sounds.h"
#include "MapEditor.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
using namespace std;



int main() {
	MapReaderandSetter();
	SoundInitialisation();
	//MapEditorLevels();
	//LevelLoader();
	//MarioGame();
	//GameOverMenu();
	MainMenu();
    return 0;
}