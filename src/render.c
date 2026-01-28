#include "render.h"
#include "config.h"

void renderGame(SDL_Surface* surface, SDL_Window* window, Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    SDL_Rect bg = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_FillRect(surface, &bg, BACKGROUND_COLOR);

    drawEntities(surface, entities->data, entities->count);
    drawProjectiles(surface, projectiles->data, projectiles->count);
    drawPlayer(surface, *player);

    SDL_UpdateWindowSurface(window);
}

void drawPlayer(SDL_Surface* surface, Player player)
{
    SDL_Rect playerRect = {
        (int) (player.x - player.size / 2.0f),
        (int) (player.y - player.size / 2.0f),
        player.size,
        player.size};
    SDL_FillRect(surface, &playerRect, 0x000000ff);
}

void drawEntities(SDL_Surface* surface, Entity* entities, int entityCount)
{
    for (int i = 0; i < entityCount; i++)
    {
        SDL_Rect entityRect = {
            (int) (entities[i].x - entities[i].size / 2.0f),
            (int) (entities[i].y - entities[i].size / 2.0f),
            entities[i].size,
            entities[i].size};
        SDL_FillRect(surface, &entityRect, 0x00ff0000);
    }
}

void drawProjectiles(SDL_Surface* surface, Projectile* projectiles, int projectileCount)
{
    for (int i = 0; i < projectileCount; i++)
    {
        SDL_Rect projectileRect = {
            (int) (projectiles[i].x - projectiles[i].size / 2.0f),
            (int) (projectiles[i].y - projectiles[i].size / 2.0f),
            projectiles[i].size,
            projectiles[i].size};
        SDL_FillRect(surface, &projectileRect, 0x0000ff00);
    }
}