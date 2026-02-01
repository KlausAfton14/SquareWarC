#pragma once

#include <SDL2/SDL_render.h>
#include <stdbool.h>

bool initSDL(SDL_Window** window, SDL_Renderer** renderer);
void shutdownSDL(SDL_Window* window, SDL_Renderer* renderer);