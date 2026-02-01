#include "player.h"

Player spawnPlayer(int x, int y, int size, int health)
{
    Player player = {
        .x = x,
        .y = y,
        .size = size,
        .health = health,
        .ammo = 25,
        .hitbox = {0}};
    return player;
}

void updatePlayerHitbox(Player* player)
{
    player->hitbox.w = player->size;
    player->hitbox.h = player->size;
    player->hitbox.x = player->x - player->size / 2.0f;
    player->hitbox.y = player->y - player->size / 2.0f;
}