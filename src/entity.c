#include "entity.h"

void initEntities(EntityArray* arr)
{
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;
}

Entity spawnEntity(int x, int y, int size, int health)
{
    Entity entity = {
        .x = x,
        .y = y,
        .size = size,
        .health = health,
        .hitbox = {0}};
    return entity;
}

void addEntity(EntityArray* arr, Entity e)
{
    if (arr->count == arr->capacity)
    {
        size_t new_cap = arr->capacity == 0 ? 4 : arr->capacity * 2;
        Entity* tmp = realloc(arr->data, new_cap * sizeof *tmp);

        if (!tmp)
        {
            perror("realloc");
            exit(1);
        }

        arr->data = tmp;
        arr->capacity = new_cap;
    }

    arr->data[arr->count++] = e;
}

void removeEntity(EntityArray* arr, size_t index)
{
    if (index >= arr->count)
        return;
    arr->data[index] = arr->data[arr->count - 1];
    arr->count--;
}

void updateEntityHitbox(Entity* entity)
{
    entity->hitbox.w = entity->size;
    entity->hitbox.h = entity->size;
    entity->hitbox.x = entity->x - entity->size / 2.0f;
    entity->hitbox.y = entity->y - entity->size / 2.0f;
}