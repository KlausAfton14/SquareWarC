#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#define WINDOW_TITLE "SquareWar"
#define WINDOW_WIDTH 901
#define WINDOW_HEIGHT 601
#define TARGET_FPS 60
#define BACKGROUND_COLOR 0x00141414

#define PLAYER_SIZE 50
#define ENTITY_SIZE 20

typedef struct {
    float x;
    float y;
    int size;
    int health;
    int ammo;
} Player;

typedef struct {   
    float x;
    float y;
    int size;
    int health;
} Entity;

typedef struct {
    float x;
    float y;
    int size;
    int damage;
    float velX; 
    float velY;
} Projectile;

typedef struct {
    Entity *data;
    size_t count;
    size_t capacity;
} EntityArray;

typedef struct {
    Projectile *data;
    size_t count;
    size_t capacity;
} ProjectileArray;

void initEntities(EntityArray *arr)
{
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

void initProjectiles(ProjectileArray *arr)
{
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

Player spawnPlayer(int x, int y)
{
    Player player = {
        x,
        y,
        PLAYER_SIZE,
        100,
        25
    };
    return player;
}

Entity spawnEntity(int x, int y)
{
    Entity entity = {
        x,
        y,
        ENTITY_SIZE,
        50
    };
    return entity;
}

Projectile spawnProjectile(Player player, int size, int targetX, int targetY)
{

    float dx = targetX - player.x;
    float dy = targetY - player.y;

    float length = sqrtf(dx * dx + dy * dy);
    if(length == 0) length = 1;

    float speed = 2.0f;

    Projectile projectile = {
        player.x,
        player.y,
        size,
        50,
        (dx / length) * speed,
        (dy / length) * speed
    };
    return projectile;
}

void addEntity(EntityArray *arr, Entity e)
{
    if(arr->count == arr->capacity)
    {
        size_t new_cap = arr->capacity == 0 ? 4 : arr->capacity * 2;
        Entity *tmp = realloc(arr->data, new_cap * sizeof *tmp);

        if(!tmp)
        {
            perror("realloc");
            exit(1);
        }

        arr->data = tmp;
        arr->capacity = new_cap;
    }

    arr->data[arr->count++] = e;
}

void addProjectile(ProjectileArray *arr, Projectile p)
{
    if(arr->count == arr->capacity)
    {
        size_t new_cap = arr->capacity == 0 ? 4 : arr->capacity * 2;
        Projectile *tmp = realloc(arr->data, new_cap * sizeof *tmp);

        if(!tmp)
        {
            perror("realloc");
            exit(1);
        }

        arr->data = tmp;
        arr->capacity = new_cap;
    }

    arr->data[arr->count++] = p;
}

void removeEntity(EntityArray *arr, int index)
{
    if (index < 0 || index >= arr->count) return;
    arr->data[index] = arr->data[arr->count - 1];
    arr->count--;
}

void removeProjectile(ProjectileArray *arr, int index)
{
    if (index < 0 || index >= arr->count) return;
    arr->data[index] = arr->data[arr->count - 1];
    arr->count--;
}

void drawPlayer(SDL_Surface *surface, Player player)
{
    SDL_Rect playerRect = {
        (int) (player.x - player.size / 2.0f),
        (int) (player.y - player.size / 2.0f),
        player.size,
        player.size
    };
    SDL_FillRect(surface, &playerRect, 0x000000ff);
}

void drawEntities(SDL_Surface *surface, Entity *entities, int entityCount)
{
    for (int i = 0; i < entityCount; i++) {
        SDL_Rect entityRect = {
            (int) (entities[i].x - entities[i].size / 2.0f),
            (int) (entities[i].y - entities[i].size / 2.0f),
            entities[i].size,
            entities[i].size
        };
        SDL_FillRect(surface, &entityRect, 0x00ff0000);
    }
}

void drawProjectiles(SDL_Surface *surface, Projectile *projectiles, int projectileCount)
{
    for (int i = 0; i < projectileCount; i++) {
        SDL_Rect projectileRect = {
            (int) (projectiles[i].x - projectiles[i].size / 2.0f),
            (int) (projectiles[i].y - projectiles[i].size / 2.0f),
            projectiles[i].size,
            projectiles[i].size
        };
        SDL_FillRect(surface, &projectileRect, 0x0000ff00);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Rect windowRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_FillRect(surface, &windowRect, BACKGROUND_COLOR);

    float frameDelay = (1.0f / TARGET_FPS) * 1000;
    int mouseX;
    int mouseY;

    int startingX = WINDOW_WIDTH / 2;
    int startingY = WINDOW_HEIGHT / 2;

    Player player = spawnPlayer(startingX, startingY);

    Entity entity1 = spawnEntity(20, 20);
    Entity entity2 = spawnEntity(600, 500);

    Projectile projectile1 = spawnProjectile(player, 10, 500, 500);
    Projectile projectile2 = spawnProjectile(player, 10, 200, 200);

    EntityArray entities;
    initEntities(&entities);

    addEntity(&entities, entity1);
    addEntity(&entities, entity2);

    ProjectileArray projectiles;
    initProjectiles(&projectiles);

    addProjectile(&projectiles, projectile1);
    addProjectile(&projectiles, projectile2);


    while (!done) {
        SDL_FillRect(surface, &windowRect, BACKGROUND_COLOR);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_MOUSEMOTION:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    Projectile projectile = spawnProjectile(player, 15, mouseX, mouseY);
                    addProjectile(&projectiles, projectile);
                    break;
            }
        }

        for(int i = 0; i < projectiles.count;)
        {
            if (
                projectiles.data[i].x < 0 || 
                projectiles.data[i].y < 0 || 
                projectiles.data[i].x > WINDOW_WIDTH || 
                projectiles.data[i].y > WINDOW_HEIGHT)
            {
                removeProjectile(&projectiles, i);
                continue;
            }
            
            projectiles.data[i].x += projectiles.data[i].velX;
            projectiles.data[i].y += projectiles.data[i].velY;

            printf("x: %d, y: %d, c: %d\n", 
                (int)projectiles.data[i].x, 
                (int)projectiles.data[i].y, 
                (int)projectiles.count);

            i++;
        }

        drawEntities(surface, entities.data, entities.count);
        drawProjectiles(surface, projectiles.data, projectiles.count);
        drawPlayer(surface, player);

        SDL_UpdateWindowSurface(window);
        SDL_Delay((int)frameDelay);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}