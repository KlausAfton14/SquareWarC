#include "projectile.h"
#include <math.h>

void initProjectiles(ProjectileArray* arr)
{
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

Projectile spawnProjectile(Player player, int size, int damage, int targetX, int targetY)
{

    float dx = targetX - player.x;
    float dy = targetY - player.y;

    float length = sqrtf(dx * dx + dy * dy);
    if (length == 0)
        length = 1;

    float speed = 5.0f;

    Projectile projectile = {
        .x = player.x,
        .y = player.y,
        .size = size,
        .damage = damage,
        .velX = (dx / length) * speed,
        .velY = (dy / length) * speed,
        .hitbox = {0}};
    return projectile;
}

void addProjectile(ProjectileArray* arr, Projectile p)
{
    if (arr->count == arr->capacity)
    {
        size_t new_cap = arr->capacity == 0 ? 4 : arr->capacity * 2;
        Projectile* tmp = realloc(arr->data, new_cap * sizeof *tmp);

        if (!tmp)
        {
            perror("realloc");
            exit(1);
        }

        arr->data = tmp;
        arr->capacity = new_cap;
    }

    arr->data[arr->count++] = p;
}

void removeProjectile(ProjectileArray* arr, size_t index)
{
    if (index >= arr->count)
        return;
    arr->data[index] = arr->data[arr->count - 1];
    arr->count--;
}

void updateProjectileHitbox(Projectile* projectile)
{
    projectile->hitbox.w = projectile->size;
    projectile->hitbox.h = projectile->size;
    projectile->hitbox.x = projectile->x - projectile->size / 2.0f;
    projectile->hitbox.y = projectile->y - projectile->size / 2.0f;
}