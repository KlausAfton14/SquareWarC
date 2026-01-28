#pragma once

#include "player.h"
#include "entity.h"
#include "projectile.h"

void initGame(Player* player, EntityArray* entities, ProjectileArray* projectiles);
void updateGame(EntityArray* entities, ProjectileArray* projectiles);
