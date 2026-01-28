#include "game.h"
#include "config.h"

void initGame(Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    int startingX = WINDOW_WIDTH / 2;
    int startingY = WINDOW_HEIGHT / 2;

    *player = spawnPlayer(startingX, startingY, 50);
    updatePlayerHitbox(player);

    initEntities(entities);
    initProjectiles(projectiles);

    Entity entity1 = spawnEntity(20, 20, 20);
    updateEntityHitbox(&entity1);
    addEntity(entities, entity1);

    Entity entity2 = spawnEntity(600, 500, 20);
    updateEntityHitbox(&entity2);
    addEntity(entities, entity2);
}

void updateGame(EntityArray* entities, ProjectileArray* projectiles)
{
    for (size_t i = 0; i < projectiles->count;)
    {
        if (
            projectiles->data[i].x < 0 ||
            projectiles->data[i].y < 0 ||
            projectiles->data[i].x > WINDOW_WIDTH ||
            projectiles->data[i].y > WINDOW_HEIGHT)
        {
            removeProjectile(projectiles, i);
            continue;
        }

        projectiles->data[i].x += projectiles->data[i].velX;
        projectiles->data[i].y += projectiles->data[i].velY;
        updateProjectileHitbox(&projectiles->data[i]);

        bool hit = false;

        for (size_t j = 0; j < entities->count;)
        {
            if (hitboxIntersects(projectiles->data[i].hitbox, entities->data[j].hitbox))
            {
                removeEntity(entities, j);
                removeProjectile(projectiles, i);
                hit = true;
                break;
            }
            else
            {
                j++;
            }
        }

        if (!hit)
            i++;
    }
}
