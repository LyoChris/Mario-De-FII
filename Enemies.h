#pragma once

struct goompa {
	float igompa, jgompa;
	int gdirection = 1;
	int gstage = 1;
	int dead = 0;
	int mapart;
};

void EnemiesMoving();