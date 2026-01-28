#pragma once 
#include <stdbool.h>

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} Hitbox;

bool hitboxIntersects(Hitbox a, Hitbox b);