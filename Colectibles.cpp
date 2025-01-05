#include "graphics.h"
#include <iostream>
#include "Colissions.h"
#include "Colectibles.h"
#include "Enemies.h"
#include "miniaudio.h"
#include "Sounds.h"

extern ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, DeathEffect, BackGroundMusic, StageClear, OneUpEffect, FireBallEffect, PowerUpAppearEffect, PowerUpEffect;
colectible coins[100], stars[100], life[100], starpow[100], fflower[100];
extern goompa gompav[100];
extern pirhana piranav[100];
firebll fireb[9];
int coino = 0, lifo = 0, staro = 0, fpow, firo=0;
extern float nci, ncf, nc1, wh;
extern int harta[30][1000], n, p, gdead;
extern void* skyblock, * mario_coin, * one_up, * mario_star, * mario_vine, * mario_vine_top, * fireball_1, * fireball_2, * fire_flower, * pipehead, * Rpipehead;


void fireballstateput(int a) {
	switch (fireb[a].fbstage) {
	case 1:
		std::cout << "AMP PSU";
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, fireball_1, COPY_PUT); break;
	case 2:
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, fireball_2, COPY_PUT); break;
	}
}

void fireballstateread(int a) {
	switch (fireb[a].fbstage) {
		case 1:
			readimagefile("fireball_1.gif", (fireb[a].jfireb - nci+ 0.3) * wh, (fireb[a].ifireb +0.3) * wh, ((fireb[a].jfireb - nci) + 0.7) * wh, (fireb[a].ifireb + 0.7) * wh); break;
		case 2:
			readimagefile("fireball_2.gif", (fireb[a].jfireb - nci + 0.3) * wh, (fireb[a].ifireb + 0.3) * wh, ((fireb[a].jfireb - nci) + 0.7) * wh, (fireb[a].ifireb + 0.7) * wh); break;
	}
}

