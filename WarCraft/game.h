#pragma once

#include "global.h"
#include "gamelogic.h"
#include "menu.h"
#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "ebullet.h"

class game {
public:
	// load all game feature
	game() {};
	~game() {};
	void loadMenu();
	void loadText();
	void loadCharacter();
	void loadSound();
	void loadDefault();
	void loadShield();
	void loadAsteroid();
	void loadHeal();
	void Resetgame();
	void loadSingleGame(player& astro1, vector<enemy>& list_creep, enemy& Boss);
	void load2Playergame(player& astro1, player& astro2);
};
