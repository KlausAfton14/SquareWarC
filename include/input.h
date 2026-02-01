#pragma once

#include "entity.h"
#include "player.h"
#include "projectile.h"
#include <SDL2/SDL_scancode.h>

extern bool keys_pressed[SDL_NUM_SCANCODES];
void handeEvents(bool* running, Player* player, EntityArray* entities, ProjectileArray* projectiles);