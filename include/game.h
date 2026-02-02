#pragma once

#include "player.h"
#include "entity.h"
#include "projectile.h"

typedef enum
{
    GAME_RUNNING,
    GAME_OVER
} GameState;

void initGame(Player* player, EntityArray* entities, ProjectileArray* projectiles);
void updateEntities(Player* player, EntityArray* entities, float dt, GameState* gameState);
void updateGame(Player*player, EntityArray* entities, ProjectileArray* projectiles, GameState* gameState);
