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
#include "MapEditor.h"
using namespace std;




int main() {
	MapReaderandSetter();
	//MapEditorLevels();
	LevelLoader();
	MarioGame();
	//MainMenu();
    return 0;
}