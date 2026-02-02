#include "input.h"
#include "config.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_scancode.h>
#include <stdbool.h>

bool keys_pressed[SDL_NUM_SCANCODES];

void handeEvents(bool* running, Player* player, EntityArray* entities, ProjectileArray* projectiles)
{
    SDL_Event event;
    int mouseX, mouseY;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *running = false;
            break;

        case SDL_MOUSEMOTION:
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseX = event.motion.x;
            mouseY = event.motion.y;
            if (event.button.button == SDL_BUTTON_RIGHT)
            {
                Projectile projectile = spawnProjectile(*player, 7, DEAFULT_PROJECTILE_DAMAGE, mouseX, mouseY);
                updateProjectileHitbox(&projectile);
                addProjectile(projectiles, projectile);
            }

            if (event.button.button == SDL_BUTTON_LEFT)
            {
                Entity entity = spawnEntity(mouseX, mouseY, 40, DEAFULT_ENTITY_HEALTH, 20);
                updateEntityHitbox(&entity);
                addEntity(entities, entity);
            }
            break;

        case SDL_KEYDOWN:
            keys_pressed[event.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            keys_pressed[event.key.keysym.scancode] = false;
            break;
        }
    }
}