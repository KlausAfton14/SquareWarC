#include "game.h"
#include "collisions.h"
#include "config.h"
#include "entity.h"
#include "input.h"
#include "player.h"
#include "projectile.h"
#include "random.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void initGame(Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    int startingX = WINDOW_WIDTH / 2;
    int startingY = WINDOW_HEIGHT / 2;

    *player = spawnPlayer(startingX, startingY, 80, DEAFULT_PLAYER_HEALTH);
    updatePlayerHitbox(player);

    initEntities(entities);
    initProjectiles(projectiles);
}

void updateEntities(Player* player, EntityArray* entities, float dt, GameState* gameState)
{
    const float SPEED = ENTITY_SPEED;
    const float ATTACK_INTERVAL = 1.5f;

    for (size_t i = 0; i < entities->count; i++)
    {
        Entity* entity = &entities->data[i];

        float dx = player->x - entity->x;
        float dy = player->y - entity->y;
        float length = sqrtf(dx * dx + dy * dy);

        if (length > 0.01f)
        {
            dx /= length;
            dy /= length;
        }

        entity->x += dx * SPEED * dt;
        entity->y += dy * SPEED * dt;

        updateEntityHitbox(entity);

        entity->attackCooldown += dt;

        if (hitboxIntersects(entity->hitbox, player->hitbox))
        {
            if (entity->attackCooldown >= ATTACK_INTERVAL)
            {
                int dmg = entity->damage;
                player->health -= dmg;

                entity->attackCooldown = 0;

                printf("Player HP: %d\n", player->health);
                if (player->health <= 0)
                {
                    *gameState = GAME_OVER;
                }
            }
        }
    }
}

void updateProjectiles(ProjectileArray* projectiles, EntityArray* entities)
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
}

void updateGame(Player* player, EntityArray* entities, ProjectileArray* projectiles, GameState* gameState)
{
    static float entitySpawnTimer = 0.0f;

    entitySpawnTimer += 1.0f / 60.0f;

    if (entitySpawnTimer >= 5.0f)
    {
        int x, y, size;
        bool canSpawnEntity;
        int attempts = 0;
        const int MAX_ATTEMPTS = 50;

        do
        {
            canSpawnEntity = true;
            attempts++;

            x = randRange(0, WINDOW_WIDTH);
            y = randRange(0, WINDOW_HEIGHT);
            size = randRange(30, 80);

            float dxPlayer = x - player->x;
            float dyPlayer = y - player->y;
            float distPlayer = sqrtf(dxPlayer * dxPlayer + dyPlayer * dyPlayer);

            if (distPlayer <= 200 + size * 1.4f)
            {
                canSpawnEntity = false;
                continue;
            }

            for (size_t i = 0; i < entities->count; i++)
            {
                Entity* entity = &entities->data[i];
                float dxEntity = x - entity->x;
                float dyEntity = y - entity->y;
                float distEntity = sqrtf(dxEntity * dxEntity + dyEntity * dyEntity);

                if (distEntity <= (entity->size) + size * 1.3f)
                {
                    canSpawnEntity = false;
                    printf("Za blisko! %f\n", distEntity);
                    break;
                }
            }
        } while (!canSpawnEntity && attempts < MAX_ATTEMPTS);

        if (canSpawnEntity)
        {
            Entity entity = spawnEntity(x, y, size, 150, 20);
            updateEntityHitbox(&entity);
            addEntity(entities, entity);
        }

        entitySpawnTimer = 0.0f;
    }

    updateEntities(player, entities, 1.0f / 60.0f, gameState);
    updateProjectiles(projectiles, entities);

    if (*gameState == GAME_RUNNING)
    {
        if (keys_pressed[SDL_SCANCODE_W] && player->y >= (player->size / 2.0f))
            player->y -= PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_S] && player->y <= WINDOW_HEIGHT - (player->size / 2.0f))
            player->y += PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_A] && player->x >= (player->size / 2.0f))
            player->x -= PLAYER_STEP;

        if (keys_pressed[SDL_SCANCODE_D] && player->x <= WINDOW_WIDTH - (player->size / 2.0f))
            player->x += PLAYER_STEP;

        updatePlayerHitbox(player);
    }
}