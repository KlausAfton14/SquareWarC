#pragma once
#include "collisions.h"

typedef struct
{
    float x;
    float y;
    int size;
    int health;
    int ammo;
    Hitbox hitbox;
} Player;

Player spawnPlayer(int x, int y, int size, int health);
void updatePlayerHitbox(Player* player);