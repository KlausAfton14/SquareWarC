#include "random.h"
#include <stdlib.h>

int randRange(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int randFloat(float min, float max)
{
    return min + (float) rand() / RAND_MAX * (max - min + 1);
}