void fireballmov(int a) {
	if (fireb[a].fbstage == 1) fireb[a].fbstage = 2;
	else fireb[a].fbstage = 1;
	std::cout << "FIREBALL: " << fireb[a].jfireb << " " << fireb[a].ifireb << '\n';
	if (fireb[a].fbdirection == 1) {
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, skyblock, COPY_PUT);
		if (fireb[a].jfireb - (int)fireb[a].jfireb != 0) {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				//cout << 2;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 3) {
				fireb[a].hoverf = 1;
				//cout << 3;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				//cout << 2;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 4) {
				fireb[a].hoverf = 1;
				//cout << 3;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				//cout << 4;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				//cout << 4;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == fireb[a].ifireb && coins[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, coins[i].icolec, coins[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 5;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= staro; i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == fireb[a].ifireb && starpow[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, starpow[i].icolec, starpow[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 6;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == fireb[a].ifireb && life[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, life[i].icolec, life[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 7;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == fireb[a].ifireb && fflower[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, fflower[i].icolec, fflower[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 7;
					putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, fire_flower, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		if (fireb[a].hoverf == 1) {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb > nci && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 10)) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					//aici niste sunet
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb > nci) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}

		}
		else {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb > nci && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb - 1] != 10)) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					//aici niste sunet
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb > nci) {
					fireb[a].jfireb -= 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}

		}
	}
	if (fireb[a].fbdirection == 0) {
		putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, skyblock, COPY_PUT);
		if (fireb[a].jfireb - (int)fireb[a].jfireb != 0) {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				//cout << 2;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 3) {
				fireb[a].hoverf = 1;
				//cout << 3;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				//cout << 2;
				putimage(((int)fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] == 4) {
				fireb[a].hoverf = 1;
				//cout << 3;
				putimage(((int)fireb[a].jfireb + 1 - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", ((int)gompav[a].jgompa + 1 - nci) * wh, gompav[a].igompa * wh, (((int)gompav[a].jgompa + 1 - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		else {
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 3) {
				fireb[a].hoverf = 1;
				//cout << 4;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
			if (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb] == 4) {
				fireb[a].hoverf = 1;
				//cout << 4;
				putimage((fireb[a].jfireb - nci) * wh, fireb[a].ifireb * wh, mario_vine_top, COPY_PUT);
				//readimagefile("mario_vine.gif", (gompav[a].jgompa - nci) * wh, gompav[a].igompa * wh, ((gompav[a].jgompa - nci) + 1) * wh, (gompav[a].igompa + 1) * wh);
			}
		}
		for (int i = 1;i <= coino;i++) {
			if (coins[i].mapart == (int)(nci - nc1) && coins[i].icolec == fireb[a].ifireb && coins[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, coins[i].icolec, coins[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 5;
					putimage((coins[i].jcolec - nci) * wh, coins[i].icolec * wh, mario_coin, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= staro; i++) {
			if (starpow[i].mapart == (int)(nci - nc1) && starpow[i].icolec == fireb[a].ifireb && starpow[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, starpow[i].icolec, starpow[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 6;
					putimage((starpow[i].jcolec - nci) * wh, starpow[i].icolec * wh, mario_star, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (life[i].mapart == (int)(nci - nc1) && life[i].icolec == fireb[a].ifireb && life[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, life[i].icolec, life[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 7;
					putimage((life[i].jcolec - nci) * wh, life[i].icolec * wh, one_up, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		for (int i = 1;i <= lifo; i++) {
			if (fflower[i].mapart == (int)(nci - nc1) && fflower[i].icolec == fireb[a].ifireb && fflower[i].colected == 0) {
				if (CheckBlock(fireb[a].ifireb, fireb[a].jfireb, wh, fflower[i].icolec, fflower[i].jcolec)) {
					fireb[a].hoverf = 1;
					//cout << 7;
					putimage((fflower[i].jcolec - nci) * wh, fflower[i].icolec * wh, fire_flower, COPY_PUT);
					//readimagefile("mario_coin.gif", (coins[i].jcolec - nci) * wh, coins[i].icolec * wh, ((coins[i].jcolec - nci) + 1) * wh, (coins[i].icolec + 1) * wh);
				}
			}
		}
		if (fireb[a].hoverf == 1) {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb < ncf && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb+1] != 1
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 13
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 8
				&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 10)) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					//aici niste sunet
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb < ncf) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateread(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}
			
		}
		else {
			if (fireb[a].jfireb - (int)fireb[a].jfireb == 0) {
				if (fireb[a].jfireb < ncf && (harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 1
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 12 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 13
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 14 && harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 8
					&& harta[(int)fireb[a].ifireb][(int)fireb[a].jfireb + 1] != 10)) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					//aici niste sunet
					fireb[a].exist = 0;
				}
			}
			else {
				if (fireb[a].jfireb < ncf) {
					fireb[a].jfireb += 0.5;
					fireb[a].hoverf = 0;
					fireballstateput(a);
				}
				else {
					fireb[a].exist = 0;
				}
			}
		}
	}
}

void fireballsmov() {
	for (int i = 0;i < 9;i++) {
		if (fireb[i].exist == 1) {
			fireballmov(i);
			for (int j = 1;j <= n;j++) {
				if (gompav[j].mapart == (int)(nci - nc1) && gompav[j].igompa == fireb[i].ifireb && gompav[j].dead == 0) {
					
					if (CheckBlock(fireb[i].ifireb * wh, fireb[i].jfireb * wh, wh, gompav[j].igompa * wh, gompav[j].jgompa * wh)) {
						std::cout << "PATRU";
						fireb[i].exist = 0;
						gompav[j].dead = 1;
						gdead++;
						ma_sound_stop(&GombaDeadEffect);
						ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
						ma_sound_start(&GombaDeadEffect);
						putimage((fireb[i].jfireb - nci) * wh, fireb[i].ifireb * wh, skyblock, COPY_PUT);
						putimage((gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, skyblock, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 3)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 4)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 3)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 4)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
					}
				}
			}
			for (int j = 1;j <= p;j++) {
				if (piranav[j].mapart == (int)(nci - nc1) && piranav[j].ipirana == fireb[i].ifireb && piranav[j].dead == 0 && piranav[j].ipinit != piranav[j].ipirana) {
					
					if (CheckBlock(fireb[i].ifireb * wh, fireb[i].jfireb * wh, wh, piranav[j].ipirana * wh, piranav[j].jpirana * wh)) {
						std::cout << "CINCI";
						fireb[i].exist = 0;
						piranav[j].dead = 1;
						ma_sound_stop(&GombaDeadEffect);
						ma_sound_seek_to_pcm_frame(&GombaDeadEffect, 0);
						ma_sound_start(&GombaDeadEffect);
						putimage((piranav[j].jpinit - nci) * wh, piranav[j].ipirana * wh, skyblock, COPY_PUT);
						if (piranav[p].orientation == -1)
							putimage((piranav[j].jpinit - nci) * wh, (piranav[j].ipinit) * wh, Rpipehead, COPY_PUT);
						else
							putimage((piranav[j].jpinit - nci) * wh, (piranav[j].ipinit) * wh, pipehead, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 3)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa] == 4)
							putimage(((int)gompav[j].jgompa - nci) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 3)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine, COPY_PUT);
						if (harta[(int)gompav[j].igompa][(int)gompav[j].jgompa + 1] == 4)
							putimage(((int)gompav[j].jgompa - nci + 1) * wh, gompav[j].igompa * wh, mario_vine_top, COPY_PUT);
					}
				}
			}
		}
	}
}