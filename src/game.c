#include "game.h"
#include "config.h"
#include "entity.h"
#include "input.h"
#include "projectile.h"

void initGame(Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    int startingX = WINDOW_WIDTH / 2;
    int startingY = WINDOW_HEIGHT / 2;

    *player = spawnPlayer(startingX, startingY, 80, DEAFULT_PLAYER_HEALTH);
    updatePlayerHitbox(player);

    initEntities(entities);
    initProjectiles(projectiles);
}

void updateGame(Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    for (size_t i = 0; i < projectiles->count;)
    {
        Projectile* projectile = &projectiles->data[i];

        if (
            projectile->x < 0 ||
            projectile->y < 0 ||
            projectile->x > WINDOW_WIDTH ||
            projectile->y > WINDOW_HEIGHT)
        {
            removeProjectile(projectiles, i);
            continue;
        }

        projectile->x += projectile->velX;
        projectile->y += projectile->velY;
        updateProjectileHitbox(projectile);

        bool hit = false;

        for (size_t j = 0; j < entities->count;)
        {
            if (hitboxIntersects(projectile->hitbox, entities->data[j].hitbox))
            {
                Entity* entity = &entities->data[j];

                int dmg = projectile->damage;
                entity->health -= dmg;

                if (entity->health <= 0)
                    removeEntity(entities, j);
                else
                    j++;

                removeProjectile(projectiles, i);

                hit = true;
                break;
            }
            else
                j++;
        }
        if (!hit)
            i++;
    }

    {
        if (keys_pressed[SDL_SCANCODE_W] && player->y >= 0)
            player->y -= PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_S] && player->y <= WINDOW_HEIGHT)
            player->y += PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_A] && player->x >= 0)
            player->x -= PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_D] && player->x <= WINDOW_WIDTH)
            player->x += PLAYER_STEP;
    }
}
