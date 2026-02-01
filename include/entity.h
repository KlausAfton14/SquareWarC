#pragma once
#include "collisions.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float x;
    float y;
    int size;
    int health;
    Hitbox hitbox;
} Entity;

typedef struct
{
    Entity* data;
    size_t count;
    size_t capacity;
} EntityArray;

void initEntities(EntityArray* arr);
Entity spawnEntity(int x, int y, int size, int health);
void addEntity(EntityArray* arr, Entity e);
void removeEntity(EntityArray* arr, size_t index); // Removes entity by swapping with last element (order not preserved)
void updateEntityHitbox(Entity* entity);