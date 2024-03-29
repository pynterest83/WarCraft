#pragma once

#include "global.h"
#include "menu.h"
#include "rendergame.h"
#include "player.h"
#include "bullet.h"
#include "object.h"
#include "enemy.h"
#include "ebullet.h"

void renderbackground();
void setupShield(player& astro1);
void setupAsteroid(player& astro1);
void setupHeal(player& astro1);
void check_creep(player& astro1, vector<enemy>&list_creep, int& dmg);
void check_boss(player& astro1, enemy& Boss, vector<enemy>& list_creep, int& dmg);
void updatePlayer(player& astro1, vector<enemy>& list_creep);
void updatePlayer2(player& astro);
void g_Animation(player& astro1, SDL_Rect& lifebar_rect, SDL_Rect& energy_rect);
void check2P(player& astro1, player& astro2, int& dmg1, int& dmg2);
void handlePause1(player& astro1);
void handlePause2(player& astro1);
void handlePause11(player& astro1, player& astro2);
void handlePause22(player& astro1, player& astro2);
void handleMute();