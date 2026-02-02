#include "render.h"
#include "config.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <stdio.h>

static SDL_Texture* playerTexture;
static SDL_Texture* entityTexture;

static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if (!surface)
    {
        printf("Error while loading texture: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void initRenderAssets(SDL_Renderer* renderer)
{
    playerTexture = loadTexture(renderer, "assets/player.png");
    entityTexture = loadTexture(renderer, "assets/entity.jpg");
}

void renderGame(SDL_Renderer* renderer, Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR, 255);
    SDL_RenderClear(renderer);

    drawEntities(renderer, entities->data, entities->count);
    drawProjectiles(renderer, projectiles->data, projectiles->count);
    drawPlayer(renderer, *player);

    SDL_RenderPresent(renderer);
}

void drawPlayer(SDL_Renderer* renderer, Player player)
{
    SDL_Rect playerRect = {
        (int) (player.x - player.size / 2.0f),
        (int) (player.y - player.size / 2.0f),
        player.size,
        player.size};
    // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // SDL_RenderFillRect(renderer, &playerRect);
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
}

void drawEntities(SDL_Renderer* renderer, Entity* entities, int entityCount)
{
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < entityCount; i++)
    {
        SDL_Rect entityRect = {
            (int) (entities[i].x - entities[i].size / 2.0f),
            (int) (entities[i].y - entities[i].size / 2.0f),
            entities[i].size,
            entities[i].size};
        // SDL_RenderFillRect(renderer, &entityRect);
        SDL_RenderCopy(renderer, entityTexture, NULL, &entityRect);
    }
}

void drawProjectiles(SDL_Renderer* renderer, Projectile* projectiles, int projectileCount)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (int i = 0; i < projectileCount; i++)
    {
        SDL_Rect projectileRect = {
            (int) (projectiles[i].x - projectiles[i].size / 2.0f),
            (int) (projectiles[i].y - projectiles[i].size / 2.0f),
            projectiles[i].size,
            projectiles[i].size};
        SDL_RenderFillRect(renderer, &projectileRect);
    }
}