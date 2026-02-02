#pragma once

#include "player.h"
#include "entity.h"
#include "projectile.h"
#include <SDL2/SDL_render.h>

void initRenderAssets(SDL_Renderer* renderer);
void renderGame(SDL_Renderer* renderer, Player* player, EntityArray* entities, ProjectileArray* projectiles);
void drawPlayer(SDL_Renderer* renderer, Player player);
void drawEntities(SDL_Renderer* renderer, Entity* entities, int entityCount);
void drawProjectiles(SDL_Renderer* renderer, Projectile* projectiles, int projectileCount);