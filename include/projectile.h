#pragma once
#include "collisions.h"
#include "player.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float x;
    float y;
    int size;
    int damage;
    float velX;
    float velY;
    Hitbox hitbox;
} Projectile;

typedef struct
{
    Projectile* data;
    size_t count;
    size_t capacity;
} ProjectileArray;


void initProjectiles(ProjectileArray* arr);
Projectile spawnProjectile(Player player, int size, int damage, int targetX, int targetY);
void addProjectile(ProjectileArray* arr, Projectile p);
void removeProjectile(ProjectileArray* arr, size_t index); // Removes projectile by swapping with last element (order not preserved)
void updateProjectileHitbox(Projectile* projectile);