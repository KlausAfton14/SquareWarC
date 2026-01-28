#pragma once

#include "player.h"
#include "entity.h"
#include "projectile.h"
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

void renderGame(SDL_Surface* surface, SDL_Window* window, Player* player, EntityArray* entities, ProjectileArray* projectiles);
void drawPlayer(SDL_Surface* surface, Player player);
void drawEntities(SDL_Surface* surface, Entity* entities, int entityCount);
void drawProjectiles(SDL_Surface* surface, Projectile* projectiles, int projectileCount);